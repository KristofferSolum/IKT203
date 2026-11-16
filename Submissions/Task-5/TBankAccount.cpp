//
// Created by krist on 08.11.2026.
//

#include "TBankAccount.h"

#include <iostream>
#include <random>
#include <__msvc_ostream.hpp>
#include <ctime>
#include <iomanip>
#include <sstream>


TBankAccount::TBankAccount(std::string accountNumber, EBankAccountType accountType, std::string ownerFirstName,
                           std::string ownerLastName, time_t creationTimestamp) {
    this->accountNumber = accountNumber;
    this->accountType = accountType;
    this->ownerFirstName = ownerFirstName;
    this->ownerLastName = ownerLastName;
    this->creationTimestamp = creationTimestamp;

    if (accountType == EBankAccountType::LOAN) {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(-50'000, -25'000);
        this->balance = dist(rng);
    }
    else {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, 1000);
        this->balance = dist(rng);
    }

}

std::string TBankAccount::GetAccountNumber() {
    return this->accountNumber;
}

EBankAccountType TBankAccount::GetAccountType() const {
    return this->accountType;
}

std::string TBankAccount::GetOwnerFirstName() {
    return this->ownerFirstName;
}

std::string TBankAccount::GetOwnerLastName() {
    return this->ownerLastName;
}

time_t TBankAccount::GetCreationTimestamp() const {
    return this->creationTimestamp;
}

double TBankAccount::GetBalance() const {
    return this->balance;
}

std::string TBankAccount::GetAccountTypeAsString() const {
    std::string accountTypeText;
    switch (this->accountType) {
        case EBankAccountType::CREDIT:
            accountTypeText = "Credit";
            break;

        case EBankAccountType::CHECKING:
            accountTypeText = "Checking";
            break;

        case EBankAccountType::LOAN:
            accountTypeText = "Loan";
            break;

        case EBankAccountType::PENSION:
            accountTypeText = "Pension";
            break;

        case EBankAccountType::SAVINGS:
            accountTypeText = "Savings";
            break;

        default:
            accountTypeText ="Unknown";
            break;
    }

    return accountTypeText;
}

std::string TBankAccount::GetCreationTimestampAsString() const {
    std::tm* date = std::localtime(&creationTimestamp);
    std::ostringstream stream;
    stream << std::put_time(date, "%Y-%m-%d %H:%M:%S");
    return stream.str();

}


void TBankAccount::PrintAccountInfo() const {
    std::cout << "--- Account Number: " << this->accountNumber << " ---" << std::endl;
    std::cout << "Account Type: " << this->GetAccountTypeAsString() << std::endl;
    std::cout << "Owners First Name: " << this->ownerFirstName << std::endl;
    std::cout << "Owners Last Name: " << this->ownerLastName << std::endl;
    std::cout << "Creation Date: : " << this->GetCreationTimestampAsString() << std::endl;
    std::cout << "Account Balance: " << this->balance << std::endl;
}


