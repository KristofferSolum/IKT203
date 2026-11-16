//
// Created by krist on 10.11.2026.
//

#ifndef STANDALONESEARCH_H
#define STANDALONESEARCH_H
#include "TBankAccount.h"
#include "SerchTypes.hpp"

TBankAccount* FindAccountByNumber(
    TBankAccount** accountArray,
    int arraySize,
    const std::string& accountNumber,
    SearchSummary& summary);

void PrintEveryAccountInDateRange(
    TBankAccount** accountArray,
    int arraySize,
    time_t fromDate,
    time_t toDate,
    SearchSummary& summary);

#endif //STANDALONESEARCH_H
