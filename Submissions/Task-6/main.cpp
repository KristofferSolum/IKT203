#include <iostream>
#include "SortingToolkit.hpp"
#include "../Task-5/TBankAccount.h"
#include "../Task-5/TLinkedList.hpp"
#include "../Task-5/PopulateList.h"
#include "../Task-5/StandaloneSearch.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <string>


void PrintSortResult(const std::string& name,
					 const OperationSummary& summary) {
	std::cout << std::left << std::setw(25) << name
			  << std::right << std::setw(18) << summary.comparisons
			  << std::setw(18) << summary.swaps
			  << std::setw(18) << std::fixed
			  << std::setprecision(3) << summary.timeSpentMs
			  << '\n';
}


int main()
{
	TLinkedList<TBankAccount> accountList(true);
	TBankAccount** accountArray = new TBankAccount*[10000];
	auto numberOfAccounts = PopulateAccount(&accountList, accountArray);


	if (numberOfAccounts < 5000) {
		std::cerr << "Error: Dataset must contain at least 5000 accounts.\n";
		delete[] accountArray;
		return 1;
	}

	TSort sorter(&accountList, accountArray, numberOfAccounts);

	OperationSummary selectionArraySummary{};
	OperationSummary selectionListSummary{};
	OperationSummary bubbleSummary{};
	OperationSummary quickSummary{};
	OperationSummary mergeSummary{};

	// Run all sorting algorithms with the same callback
	TBankAccount** selectionArray =
		sorter.SelectionSortArray(CompareByLastName, selectionArraySummary);

	TLinkedList<TBankAccount>* selectionList =
		sorter.SelectionSortList(CompareByLastName, selectionListSummary);

	TBankAccount** bubbleArray =
		sorter.BubbleSortArray(CompareByLastName, bubbleSummary);

	TBankAccount** quickArray =
		sorter.QuickSort(CompareByLastName, quickSummary);

	TLinkedList<TBankAccount>* mergeList =
		sorter.MergeSortList(CompareByLastName, mergeSummary);


	std::cout << "\n--- Sorting Performance Comparison ---\n";
	std::cout << "Accounts: " << numberOfAccounts << "\n\n";

	std::cout << std::left << std::setw(25) << "Algorithm"
			  << std::right << std::setw(18) << "Comparisons"
			  << std::setw(18) << "Swaps/Moves"
			  << std::setw(18) << "Time (ms)"
			  << '\n';

	std::cout << std::string(79, '-') << '\n';

	PrintSortResult("Selection Sort Array", selectionArraySummary);
	PrintSortResult("Selection Sort List", selectionListSummary);
	PrintSortResult("Bubble Sort Array", bubbleSummary);
	PrintSortResult("Quick Sort Array", quickSummary);
	PrintSortResult("Merge Sort List", mergeSummary);

	/*
	* Part 4 - Performance Analysis
	*
	* The sorting algorithms were tested on the same dataset of
	* 5003 bank accounts using the same comparison callback.
	*
	* Algorithm                  Comparisons    Swaps/Moves    Time (ms)
	* Selection Sort Array         12512503          4849        7571.350
	* Selection Sort List          12512503          4858        8069.246
	* Bubble Sort Array           12472033       5984295        8180.732
	* Quick Sort Array              481092         16614         311.763
	* Merge Sort List                50809         50809          34.877
	*
	* The results demonstrate the difference between O(n^2) and
	* O(n log n) complexity. Selection Sort and Bubble Sort required
	* around 12.5 million comparisons, while Quick Sort and Merge Sort
	* required significantly fewer comparisons and execution time.
	*
	* Selection Sort was harder to implement on a linked list because
	* you cannot access elements directly using an index. Instead,
	* you have to traverse nodes using next pointers and manipulate
	* these pointers to move nodes without breaking the list.
	* You also need to update the tail pointer after sorting.
	*/

	TBankAccount* searchAccount = accountArray[numberOfAccounts - 5];
	std::string lastName = searchAccount->GetOwnerLastName();

	SearchSummary linearSummary{};
	OperationSummary binarySummary{};

	TBankAccount* linearResult = FindAccountByLastName(accountArray, numberOfAccounts, lastName, linearSummary);

	TBankAccount* binaryResult = sorter.BinarySearch(searchAccount, CompareByLastName, binarySummary);


	std::cout << "\n--- Search Performance Comparison ---\n";

	std::cout << std::left << std::setw(30) << "Algorithm"
			  << std::right << std::setw(18) << "Comparisons"
			  << std::setw(18) << "Time (ms)" << '\n';

	std::cout << std::string(66, '-') << '\n';

	std::cout << std::left << std::setw(30) << "Linear Search"
			  << std::right << std::setw(18) << linearSummary.comparisons
			  << std::setw(18) << linearSummary.timeSpentMs << '\n';

	std::cout << std::left << std::setw(30) << "Binary Search"
			  << std::right << std::setw(18) << binarySummary.comparisons
			  << std::setw(18) << binarySummary.timeSpentMs << '\n';

	std::cout << std::left << std::setw(30) << "Quick Sort + Binary Search"
			  << std::right << std::setw(18)
			  << quickSummary.comparisons + binarySummary.comparisons
			  << std::setw(18)
			  << quickSummary.timeSpentMs + binarySummary.timeSpentMs
			  << '\n';


	/*
	 * Part 5 - Integrated Binary Search Analysis
	 *
	 * Search Performance Results:
	 *
	 * Algorithm                   Comparisons    Time (ms)
	 * Linear Search                      106        0.036
	 * Binary Search                        2        0.002
	 * Quick Sort + Binary Search       493290      324.796
	 *
	 * Linear Search has O(n) time complexity because it checks
	 * each account sequentially until a match is found.
	 *
	 * Binary Search has O(log n) time complexity because it
	 * eliminates approximately half of the remaining search
	 * interval after each comparison.
	 *
	 * In this test, Binary Search required only 2 comparisons,
	 * while Linear Search required 106 comparisons.
	 *
	 * However, Binary Search requires a sorted array.
	 * When including the cost of Quick Sort, the total number
	 * of comparisons increased to 493290, making Linear Search
	 * more efficient for this single search.
	 *
	 * For repeated searches on the same dataset, Binary Search
	 * becomes more beneficial because sorting only needs to be
	 * performed once.
	 */

	delete[] selectionArray;
	delete selectionList;
	delete[] bubbleArray;
	delete[] quickArray;
	delete mergeList;
	delete[] accountArray;

	return 0;
}
