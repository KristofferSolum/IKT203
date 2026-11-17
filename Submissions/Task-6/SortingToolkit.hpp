#pragma once
#include "../Task-5/TBankAccount.h"
#include "../Task-5/TLinkedList.hpp"

namespace Sorting {
    typedef int (*FCompareAccounts)(TBankAccount* a, TBankAccount* b);
}

inline int CompareByLastName(TBankAccount* a, TBankAccount* b) {
    return a->GetOwnerLastName().compare(b->GetOwnerLastName());
}

inline int CompareByBalance(TBankAccount* a, TBankAccount* b) {
    if (a->GetBalance() < b->GetBalance()) {
        return -1;
    }
    if (a->GetBalance() > b->GetBalance()) {
        return 1;
    }
    return 0;
}


struct OperationSummary {
    long long comparisons;
    long long swaps;
    double timeSpentMs;
};

class TSort {
private:
    TLinkedList<TBankAccount>* list;
    TBankAccount** accountArray;
    int arraySize;
    void QuickSortRecursive(TBankAccount** arr, int low, int high, Sorting::FCompareAccounts compare, OperationSummary& summary);
    int Partition(TBankAccount** arr, int low, int high, Sorting::FCompareAccounts compare, OperationSummary& summary);
    TNode<TBankAccount>* MergeSortRecursive(TNode<TBankAccount>* head, Sorting::FCompareAccounts compare, OperationSummary& summary);
    TNode<TBankAccount>* Merge(TNode<TBankAccount>* left, TNode<TBankAccount>* right, Sorting::FCompareAccounts compare, OperationSummary& summary);
    TBankAccount** sortedArray = nullptr;
    bool isSorted = false;
    TBankAccount* BinarySearchRecursive(int left, int right, TBankAccount* searchKey, Sorting::FCompareAccounts compare, OperationSummary& summary);

public:
    TSort(TLinkedList<TBankAccount>* list,TBankAccount** accountArray,int arraySize)
        : list(list), accountArray(accountArray), arraySize(arraySize) {}
    ~TSort() {delete[] sortedArray;}
    TBankAccount** SelectionSortArray(Sorting::FCompareAccounts compare, OperationSummary& summary);
    TLinkedList<TBankAccount>* SelectionSortList(Sorting::FCompareAccounts compare, OperationSummary& summary);
    TBankAccount** BubbleSortArray(Sorting::FCompareAccounts compare, OperationSummary& summary);
    TBankAccount** QuickSort(Sorting::FCompareAccounts compare, OperationSummary& summary);
    TLinkedList<TBankAccount>* MergeSortList(Sorting::FCompareAccounts compare, OperationSummary& summary);
    TBankAccount* BinarySearch(TBankAccount* searchKey, Sorting::FCompareAccounts compare, OperationSummary& summary);
};

inline TBankAccount** TSort::SelectionSortArray(Sorting::FCompareAccounts compare, OperationSummary& summary) {
    /*
     * Selection Sort (Array)
     *
     * Time Complexity:
     * Best:    O(n^2)
     * Average: O(n^2)
     * Worst:   O(n^2)
     *
     * Selection Sort always searches the remaining unsorted
     * elements to find the smallest value, regardless of
     * whether the array is already sorted.
     *
     * Space Complexity:
     * Best:    O(n)
     * Average: O(n)
     * Worst:   O(n)
     *
     * The sorting algorithm itself uses O(1) extra space,
     * but O(n) space is required to copy the pointer array.
     */
    const auto start = std::chrono::steady_clock::now();
    TBankAccount** sortedArray = new TBankAccount*[arraySize];
    summary.comparisons = 0;
    summary.swaps = 0;

    for (int i = 0; i < arraySize; i++) {
        sortedArray[i] = accountArray[i];
    }

    for (int i = 0; i < arraySize - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < arraySize; j++) {
            summary.comparisons++;

            if (compare(sortedArray[j], sortedArray[minIndex]) < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            TBankAccount* temp = sortedArray[i];
            sortedArray[i] = sortedArray[minIndex];
            sortedArray[minIndex] = temp;

            summary.swaps++;
        }
    }

    const auto end = std::chrono::steady_clock::now();
    summary.timeSpentMs = std::chrono::duration<double, std::milli>(end - start).count();
    return sortedArray;
}

inline void CopyAccountToList(TBankAccount* account, void* context) {
    auto* targetList =
        static_cast<TLinkedList<TBankAccount>*>(context);

    targetList->Append(account);
}

