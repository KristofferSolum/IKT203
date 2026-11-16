#include <iostream>
#include "TLinkedList.hpp"
#include "SerchTypes.hpp"
#include "StandaloneSearch.h"
#include <random>
#include <fstream>
#include <ctime>
#include <filesystem>


struct AccountOwner {
	std::string firstName;
	std::string lastName;
};

int LoadAccountOwners(AccountOwner accountOwners[], int maxOwners){
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

std::string GenerateAccountNumber(int index) {
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

EBankAccountType GenerateAccountType() {
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(1, 5);

	return static_cast<EBankAccountType>(dist(rng));
}

time_t GenerateTimestamp() {
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


int PopulateAccount(TLinkedList<TBankAccount>* accountList, TBankAccount** accountArray) {
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

void PrintAccount(TBankAccount* account) {
	account->PrintAccountInfo();
}

struct PersonStats {
	std::string firstName;
	std::string lastName;
	double debt = 0;
	bool activeMonths[12] = {};
};

struct BankStats {
	PersonStats people[10000];
	int personCount = 0;

	double monthlyBalance[12] = {};
};

void CollectBankStats(TBankAccount* account, void* context) {
	auto* stats = static_cast<BankStats*>(context);

	// Get creation month
	time_t timestamp = account->GetCreationTimestamp();
	std::tm date = *std::localtime(&timestamp);
	int month = date.tm_mon;

	// Task 3: Sum monthly balances
	double balance = account->GetBalance();
	stats->monthlyBalance[month] += balance;

	// Find existing person
	int personIndex = -1;

	for (int i = 0; i < stats->personCount; i++) {
		if (stats->people[i].firstName == account->GetOwnerFirstName() &&
			stats->people[i].lastName == account->GetOwnerLastName()) {
			personIndex = i;
			break;
			}
	}

	// Register new person if necessary
	if (personIndex == -1) {
		if (stats->personCount >= 10000)
			return;

		personIndex = stats->personCount++;

		stats->people[personIndex].firstName = account->GetOwnerFirstName();
		stats->people[personIndex].lastName = account->GetOwnerLastName();
	}

	PersonStats& person = stats->people[personIndex];

	// Task 1: Add debt (negative balances only)
	if (balance < 0)
		person.debt -= balance;

	// Task 2: Track unique person per month
	person.activeMonths[month] = true;
}

void PrintBankStats(const BankStats& stats) {
	// Task 1
	int peopleWithDebt = 0;

	for (int i = 0; i < stats.personCount; i++) {
		const PersonStats& person = stats.people[i];

		if (!person.lastName.empty() &&
			person.lastName[0] == 'F' &&
			person.debt > 50000) {
			peopleWithDebt++;
			}
	}

	std::cout << "1. People with last name F and debt > 50000: "
			  << peopleWithDebt << '\n';

	// Task 2
	int peoplePerMonth[12] = {};

	for (int i = 0; i < stats.personCount; i++) {
		for (int month = 0; month < 12; month++) {
			if (stats.people[i].activeMonths[month])
				peoplePerMonth[month]++;
		}
	}

	int mostPeopleMonth = 0;

	for (int month = 1; month < 12; month++) {
		if (peoplePerMonth[month] >
			peoplePerMonth[mostPeopleMonth]) {
			mostPeopleMonth = month;
			}
	}

	std::cout << "2. Month with most unique people: "
			  << mostPeopleMonth + 1
			  << " (" << peoplePerMonth[mostPeopleMonth]
			  << " people)\n";

	// Task 3
	int lowestDebtMonth = 0;
	int highestDebtMonth = 0;

	for (int month = 1; month < 12; month++) {
		if (stats.monthlyBalance[month] >
			stats.monthlyBalance[lowestDebtMonth]) {
			lowestDebtMonth = month;
			}

		if (stats.monthlyBalance[month] <
			stats.monthlyBalance[highestDebtMonth]) {
			highestDebtMonth = month;
			}
	}

	std::cout << "3. Lowest net debt: Month "
			  << lowestDebtMonth + 1
			  << " (" << -stats.monthlyBalance[lowestDebtMonth] << ")\n";

	std::cout << "   Highest net debt: Month "
			  << highestDebtMonth + 1
			  << " (" << -stats.monthlyBalance[highestDebtMonth] << ")\n";
}


int main(){
	TLinkedList<TBankAccount> accountList(true);
	TBankAccount** accountArray = new TBankAccount*[10000];
	auto numberOfAccounts = PopulateAccount(&accountList, accountArray);

	std::cout << std::endl<<"--- Test Find() account number ---"<< std::endl;
	std::string searchKeyAccountNumber = accountArray[numberOfAccounts - 5]->GetAccountNumber();
	SearchSummary summary;
	FCompareAccounts FCompareAccountNumber = &CompareAccountNumber;
	auto searchedAccount1 = accountList.Find(FCompareAccountNumber, &searchKeyAccountNumber, summary);
	if (searchedAccount1 != nullptr && searchedAccount1->GetAccountNumber() == searchKeyAccountNumber) {
		std::cout << "Search sucsessfull!" << std::endl;
		std::cout << "Number of comparisons: " << summary.comparisons << std::endl;
		std::cout << "Searching time:  " << summary.timeSpentMs << std::endl;
		searchedAccount1->PrintAccountInfo();
	}

	std::cout << std::endl <<"--- Test Find() account not existing ---" << std::endl;
	std::string missingAccountNumber = "99999999999";
	SearchSummary missingSummary;
	auto searchedMissingAccount = accountList.Find(FCompareAccountNumber, &missingAccountNumber, missingSummary);
	if (searchedMissingAccount == nullptr) {
		std::cout << "Search Successful!" << std::endl;
	}
	else {
		std::cout << "Test Failed!" << std::endl;
	}
	std::cout << "Number of comparisons: " << missingSummary.comparisons << std::endl;
	std::cout << "Searching time:  " << missingSummary.timeSpentMs << std::endl;

	std::cout << std::endl << "--- Test Every(), find all accounts created June 2024 ---" << std::endl;
	MonthSearchKey searchKeyAccountMonth = {6, 2024};
	FCompareAccounts FCompareAccountMonth = &CompareAccountMonth;
	auto searchedAccounts2 = accountList.Every(FCompareAccountMonth, &searchKeyAccountMonth, summary);
	searchedAccounts2->ForEach(PrintAccount);

	std::cout <<std::endl<< "--- Test PrintEveryAccountInDateRange(), find all accounts created first quarter of 2024 ---" << std::endl;

	std::tm from = {};
	from.tm_year = 2024 - 1900;
	from.tm_mon = 0;   // Januar
	from.tm_mday = 1;
	from.tm_isdst = -1;

	std::tm to = {};
	to.tm_year = 2024 - 1900;
	to.tm_mon = 3;     // April
	to.tm_mday = 1;
	to.tm_isdst = -1;

	time_t fromDate = std::mktime(&from);
	time_t toDate = std::mktime(&to);

	PrintEveryAccountInDateRange(
	accountArray,
	numberOfAccounts,
	fromDate,
	toDate,
	summary);

	std::cout << std::endl << "--- Optional (integrated) ---" << std::endl;
	std::cout << "\n--- Optional: Bank Statistics ---\n";

	auto* stats = new BankStats{};

	accountList.ForEach(CollectBankStats, stats);

	PrintBankStats(*stats);


	/*
	 * Final Analysis:
	 *
	 * Find() has O(n) time complexity because it searches through the
	 * linked list sequentially until it finds a match or reaches the end.
	 * When searching for an account near the end, the number of comparisons
	 * is close to the total number of accounts. When searching for a
	 * non-existing account, it must compare all n accounts.
	 * This shows that the worst-case time complexity is O(n).
	 *
	 * The main difference between Every() and PrintEveryAccountInDateRange()
	 * is flexibility. Every() is a generic method that uses a callback
	 * to decide which accounts match the search criteria. This means
	 * it can be reused for different searches without modifying the method.
	 *
	 * PrintEveryAccountInDateRange() is designed specifically to find
	 * accounts within a date range. It is less flexible because the
	 * search criteria are fixed in the function itself.
	 */


	delete stats;
	delete[] accountArray;
	delete searchedAccounts2;
	return 0;
}
