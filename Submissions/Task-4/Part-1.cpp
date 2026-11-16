//
// Created by krist on 08.11.2026.
//
#include <iostream>
#include "Task-4.h"
#include "TQueue.h"
#include "TStack.h"
using namespace std;

void testStack() {
     // Time: O(n), Space: O(n)
     // Tests stack operations, including filling the stack to capacity.
    TStack stack;

    cout << "--- Stack Tests ---" << endl;

    cout << "New stack is empty: "
         << (stack.IsEmpty() ? "PASS" : "FAIL")
         << endl;

    stack.Push(10);
    stack.Push(20);
    stack.Push(30);

    cout << "Peek after Push: "
         << (stack.Peek() == 30 ? "PASS" : "FAIL")
         << endl;

    cout << "Stack is not empty: "
         << (!stack.IsEmpty() ? "PASS" : "FAIL")
         << endl;

    cout << "Pop 30: "
     << (stack.Pop() == 30 ? "PASS" : "FAIL")
     << endl;

    cout << "Pop 20: "
         << (stack.Pop() == 20 ? "PASS" : "FAIL")
         << endl;

    cout << "Pop 10: "
         << (stack.Pop() == 10 ? "PASS" : "FAIL")
         << endl;

    cout << "Stack empty after Pop: "
         << (stack.IsEmpty() ? "PASS" : "FAIL")
         << endl;

     try {
          stack.Pop();
          cout << "Pop on empty stack: FAIL" << endl;
     }
     catch (const std::underflow_error& e) {
          cout << "Pop on empty stack: PASS" << endl;
     }

     try {
          stack.Peek();
          cout << "Peek on empty stack: FAIL" << endl;
     }
     catch (const std::underflow_error& e) {
          cout << "Peek on empty stack: PASS" << endl;
     }

     for (int i = 0; i < MAX_SIZE; i++) {
          stack.Push(i);
     }

     cout << "Fill stack to capacity: "
          << (stack.Peek() == MAX_SIZE - 1 ? "PASS" : "FAIL")
          << endl;

     try {
          stack.Push(12000);
          cout << "Push on full stack: FAIL" << endl;
     }
     catch (const std::overflow_error& e) {
          cout << "Push on full stack: PASS" << endl;
     }

     stack.Pop();

     try {
          stack.Push(99999);

          cout << "Push after Pop on full stack: "
               << (stack.Peek() == 99999 ? "PASS" : "FAIL")
               << endl;
     }
     catch (const std::overflow_error& e) {
          cout << "Push after Pop on full stack: FAIL" << endl;
     }
}

void testQueue() {
     // Time: O(n), Space: O(n)
     // Tests queue operations, including filling the queue to capacity.
     TQueue queue;
     cout << "--- Queue Tests ---" << endl;
     cout << "New queue is empty: "
     << (queue.IsEmpty() ? "PASS" : "FAIL")
     << endl;

     queue.Enqueue(10);
     queue.Enqueue(20);
     queue.Enqueue(30);

     cout << "Peek after Enqueue: "
     << (queue.Peek() == 10 ? "PASS" : "FAIL")
     << endl;
     cout << "Queue not empty: "
     << (!queue.IsEmpty() ? "PASS" : "FAIL")
     << endl;
     cout << "Dequeue 10: "
     << (queue.Dequeue() == 10 ? "PASS" : "FAIL")
     << endl;
     cout << "Dequeue 20: "
     << (queue.Dequeue() == 20 ? "PASS" : "FAIL")
     << endl;
     cout << "Dequeue 30: "
     << (queue.Dequeue() == 30 ? "PASS" : "FAIL")
     << endl;
     cout << "Queue empty after Dequeue: "
     << (queue.IsEmpty() ? "PASS" : "FAIL")
     << endl;

     try {
          queue.Dequeue();
          cout << "Dequeue on empty queue: FAIL" << endl;
     }
     catch (const std::underflow_error& e) {
          cout << "Dequeue on empty queue: PASS" << endl;
     }
     try {
          queue.Peek();
          cout << "Peek on empty queue: FAIL" << endl;
     }
     catch (const std::underflow_error& e) {
          cout << "Peek on empty queue: PASS" << endl;
     }

     for (int i = 0; i < MAX_SIZE; i++) {
          queue.Enqueue(i);
     }

     cout << "Fill queue to capacity: "
          << (queue.IsFull() ? "PASS" : "FAIL")
          << endl;

     try {
          queue.Enqueue(10);
          cout << "Enqueue on full queue: FAIL" << endl;
     }
     catch (const std::overflow_error& e) {
          cout << "Enqueue on full queue: PASS" << endl;
     }

     queue.Dequeue();

     try {
          queue.Enqueue(99999);

          cout << "Enqueue after Dequeue on full queue: "
               << (queue.Peek() == 1 && queue.IsFull() ? "PASS" : "FAIL")
               << endl;
     }
     catch (const std::overflow_error& e) {
          cout << "Enqueue after Dequeue on full queue: FAIL" << endl;
     }
}

void runPart1() {
    cout << "--- 1) Implementing a Stack ---" << endl;
    testStack();

     cout << "--- 2) Implementing a Queue  ---" << endl;
     testQueue();
}