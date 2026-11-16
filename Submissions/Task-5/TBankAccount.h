//
// Created by krist on 08.11.2026.
//

#ifndef TBANKACCOUNT_H
#define TBANKACCOUNT_H
#include <string>
#include "EBankAccountType.h"


class TBankAccount {
private:
    std::string accountNumber;
    EBankAccountType accountType;
    std::string ownerFirstName;
    std::string ownerLastName;
    time_t creationTimestamp;
    double balance;
public:
    TBankAccount(std::string accountNumber,
        EBankAccountType accountType,
        std::string ownerFirstName,
        std::string ownerLastName,
        time_t creationTimestamp);
    std::string GetAccountNumber();
    EBankAccountType GetAccountType() const;
    std::string GetOwnerFirstName();
    std::string GetOwnerLastName();
    time_t GetCreationTimestamp() const;
    double GetBalance() const;
    void PrintAccountInfo() const;
    std::string GetAccountTypeAsString() const;
    std::string GetCreationTimestampAsString() const;
};



#endif //TBANKACCOUNT_H
