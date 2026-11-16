//
// Created by krist on 07.11.2026.
//
#include <iostream>
#include <stdexcept>
#include "Task-3.h"
using namespace std;

void printNaturalNumbers(int n){
    // Time: O(n), Space: O(n)
    // The function makes n recursive calls, each using space on the call stack.
    if (n < 1) {
        cout << n << " is not a natural number!" << endl;
        return;
    }
    if (n-1 > 0) {
        printNaturalNumbers(n-1);
    }

    cout << n << " ";
}

int calculateFactorial(int n) {
    // Time: O(n), Space: O(n)
    // The function makes n recursive calls, each using space on the call stack.
    if (n < 0) {
        throw std::invalid_argument("Cannot calculate factorial of a negative number!");
    }
    else if (n == 0) {
        return 1;
    }
    else {
        return n * calculateFactorial(n-1);
    }
}

void printFactorial(int n) {
    // Time: O(n), Space: O(n)
    // Calls calculateFactorial(n), which uses linear time and stack space.
    try {
        std::cout << n << "! = " << calculateFactorial(n) << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

void runPart1() {
    cout << "--- 1) Print natural numbers from 1 to n ---" << endl;
    cout << "n = 10: ";
    printNaturalNumbers(10);
    cout << endl;
    cout << "n = 0: ";
    printNaturalNumbers(0);
    cout << endl;
    cout << "n = -3: ";
    printNaturalNumbers(-3);
    cout << endl;

    cout << "--- 2) Calculate the factorial of a number n ---" << endl;
    printFactorial(5);
    printFactorial(-3);
    printFactorial(0);

}