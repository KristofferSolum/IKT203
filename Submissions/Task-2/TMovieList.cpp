//
// Created by krist on 06.11.2026.
//

#include "TMovieList.h"


TMovieList::TMovieList() {
    head = new TMovieNode(nullptr);
    tail = head;
}

TMovieList::~TMovieList() {
    TMovieNode* current = head;

    while (current != nullptr) {
        TMovieNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void TMovieList::Append(TMovie *movie) {
    auto* newNode = new TMovieNode(movie);
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
}

void TMovieList::Prepend(TMovie *movie) {
    auto* newNode = new TMovieNode(movie);

    newNode->prev = head;
    newNode->next = head->next;

    if (head->next != nullptr) {
        head->next->prev = newNode;
    }

    head->next = newNode;

    if (tail == head) {
        tail = newNode;
    }
}

TMovie *TMovieList::GetAtIndex(int index) {
    if (index < 0) {
        return nullptr;
    }

    int current_index = 0;
    TMovieNode* current = head->next;

    while (current != nullptr && current_index < index) {
        current = current->next;
        current_index++;
    }

    if (current == nullptr) {
        return nullptr;
    }

    return current->movie;
}


void TMovieList::Remove(int index) {
    if (index >= 0) {
        int current_index = 0;
        TMovieNode* current = head;

        while (current != nullptr && current_index < index) {
            current = current->next;
            current_index++;
        }

        if (current != nullptr && current->next != nullptr) {
            if (tail == current->next) {
                tail = current;
            }
            TMovieNode* nextNode = current->next->next;
            delete current -> next;
            current->next = nextNode;
            if (nextNode != nullptr) {
                current->next->prev = current;
            }
        }

    }
}

void TMovieList::Reverse() {
    if (head->next == nullptr || head->next == tail) {
        return;
    }

    TMovieNode* current = head->next;
    tail = current;

    TMovieNode* previous = nullptr;

    while (current != nullptr) {
        TMovieNode* nextNode = current->next;

        current->next = previous;
        current->prev = nextNode;

        previous = current;
        current = nextNode;
    }

    head->next = previous;
    previous->prev = head;
}

TMovie *TMovieList::SearchFor(FCheckMovie callback, void* criteria) {
    for (TMovieNode* current = head->next; current != nullptr; current = current->next) {
        if (callback(current->movie, criteria)) {
            return current->movie;
        }
    }
    return nullptr;
}

