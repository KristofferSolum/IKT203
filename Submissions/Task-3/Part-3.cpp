//
// Created by krist on 07.11.2026.
//
#include<iostream>
#include <random>
#include <stdexcept>
#include "Task-3.h"
using namespace std;


int findLargestElement(int arr[], int size) {
    // Time: O(n), Space: O(log n)
    // The function recursively divides the array into two halves.
    // All n elements are examined, while the maximum recursion depth
    // grows logarithmically with the array size.
    if (size <= 0) {
        throw std::invalid_argument("Array size must be greater than zero!");
    }
    else if (size == 1) {
        return arr[0];
    }

    int mid = size / 2;
    int left = findLargestElement(arr, mid);
    int right = findLargestElement(arr + mid, size - mid);

    return max(left, right);
}

void printArray(int arr[], int size) {
    // Time: O(n), Space: O(1)
    // The function iterates through the array to print its elements.
    // It uses constant extra memory regardless of the array size.
    if (size <= 50) {
        std::cout << "Array: [";

        for (int i = 0; i < size; i++) {
            std::cout << arr[i];

            if (i < size - 1) {
                std::cout << ", ";
            }
        }

        std::cout << "]" << std::endl;
    }
}

void testRandomArray(int size) {
    // Time: O(n), Space: O(n)
    // The function generates n random numbers and finds the largest element.
    // The array requires linear memory, while the recursive calls
    // use logarithmic stack space.
    int* arr = new int[size];

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    for (int i = 0; i < size; i++) {
        arr[i] = dist(rng);
    }

    try {
        int largest = findLargestElement(arr, size);
        cout << "Array size: " << size << endl;
        printArray(arr, size);
        std::cout << "Largest element: " << largest << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    delete[] arr;
}

void traverseAsciiTable(char start, char end) {
    // Time: O(n), Space: O(n)
    // The function recursively traverses n ASCII characters.
    // Each character is printed twice, and each recursive call
    // uses space on the call stack.
    if (end < start) {
        std::cout << "Start must be less than or equal to end!" << std::endl;
        return;
    }
    // When the print statement is placed before the recursive call,
    // the character is printed before the next recursive call is added to the stack,
    // so the characters are printed in ascending order.
    cout << start << " ";
    if (start != end) {
        traverseAsciiTable(start + 1, end);
    }
    if (start == end) {
        cout << endl;
    }
    cout << start << " ";
    // When the print statement is placed after the recursive call,
    // all the recursive calls are completed before printing starts.
    // The last function call finishes first,
    // so the characters are printed in descending order.

}

void runPart3() {
    cout << "--- 6) Largest element in an array ---" << endl;
    cout << "--- test 1 ---"<< endl;
    testRandomArray(10);
    cout << "--- test 2 ---"<< endl;
    testRandomArray(50);
    cout << "--- test 3 ---"<< endl;
    testRandomArray(100);
    cout << "--- test 4 ---"<< endl;
    testRandomArray(0);

    cout << "--- 7) ASCII table traversal ---" << endl;
    traverseAsciiTable('a', 'e');

}