inline TLinkedList<TBankAccount>* TSort::SelectionSortList(Sorting::FCompareAccounts compare,OperationSummary& summary) {
    /*
     * Selection Sort (Linked List)
     *
     * Time Complexity:
     * Best:    O(n^2)
     * Average: O(n^2)
     * Worst:   O(n^2)
     *
     * The algorithm traverses the unsorted part of the list
     * to find the smallest node in each iteration.
     * Nodes are moved by updating their next pointers.
     *
     * Space Complexity:
     * Best:    O(n)
     * Average: O(n)
     * Worst:   O(n)
     *
     * Sorting only requires O(1) space,
     * but O(n) space is used to create a new linked list
     * containing pointers to the original accounts.
     */
    const auto start = std::chrono::steady_clock::now();

    summary.comparisons = 0;
    summary.swaps = 0;

    auto* sortedList = new TLinkedList<TBankAccount>(false);
    list->ForEach(CopyAccountToList, sortedList);

    TNode<TBankAccount>* previous = sortedList->GetHead();

    while (previous->GetNext() != nullptr) {
        TNode<TBankAccount>* minPrevious = previous;
        TNode<TBankAccount>* currentPrevious = previous->GetNext();

        while (currentPrevious->GetNext() != nullptr) {
            summary.comparisons++;

            if (compare(
                currentPrevious->GetNext()->GetData(),
                minPrevious->GetNext()->GetData()
            ) < 0) {
                minPrevious = currentPrevious;
            }

            currentPrevious = currentPrevious->GetNext();
        }

        if (minPrevious != previous) {
            TNode<TBankAccount>* minNode = minPrevious->GetNext();

            minPrevious->SetNext(minNode->GetNext());

            minNode->SetNext(previous->GetNext());
            previous->SetNext(minNode);

            summary.swaps++;
        }

        previous = previous->GetNext();
    }

    sortedList->SetTail(previous);

    const auto end = std::chrono::steady_clock::now();
    summary.timeSpentMs = std::chrono::duration<double, std::milli>(end - start).count();

    return sortedList;
}

inline TBankAccount** TSort::BubbleSortArray(Sorting::FCompareAccounts compare, OperationSummary& summary) {
    /*
     * Bubble Sort (Array)
     *
     * Time Complexity:
     * Best:    O(n)
     * Average: O(n^2)
     * Worst:   O(n^2)
     *
     * In the best case, the array is already sorted and
     * the swapped flag allows the algorithm to stop
     * after the first pass.
     *
     * Space Complexity:
     * Best:    O(n)
     * Average: O(n)
     * Worst:   O(n)
     *
     * Bubble Sort uses O(1) space,
     * but copying the pointer array requires O(n) space.
     */
    const auto start = std::chrono::steady_clock::now();

    summary.comparisons = 0;
    summary.swaps = 0;

    TBankAccount** sortedArray = new TBankAccount*[arraySize];

    for (int i = 0; i < arraySize; i++) {
        sortedArray[i] = accountArray[i];
    }


    for (int i = 0; i < arraySize - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < arraySize - i - 1; j++) {
            summary.comparisons++;

            if (compare(sortedArray[j], sortedArray[j + 1]) > 0) {
                TBankAccount* temp = sortedArray[j];
                sortedArray[j] = sortedArray[j + 1];
                sortedArray[j + 1] = temp;

                summary.swaps++;
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }

    const auto end = std::chrono::steady_clock::now();

    summary.timeSpentMs =
        std::chrono::duration<double, std::milli>(end - start).count();

    return sortedArray;
}

inline int TSort::Partition(TBankAccount** arr, int low, int high, Sorting::FCompareAccounts compare, OperationSummary& summary) {
    TBankAccount* pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        summary.comparisons++;

        if (compare(arr[j], pivot) <= 0) {
            i++;

            if (i != j) {
                TBankAccount* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;

                summary.swaps++;
            }
        }
    }

    if (i + 1 != high) {
        TBankAccount* temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        summary.swaps++;
    }

    return i + 1;
}

inline void TSort::QuickSortRecursive(TBankAccount** arr, int low, int high, Sorting::FCompareAccounts compare, OperationSummary& summary) {
    if (low >= high)
        return;

    int pivotIndex = Partition(arr, low, high, compare, summary);
    QuickSortRecursive(arr, low, pivotIndex - 1, compare, summary);
    QuickSortRecursive(arr, pivotIndex + 1, high, compare, summary);
}

inline TBankAccount** TSort::QuickSort(Sorting::FCompareAccounts compare, OperationSummary& summary) {
    /*
     * Quick Sort
     *
     * Time Complexity:
     * Best:    O(n log n)
     * Average: O(n log n)
     * Worst:   O(n^2)
     *
     * Quick Sort partitions the array around a pivot
     * and recursively sorts the two partitions.
     * The worst case occurs when partitions are highly
     * unbalanced, for example when many values are equal.
     *
     * Space Complexity (total):
     * Best:    O(n)
     * Average: O(n)
     * Worst:   O(n)
     *
     * Recursion requires O(log n) space in the best and
     * average cases, and O(n) in the worst case.
     * The implementation also stores two pointer arrays,
     * each requiring O(n) space, so total space is O(n).
     */
    const auto start = std::chrono::steady_clock::now();
    summary.comparisons = 0;
    summary.swaps = 0;

    TBankAccount** sortedArray = new TBankAccount*[arraySize];

    for (int i = 0; i < arraySize; i++) {
        sortedArray[i] = accountArray[i];
    }

    QuickSortRecursive(sortedArray, 0,arraySize - 1, compare, summary);

    const auto end = std::chrono::steady_clock::now();
    summary.timeSpentMs =std::chrono::duration<double, std::milli>(end - start).count();

    delete[] this->sortedArray;

    this->sortedArray = new TBankAccount*[arraySize];

    for (int i = 0; i < arraySize; i++) {
        this->sortedArray[i] = sortedArray[i];
    }

    this->isSorted = true;
    return sortedArray;
}

