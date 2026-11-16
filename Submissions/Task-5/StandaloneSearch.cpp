//
// Created by krist on 10.11.2026.
//
#include "StandaloneSearch.h"
#include <chrono>


TBankAccount* FindAccountByNumber(
    TBankAccount** accountArray,
    int arraySize,
    const std::string& accountNumber,
    SearchSummary& summary) {

    summary.comparisons = 0;
    const auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < arraySize; i++) {
        summary.comparisons++;
        if (accountArray[i]->GetAccountNumber() == accountNumber) {
            const auto end = std::chrono::steady_clock::now();
            summary.timeSpentMs = std::chrono::duration<double, std::milli>(end - start).count();
            return accountArray[i];
        }
    }
    const auto end = std::chrono::steady_clock::now();
    summary.timeSpentMs = std::chrono::duration<double, std::milli>(end - start).count();
    return nullptr;
}

void PrintEveryAccountInDateRange(
    TBankAccount** accountArray,
    int arraySize,
    time_t fromDate,
    time_t toDate,
    SearchSummary& summary) {

    summary.comparisons = 0;
    const auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < arraySize; i++) {
        summary.comparisons++;
        if (accountArray[i]->GetCreationTimestamp() >= fromDate && accountArray[i]->GetCreationTimestamp() < toDate) {
            accountArray[i]->PrintAccountInfo();
        }
    }
    const auto end = std::chrono::steady_clock::now();
    summary.timeSpentMs = std::chrono::duration<double, std::milli>(end - start).count();
}
