//
// Created by krist on 17.11.2026.
//

#ifndef POPULATELIST_H
#define POPULATELIST_H

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <string>

#include "TLinkedList.hpp"
#include "TBankAccount.h"

struct AccountOwner {
	std::string firstName;
	std::string lastName;
};

inline int LoadAccountOwners(AccountOwner accountOwners[], int maxOwners){
	std::ifstream file("names.txt");
	int ownerCount = 0;

	if (!file.is_open()) {
		std::cerr << "ERROR: Could not open random-names.txt" << std::endl;
		return 0;
	}
	while (ownerCount < maxOwners && file >> accountOwners[ownerCount].firstName >> accountOwners[ownerCount].lastName) {
		ownerCount++;
	}
	return ownerCount;
}

inline std::string GenerateAccountNumber(int index) {
	constexpr long long maxAccounts = 1'000'000;
	constexpr long long multiplier = 791'999;
	constexpr long long offset = 382'417;
	constexpr long long prefix = 10'000'000'000LL;

	if (index < 0 || index >= maxAccounts) {
		return "";
	}

	long long shuffled = (multiplier * index + offset) % maxAccounts;
	long long accountNumber = prefix + shuffled;

	return std::to_string(accountNumber);
}

inline EBankAccountType GenerateAccountType() {
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(1, 5);

	return static_cast<EBankAccountType>(dist(rng));
}

inline time_t GenerateTimestamp() {
	static std::mt19937 rng(std::random_device{}());

	std::tm startDate = {};
	startDate.tm_year = 2024 - 1900;
	startDate.tm_mon = 0;
	startDate.tm_mday = 1;
	startDate.tm_isdst = -1;

	std::tm endDate = {};
	endDate.tm_year = 2025 - 1900;
	endDate.tm_mon = 0;
	endDate.tm_mday = 1;
	endDate.tm_isdst = -1;

	time_t start = std::mktime(&startDate);
	time_t end = std::mktime(&endDate);

	std::uniform_int_distribution<time_t> dist(start, end-1);
	return dist(rng);
}


inline int PopulateAccount(TLinkedList<TBankAccount>* accountList, TBankAccount** accountArray) {
	AccountOwner owners[1000];
	int numberOfOwners = LoadAccountOwners(owners, 1000);
	int numberOfAccounts = 0;
	for (int i = 0; i < numberOfOwners; i++) {
		AccountOwner owner = owners[i];
		if (numberOfAccounts > 5000) {
			break;
		}
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> dist(5, 10);
		int n = dist(rng);
		for (int i = 0; i < n; i++) {
			auto* newAccount = new TBankAccount(
				GenerateAccountNumber(numberOfAccounts),
				GenerateAccountType(),
				owner.firstName,
				owner.lastName,
				GenerateTimestamp());
			accountArray[numberOfAccounts] = newAccount;
			accountList->Append(newAccount);
			numberOfAccounts++;
		}
	}
	return numberOfAccounts;
}

#endif //POPULATELIST_H