inline TLinkedList<TBankAccount> *TSort::MergeSortList(Sorting::FCompareAccounts compare, OperationSummary &summary) {
    /*
     * Merge Sort 
     *
     * Time Complexity:
     * Best:    O(n log n)
     * Average: O(n log n)
     * Worst:   O(n log n)
     *
     * The list is recursively divided into two halves.
     * The sorted halves are merged by rearranging
     * node pointers using the comparison callback.
     *
     * Space Complexity:
     * Best:    O(n)
     * Average: O(n)
     * Worst:   O(n)
     *
     * The recursive calls require O(log n) stack space.
     * Creating a new linked list requires O(n) space,
     * while merging the existing nodes uses O(1)
     * additional space per merge operation.
     */

    const auto start = std::chrono::steady_clock::now();
    summary.comparisons = 0;
    summary.swaps = 0;

    auto* sortedList = new TLinkedList<TBankAccount>(false);

    TNode<TBankAccount>* current = list->GetHead()->GetNext();

    while (current != nullptr) {
        sortedList->Append(current->GetData());
        current = current->GetNext();
    }

    TNode<TBankAccount>* dummy = sortedList->GetHead();
    TNode<TBankAccount>* sortedHead = MergeSortRecursive(dummy->GetNext(), compare, summary);
    dummy->SetNext(sortedHead);
    TNode<TBankAccount>* currentTail = dummy;

    while (currentTail->GetNext() != nullptr) {
        currentTail = currentTail->GetNext();
    }
    sortedList->SetTail(currentTail);

    const auto end = std::chrono::steady_clock::now();
    summary.timeSpentMs = std::chrono::duration<double, std::milli>(end - start).count();

    return sortedList;
}


inline TNode<TBankAccount>* TSort::MergeSortRecursive(TNode<TBankAccount>* head, Sorting::FCompareAccounts compare, OperationSummary& summary) {
    if (head == nullptr || head->GetNext() == nullptr) {
        return head;
    }

    TNode<TBankAccount>* slow = head;
    TNode<TBankAccount>* fast = head->GetNext();

    while (fast != nullptr && fast->GetNext() != nullptr) {
        slow = slow->GetNext();
        fast = fast->GetNext()->GetNext();
    }

    TNode<TBankAccount>* right = slow->GetNext();
    slow->SetNext(nullptr);

    TNode<TBankAccount>* leftSorted =
        MergeSortRecursive(head, compare, summary);

    TNode<TBankAccount>* rightSorted =
        MergeSortRecursive(right, compare, summary);

    return Merge(leftSorted, rightSorted, compare, summary);
}


inline TNode<TBankAccount>* TSort::Merge(TNode<TBankAccount>* left, TNode<TBankAccount>* right, Sorting::FCompareAccounts compare, OperationSummary& summary) {
    TNode<TBankAccount> dummy(nullptr);
    TNode<TBankAccount>* tail = &dummy;

    while (left != nullptr && right != nullptr) {
        summary.comparisons++;

        if (compare(left->GetData(), right->GetData()) <= 0) {
            tail->SetNext(left);
            left = left->GetNext();
        }
        else {
            tail->SetNext(right);
            right = right->GetNext();
        }

        tail = tail->GetNext();
        summary.swaps++;
    }

    if (left != nullptr) {
        tail->SetNext(left);
    }
    else {
        tail->SetNext(right);
    }

    return dummy.GetNext();
}

inline TBankAccount* TSort::BinarySearchRecursive(int left, int right, TBankAccount* searchKey, Sorting::FCompareAccounts compare, OperationSummary& summary) {
    if (left > right) {
        return nullptr;
    }

    int mid = left + (right - left) / 2;

    summary.comparisons++;

    int result = compare(sortedArray[mid], searchKey);

    if (result == 0) {
        return sortedArray[mid];
    }

    if (result > 0) {
        return BinarySearchRecursive(left, mid - 1, searchKey, compare, summary);
    }

    return BinarySearchRecursive(mid + 1, right, searchKey, compare, summary);
}

inline TBankAccount* TSort::BinarySearch(TBankAccount* searchKey, Sorting::FCompareAccounts compare, OperationSummary& summary) {
    summary.comparisons = 0;
    summary.swaps = 0;
    summary.timeSpentMs = 0;

    if (!isSorted || sortedArray == nullptr || searchKey == nullptr) {
        return nullptr;
    }

    const auto start = std::chrono::steady_clock::now();

    TBankAccount* result = BinarySearchRecursive(0,arraySize - 1,searchKey,compare,summary);

    const auto end = std::chrono::steady_clock::now();
    summary.timeSpentMs = std::chrono::duration<double, std::milli>(end - start).count();

    return result;
}
