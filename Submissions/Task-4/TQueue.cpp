//
// Created by krist on 07.11.2026.
//

#include "TQueue.h"
#include <stdexcept>

void TQueue::Enqueue(int item) {
    // Time: O(1), Space: O(1)
    // Adds an element at the back using circular indexing.
    if (IsFull()) {
        throw std::overflow_error("Queue is full");
    }
    if (IsEmpty()) {
        front_idx = 0;
        back_idx = 0;
        values[back_idx] = item;
    }
    else {
        back_idx = (back_idx +1) % MAX_SIZE;
        values[back_idx] = item;
    }
}

int TQueue::Dequeue() {
    // Time: O(1), Space: O(1)
    // Removes the front element and advances front_idx.
    if (IsEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    int item = values[front_idx];

    if (front_idx == back_idx) {
        front_idx = -1;
        back_idx = -1;

    }
    else {
        front_idx = (front_idx +1) % MAX_SIZE;
    }
    return item;
}

int TQueue::Peek() {
    // Time: O(1), Space: O(1)
    // Returns the front element without removing it.
    if (IsEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    return values[front_idx];
}

bool TQueue::IsEmpty() {
    // Time: O(1), Space: O(1)
    // Checks whether the queue is empty.
    if (front_idx == -1 && back_idx == - 1) {
        return true;
    }
    return false;
}

bool TQueue::IsFull() {
    // Time: O(1), Space: O(1)
    // Checks whether the next position would reach front_idx.
    return (back_idx +1) % MAX_SIZE == front_idx;
}
