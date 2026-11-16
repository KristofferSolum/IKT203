#include "GlobalCallbacks.h"

int Add(int a, int b) {
    return a + b;
}

string Greet(const string &name) {
    return "Hello, " + name;
}

bool IsEven(int value) {
    if (value % 2 == 0) {
        return true;
    }
    return false;
}

bool IsOdd(int value) {
    if (value % 2 != 0) {
        return true;
    }
    return false;
}

void FilterAndPrint(int arr[], int size, FPredicatePtr filter) {
    for (int i = 0; i < size; i++) {
        if (filter(arr[i])) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
}

void Play() {
    cout << "Playing game..." << endl;
}

void Pause() {
    cout << "Game paused." << endl;
}

void Quit() {
    cout << "Quitting game." << endl;
}

void DoubleInt(int &val) {
    val *= 2;
}

void CapitalizeChar(char &val) {
    val = toupper(val);
}