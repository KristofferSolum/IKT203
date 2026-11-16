//
// Created by krist on 07.11.2026.
//

#include "TStack.h"
#include <stack>
#include <stdexcept>

bool TStack::IsEmpty() {
    // Time: O(1), Space: O(1)
    // Checks whether the stack is empty using a single comparison.
    if (top_idx == -1) {
        return true;
    }
    return false;
}

int TStack::Peek() {
    // Time: O(1), Space: O(1)
    // Returns the top element without removing it.
    if (IsEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return values[top_idx];
}

int TStack::Pop() {
    // Time: O(1), Space: O(1)
    // Removes and returns the top element by decrementing top_idx.
    if (IsEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    top_idx--;
    return values[top_idx + 1];
}

void TStack::Push(int item) {
    // Time: O(1), Space: O(1)
    // Adds an element at the top of the stack by incrementing top_idx.
    if (top_idx == MAX_SIZE - 1) {
        throw std::overflow_error("Stack is full");
    }
    top_idx++;
    values[top_idx] = item;
}


