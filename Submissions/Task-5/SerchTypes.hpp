//
// Created by krist on 10.11.2026.
//

#pragma once
#include "TBankAccount.h"
#include <ctime>
class TBankAccount;

struct SearchSummary {
    long long comparisons = 0;
    double timeSpentMs = 0.0;
};

template <typename T>
using FCompare = bool (*)(T*, void*);


using FCompareAccounts = FCompare<TBankAccount>;

inline bool CompareAccountNumber(TBankAccount* account, void* searchKey) {
    auto* accountNumber = static_cast<std::string*>(searchKey);
    if (account->GetAccountNumber() == *accountNumber) {
        return true;
    }
    return false;
}

struct MonthSearchKey {
    int month;
    int year;
};

inline bool CompareAccountMonth(TBankAccount* account, void* searchKey) {
    auto* key = static_cast<MonthSearchKey*>(searchKey);

    std::time_t timestamp = account->GetCreationTimestamp();
    std::tm* date = std::localtime(&timestamp);

    return date->tm_mon == key->month - 1 &&
           date->tm_year == key->year - 1900;
}

