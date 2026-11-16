#include <iostream>
#include "Task-1.h"
#include "TemplateMastery.hpp"
using namespace std;

void runStep1() {
    std::cout << "--- 1a) Testing PrintTypeSize ---\n";
    int testInt = 20;
    double testDouble = 10.5;
    TStudent testStruct{"Kristoffer", 22, 85};

    PrintTypeSize(testInt);
    PrintTypeSize(testDouble);
    PrintTypeSize(testStruct);

    std::cout << "\n--- 1b) Testing GetMax ---\n";
    int maxInt = GetMax(5, 10);
    cout << "Max Int: " << maxInt << "\n";

    TStudent studentA{"Kristoffer", 22, 85};
    TStudent studentB{"Henrik", 27, 75};

    TStudent topStudent = GetMax(studentA, studentB);
    cout << "Top Student Grade: " << topStudent.grade << "\n";

    std::cout << "\n--- 1c) Testing TDataPack (Variadic) ---\n";
    TDataPack<int, double, std::string> dataPack = {5, 2.3, "hello"};

    std::cout << "DataPack Value 1 (int): " << dataPack.value << "\n";
    std::cout << "DataPack Value 2 (double): " << dataPack.rest.value << "\n";
    std::cout << "DataPack Value 3 (string): " << dataPack.rest.rest.value << "\n";

    std::cout << "\n--- 1d) Testing TStaticArray ---\n";
    TStaticArray<int, 3> numbers1;
    numbers1.Populate(0, 1);
    numbers1.Populate(1, 2);
    numbers1.Populate(2, 3);

    std::cout << "Array contents: ";
    numbers1.Print();

    std::cout << "\n--- 1e) Testing PrintContainer (Template-Template) ---\n";
    PrintContainer(numbers1);
}