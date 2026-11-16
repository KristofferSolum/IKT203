#pragma once
#include <iostream>
using namespace std;

int Add(int a, int b);

string Greet(const string &name);
using GreetPtr = string(*)(const string&);

bool IsEven(int value);
bool IsOdd(int value);

using FPredicatePtr = bool(*)(int);
void FilterAndPrint(int [], int size, FPredicatePtr filter);

void Play();
void Pause();
void Quit();

void DoubleInt(int& val);
void CapitalizeChar(char& val);