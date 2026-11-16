//
// Created by krist on 08.11.2026.
//
#include <iostream>
#include <stdexcept>
#include "TQueue.h"
#include "TStack.h"
#include "Task-4.h"
#include <string>
using namespace std;

string reverseString(string text) {
    // Time: O(n), Space: O(n)
    // Reverses a string by pushing and popping each character using a stack.
    // A stack uses LIFO (Last In, First Out), meaning the last character
    // pushed onto the stack is the first one popped.
    // This allows us to retrieve the characters in reverse order.
    TStack stack;
    for (char c : text) {
        try {
            stack.Push(c);
        }
        catch(const std::overflow_error& e) {
           return  "Error: " + string(e.what()) + "\n";
        }
    }

    string reversedText = "";

    while (!stack.IsEmpty()) {
        try {
            char c = static_cast<char>(stack.Pop());
            reversedText += c;
        }
        catch(const std::underflow_error& e) {
            return  "Error: " + string(e.what()) + "\n";
        }
    }
    return reversedText;
}

int calculateFactorial(int n) {
    // Time: O(n), Space: O(n)
    // Calculates factorial by pushing numbers onto a stack and multiplying them.
    if (n < 0) {
        throw std::invalid_argument("Cannot calculate factorial of a negative number!");
    }
    else if (n == 0) {
        return 1;
    }
    TStack stack;
    int factorial = 1;
    while (n > 0){
        stack.Push(n);
        n --;
    }
    while (!stack.IsEmpty()) {
        factorial *= stack.Pop();
    }

    return factorial;
}

void printFactorial(int n) {
    // Time: O(n), Space: O(n)
    // Prints the factorial calculated using a stack.
    try {
        std::cout << n << "! = " << calculateFactorial(n) << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void simulateWaitingLine() {
    // Time: O(1), Space: O(n)
    // Simulates a fixed number of customers using a queue.
    cout << "--- Ticket Counter Simulation ---" << endl;
    TQueue queue;
    cout << "Person 101 joins the queue." << endl;
    queue.Enqueue(101);
    cout << "Person 102 joins the queue." << endl;
    queue.Enqueue(102);
    cout << "Person 103 joins the queue." << endl;
    queue.Enqueue(103);
    cout << "Serving person " << queue.Dequeue() << "." << endl;
    cout << "Person 104 joins the queue." << endl;
    queue.Enqueue(104);
    while (!queue.IsEmpty()) {
        cout << "Serving person " << queue.Dequeue() << "." << endl;
    }
    cout << "Queue is empty." << endl;

}



void runPart2() {
    cout << "--- 3) String Reversal with a Stack ---" << endl;
    string text = "Hello World!";
    cout << "Initial text: " << text << endl;
    cout << "Reversed text: " << reverseString(text) << endl;

    cout << "--- 4) Recursive Functions with a Stack ---" << endl;
    printFactorial(5);
    printFactorial(-3);
    printFactorial(0);

    cout << "--- 5) Wait Line Simulation with a Queue ---" << endl;
    try {
        simulateWaitingLine();
    }
    catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}
