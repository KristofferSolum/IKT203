#pragma once

template <typename T>
class TNode {
private:
    T* data;
    TNode* next;
public:
    TNode(T* data);
    ~TNode();
    T* GetData();
    TNode* GetNext();
    void SetNext(TNode* next);
};

template<typename T>
TNode<T>::TNode(T *data) {
    this->data = data;
    this->next = nullptr;
}

template<typename T>
TNode<T>::~TNode() {
    this->next = nullptr;
}

template<typename T>
T *TNode<T>::GetData() {
    return this->data;
}

template<typename T>
TNode<T> *TNode<T>::GetNext() {
    return this->next;
}

template<typename T>
void TNode<T>::SetNext(TNode *next) {
    this->next = next;
}



