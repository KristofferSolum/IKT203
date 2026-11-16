#include <iostream>
#include "Task-1.h"
#include "TemplateMastery.hpp"
#include "GlobalCallbacks.h"
using namespace std;

void runStep3() {
    std::cout << endl << "--- 3) Callbacks + Templates (In-Place Modification) ---\n";

    int nums[5] = {1, 2, 3, 4, 5};
    char chars[5] = {'a', 'b', 'c', 'd', 'e'};

    FActionFunc<int> FDoubleInt = &DoubleInt;
    FActionFunc<char> FCapitalizeChar = &CapitalizeChar;

    std::cout << "Integers before: ";

    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    ProcessArray(nums, sizeof(nums)/sizeof(nums[0]), FDoubleInt);

    std::cout << "Integers after: ";

    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    std::cout << "Chars before: ";

    for (char c : chars) {
        cout << c << " ";
    }
    cout << endl;

    ProcessArray(chars, sizeof(chars)/sizeof(chars[0]), FCapitalizeChar);

    std::cout << "Chars after: ";

    for (char c : chars) {
        cout << c << " ";
    }
    cout << endl;

}