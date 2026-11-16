//
// Created by krist on 07.11.2026.
//
#include <iostream>
#include <stdexcept>
#include <string>
#include <random>
#include "Task-3.h"

double power(int base, int exponent) {
    // Time: O(log n), Space: O(log n)
    // The exponent is halved in each recursive call, reducing both
    // the number of operations and the depth of the call stack.
    if (base == 0 && exponent < 0) {
        throw std::invalid_argument("Cannot divide by zero!");
    }
    if (exponent == 0) {
        return 1;
    }
    else if (exponent < 0) {
        return 1.0 / power(base, -exponent);
    }
    else if (exponent % 2 == 0) {
        double half = power(base, exponent / 2);
        return half * half;
    }
    else {
        double half = power(base, (exponent - 1) / 2);
        return base * half * half;
    }

}

void printPower(int base, int exponent) {
    // Time: O(log n), Space: O(log n)
    // Calls power(), which uses logarithmic time and stack space.
    try {
        std::cout << base <<"^"<<exponent<<" = " << power(base, exponent) << std::endl;
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

int fibonacci(int n) {
    // Time: O(2^n), Space: O(n)
    // The function makes two recursive calls, resulting in repeated calculations.
    // The maximum recursion depth grows linearly with n.
    // This function uses two recursive calls to calculate the Fibonacci number,
    // so both recursive calls end up calculating several of the same Fibonacci numbers.
    // To make the function more efficient, we can store the earlier results so the recursive calls
    // don't need to calculate the same values multiple times.
    if ( n == 0 || n == 1 ) {
        return n;
    }
    else if ( n < 0 ) {
        throw std::invalid_argument("Fibonacci n cannot be negative!");
    }
    else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

void printFibonacci(int n) {
    // Time: O(2^n), Space: O(n)
    // Calls fibonacci(), which has exponential time complexity
    // and linear stack space usage.
    try {
        std::cout <<"Fibonacci("<< n<<") :" << fibonacci(n) << std::endl;
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

int countOccurrences(const char* aS, char aC) {
    // Time: O(n), Space: O(n)
    // The function checks one character per recursive call.
    // No strings are copied, but each call uses space on the call stack.
    if (*aS == '\0') {
        return 0;
    }
    if (*aS == aC) {
        return 1 + countOccurrences(aS +1, aC);
    }
    else {
        return countOccurrences(aS + 1, aC);
    }
}

struct RandomStringData {
    std::string text;
    char target;
};

RandomStringData generateRandomString(int length) {
    // Time: O(n), Space: O(n)
    // The function generates n random characters using a loop.
    // The resulting string requires memory proportional to n.
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist('a', 'z');
    std::string result;

    for (int i = 0; i < length; i++) {
        result += static_cast<char>(dist(rng));
    }

    char target = static_cast<char>(dist(rng));

    return RandomStringData{result, target};
}

void testRandomOccurrences(int length) {
    // Time: O(n), Space: O(n)
    // Generates a random string and counts character occurrences recursively.
    // Both operations require linear time and space.
    RandomStringData randomString = generateRandomString(length);
    int count = countOccurrences(randomString.text.c_str(), randomString.target);

    if (length <= 100) {
        std::cout << "String: " << randomString.text << std::endl;
    }
    std::cout << "String length: " << length << std::endl;
    std::cout << "Target character: " << randomString.target << std::endl;
    std::cout << "Occurrences: " << count << std::endl;
}

void runPart2() {
    std::cout << "--- 3) Power calculation ---" << std::endl;
    printPower(2, 3);
    printPower(3, -2);
    printPower(0, -2);
    printPower(3, 0);
    printPower(0, 3);

    std::cout << "--- 4) Fibonacci sequence ---" << std::endl;
    printFibonacci(4);
    printFibonacci(0);
    printFibonacci(1);
    printFibonacci(-2);

    std::cout << "--- 5) Count occurrences of a character in a string ---" << std::endl;
    std::cout << "--- test 1 ---" << std::endl;
    testRandomOccurrences(20);
    std::cout << "--- test 2 ---" << std::endl;
    testRandomOccurrences(100);


}
