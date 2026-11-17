#pragma once
#include "TNode.hpp"
#include "SerchTypes.hpp"
#include <chrono>


template <typename T>
class TLinkedList {
    private:
    TNode<T>* head;
    TNode<T>* tail;
    bool ownsData;
    int count = 0;
    public:
    TLinkedList(bool ownsData = false);
    ~TLinkedList();
    TNode<T>* GetHead() const;
    void SetTail(TNode<T>* node);
    bool IsEmpty() const;
    int GetCount() const;
    void Append(T* data);
    bool Remove(T* data);
    T* Find(FCompare<T> aOnCompare, void* searchKey, SearchSummary& summary);
    TLinkedList<T>* Every(FCompare<T> aOnCompare, void* searchKey, SearchSummary& summary);
    void ForEach(void (*action)(T*)) const;
    void ForEach(void (*action)(T*, void*), void* context) const;
};

template<typename T>
TNode<T>* TLinkedList<T>::GetHead() const {
    return head;
}

template<typename T>
void TLinkedList<T>::SetTail(TNode<T>* node) {
    tail = node;
}

template<typename T>
bool TLinkedList<T>::IsEmpty() const {
    return head == tail;
}

template<typename T>
int TLinkedList<T>::GetCount() const {
    return count;
}

template<typename T>
TLinkedList<T>::TLinkedList(bool ownsData) {
    this->head = new TNode<T>(nullptr);
    this->tail = head;
    this->ownsData = ownsData;
}

template<typename T>
TLinkedList<T>::~TLinkedList() {
    TNode<T>* current = head;

    while (current != nullptr) {
        TNode<T>* nextNode = current->GetNext();
        if (ownsData) {
            delete current->GetData();
        }
        delete current;
        current = nextNode;
    }
}

template<typename T>
void TLinkedList<T>::Append(T *data) {
    auto* newNode = new TNode<T>(data);
    tail->SetNext(newNode);
    tail = newNode;
    count++;
}

template<typename T>
bool TLinkedList<T>::Remove(T *data) {
    TNode<T>* previous = head;
    while (previous->GetNext() != nullptr && previous->GetNext()->GetData() != data) {
        previous = previous->GetNext();
    }
    if (previous->GetNext() != nullptr && previous->GetNext()->GetData() == data) {
        if (previous->GetNext()->GetNext() == nullptr) {
            if (ownsData) {
                delete previous->GetNext()->GetData();
            }
            delete previous->GetNext();
            tail = previous;
            previous->SetNext(nullptr);
        }
        else {
            TNode<T>* nextNode = previous->GetNext()->GetNext();
            if (ownsData) {
                delete previous->GetNext()->GetData();
            }
            delete previous->GetNext();
            previous->SetNext(nextNode);
        }
        count--;
        return true;
    }
    return false;
}

template<typename T>
T *TLinkedList<T>::Find(FCompare<T> aOnCompare, void *searchKey, SearchSummary &summary) {
    const auto start = std::chrono::steady_clock::now();
    TNode<T>* current = head;
    summary.comparisons = 0;

    while (current->GetNext() != nullptr) {
        current = current->GetNext();
        summary.comparisons++;
        if (aOnCompare(current->GetData(), searchKey)) {
            const auto end = std::chrono::steady_clock::now();
            summary.timeSpentMs = std::chrono::duration<double, std::milli>(end - start).count();
            return current->GetData();
        }
    }

    const auto end = std::chrono::steady_clock::now();
    summary.timeSpentMs = std::chrono::duration<double, std::milli>(end - start).count();
    return nullptr;
}

template<typename T>
TLinkedList<T> *TLinkedList<T>::Every(FCompare<T> aOnCompare, void *searchKey, SearchSummary &summary) {
    const auto start = std::chrono::steady_clock::now();
    TNode<T>* current = head;
    summary.comparisons = 0;
    TLinkedList<T> *result = new TLinkedList<T>(false);

    while (current->GetNext() != nullptr) {
        current = current->GetNext();
        summary.comparisons++;
        if (aOnCompare(current->GetData(), searchKey)) {
            result->Append(current->GetData());
        }
    }
    const auto end = std::chrono::steady_clock::now();
    summary.timeSpentMs = std::chrono::duration<double, std::milli>(end - start).count();
    return result;
}

template<typename T>
void TLinkedList<T>::ForEach(void (*action)(T*)) const {
    TNode<T>* current = head->GetNext();

    while (current != nullptr) {
        action(current->GetData());
        current = current->GetNext();
    }
}

template<typename T>
void TLinkedList<T>::ForEach(
    void (*action)(T*, void*),
    void* context
) const {
    TNode<T>* current = head->GetNext();

    while (current != nullptr) {
        action(current->GetData(), context);
        current = current->GetNext();
    }
}
