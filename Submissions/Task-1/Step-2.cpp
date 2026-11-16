#include <iostream>
#include "GlobalCallbacks.h"
using namespace std;

void runStep2() {
    int (*addPtr)(int, int) = &Add;
    cout <<endl<< "--- 2a) Basic Assignment & Invocation ---\n";
    cout << "Explicit call: " << (*addPtr)(5, 6) << "\n";
    cout << "Implicit call: " << addPtr(5, 6) << "\n";

    std::cout << "\n--- 2b) Making It Readable with Type Aliases ---\n";
    GreetPtr myGreeter = &Greet;
    cout << myGreeter("Kristoffer") << "\n";

    std::cout << "\n--- 2c) Passing Functions as Arguments (Callbacks) ---\n";
    int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = std::size(numbers);

    cout << "Evens: " << endl;
    FilterAndPrint(numbers, size, &IsEven);
    cout << "Odds: " << endl;
    FilterAndPrint(numbers, size, &IsOdd);

    std::cout << "\n--- 2d) Array of Function Pointers ---\n";
    using FAction = void(*)();
    FAction gamingList[] = {&Play, &Pause, &Play, &Quit};

    for (const auto & i : gamingList) {
        i();
    }
}