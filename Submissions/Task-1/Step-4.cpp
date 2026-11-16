//
// Created by krist on 06.11.2026.
//
#include <iostream>
#include "Task-1.h"
#include "ContextPointers.hpp"
using namespace std;

void runStep4() {
    std::cout<< endl << "--- 4) OOP Template Class & Context Pointers ---\n";

    TDataAggregator<int> dataAggregator;

    int arr[5] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Initial Array: ";
    for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
    std::cout << "\nInitial State Total: " << dataAggregator.GetStateTotal() << "\n\n";

    ProcessWithContext(arr, size, TDataAggregator<int>::StaticCallback, &dataAggregator);

    std::cout << "Modified Array (Doubled): ";
    for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";

    std::cout << "\nModified State Total: " << dataAggregator.GetStateTotal() << "\n\n";

}
