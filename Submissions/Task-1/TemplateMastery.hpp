#pragma once
#include <iostream>
#include <__msvc_ostream.hpp>
using namespace std;


template <typename T>
void PrintTypeSize(T v) {
    cout << sizeof(v) << endl;
}

struct TStudent {
    string name;
    int age;
    int grade;
    bool operator>(const TStudent &other) const {
        if (grade != other.grade){
            return grade > other.grade;
        }
        return age > other.age;
    }
};

template <typename T>
T GetMax(T a, T b) {
    if (a > b) {
        return a;
    }
    return b;
}


template <typename... Args>
struct TDataPack;

template <>
struct TDataPack<>{
};

template <typename First, typename ...Rest>
struct TDataPack<First, Rest...> {
    First value;
    TDataPack<Rest...> rest;
};


template <typename T, int Size>
class TStaticArray {
private:
    T data[Size]{};
public:
    void Populate(int index, T value) {
        data[index] = value;
    }
    void Print() {
        for (int i = 0; i < Size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};


template <
    template <typename, int> class Container,
    typename T,
    int N
>
void PrintContainer(Container<T, N>& container) {
    container.Print();
}


template <typename T>
using FActionFunc = void(*)(T&);

template <typename T>
void ProcessArray(T* arr, int size, FActionFunc<T> callback) {
    for (int i = 0; i < size; i++) {
        callback(arr[i]);
    }
}

