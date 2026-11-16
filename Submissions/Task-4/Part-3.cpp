//
// Created by krist on 08.11.2026.
//
#include <random>
#include <iostream>
#include "Task-4.h"
#include "TQueue.h"
#include "TStack.h"
using namespace std;

struct GridSetup {
    int grid[100][100];
};

GridSetup setupGrid() {
    // Time: O(rows * cols), Space: O(rows * cols)
    // Initializes each cell with a random number and marks it as unvisited.
    GridSetup setup;
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 9);

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            setup.grid[i][j] = dist(rng);
        }
    }

    return setup;
}

int getIndex(int i, int j) {
    // Time: O(1), Space: O(1)
    // Converts a grid position (row, column) into a single index.
    return i * 100 + j;
}

struct Node {
    int row;
    int col;
};

Node getRowAndCol(int index) {
    // Time: O(1), Space: O(1)
    // Converts a single index into grid coordinates (row, column).
    Node node;
    node.row = index/100;
    node.col = index % 100;
    return node;
}

bool depthFirstSearch(
    GridSetup& setup,
    int startRow,
    int startCol,
    int target,
    bool explored[100][100],
    int& foundRow,
    int& foundCol) {
    // Time: O(rows * cols), Space: O(rows * cols)
    // Uses a stack to explore grid cells with depth-first search.
    TStack stack;
    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};
    bool visited[100][100] = {};

    if (startRow < 0 || startRow >= 100 || startCol < 0 || startCol >= 100) {
        throw std::invalid_argument("Invalid startRow or startCol");
    }
    stack.Push(getIndex(startRow, startCol));
    visited[startRow][startCol] = true;
    explored[startRow][startCol] = true;

    while (!stack.IsEmpty()) {
        Node node = getRowAndCol(stack.Pop());
        if (setup.grid[node.row][node.col] == target) {
            foundRow = node.row;
            foundCol = node.col;
            return true;
        }
        explored[node.row][node.col] = true;

        for (int i = 0; i < 4; i++) {
            int newRow = node.row + dRow[i];
            int newCol = node.col + dCol[i];
            if (newRow >= 0 && newRow < 100 &&
                newCol >= 0 && newCol < 100 &&
                !visited[newRow][newCol]) {
                stack.Push(getIndex(newRow, newCol));
                visited[newRow][newCol] = true;
            }
        }
    }
    return false;
}

bool breadthFirstSearch(
    GridSetup& setup,
    int startRow,
    int startCol,
    int target,
    bool explored[100][100],
    int& foundRow,
    int& foundCol) {
    // Time: O(rows * cols), Space: O(rows * cols)
    // Uses a queue to explore grid cells with breadth-first search.
    TQueue queue;
    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};
    bool visited[100][100] = {};

    if (startRow < 0 || startRow >= 100 || startCol < 0 || startCol >= 100) {
        throw std::invalid_argument("Invalid startRow or startCol");
    }

    queue.Enqueue(getIndex(startRow, startCol));
    visited[startRow][startCol] = true;
    explored[startRow][startCol] = true;

    while (!queue.IsEmpty()) {
        Node node = getRowAndCol(queue.Dequeue());
        if (setup.grid[node.row][node.col] == target) {
            foundRow = node.row;
            foundCol = node.col;
            return true;
        }
        explored[node.row][node.col] = true;

        for (int i = 0; i < 4; i++) {
            int newRow = node.row + dRow[i];
            int newCol = node.col + dCol[i];
            if (newRow >= 0 && newRow < 100 &&
                newCol >= 0 && newCol < 100 &&
                !visited[newRow][newCol]) {
                queue.Enqueue(getIndex(newRow, newCol));
                visited[newRow][newCol] = true;
            }
        }
    }
    return false;
}

void printGridTraversal(const bool explored[100][100], int startRow, int startCol, int foundRow, int foundCol) {
    // Time: O(1), Space: O(1)
    // Prints a fixed 20x20 section of the grid.
    int rowStart = max(0, min(startRow - 10, 80));
    int colStart = max(0, min(startCol - 10, 80));

    for (int row = rowStart; row < rowStart + 20; row++) {
        for (int col = colStart; col < colStart + 20; col++) {
            if (row == startRow && col == startCol) {
                cout << 'S';
            }
            else if (row == foundRow && col == foundCol) {
                cout << 'X';
            }
            else if (explored[row][col]) {
                cout << '1';
            }
            else {
                cout << '0';
            }
            cout << ' ';
        }

        cout << endl;
    }
}


void runPart3() {
    cout << "--- 7) Depth-First Search (DFS) with a Stack ---" << endl;
    // The stack uses LIFO, meaning the last added position is explored first.
    // This allows DFS to follow one path as far as possible until it reaches
    // a boundary or a position where all neighbours have been visited.
    // The search then backtracks to explore other available paths.
    GridSetup setup = setupGrid();
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 99);
    Node startNode;
    startNode.row = dist(rng);
    startNode.col = dist(rng);
    int target = 0;
    bool exploredDFS[100][100] = {};
    int foundRowDFS = -1;
    int foundColDFS = -1;
    try {
        if (depthFirstSearch(setup, startNode.row, startNode.col, target, exploredDFS, foundRowDFS, foundColDFS)) {
            cout << "Depth First Search Success!" << endl;
        }
        else {
            cout << "Depth First Search Failed!" << endl;
        }
    }
    catch (const std::exception& e) {
        cout <<"Error: " << e.what() << endl;
    }
    cout << endl << "--- DFS Traversal Grid ---" << endl;
    printGridTraversal(exploredDFS, startNode.row, startNode.col, foundRowDFS, foundColDFS);

    cout << "--- 8) Breadth-First Search (BFS) with a Queue ---" << endl;
    // The queue uses FIFO, meaning the first added position is explored first.
    // This allows BFS to traverse all positions near the starting point first,
    // exploring the grid level by level and finding the nearest target.
    bool exploredBFS[100][100] = {};
    int foundRowBFS = -1;
    int foundColBFS = -1;

    try {
        if (breadthFirstSearch(setup, startNode.row, startNode.col, target, exploredBFS, foundRowBFS, foundColBFS)) {
            cout << "Breadth First Search Success!" << endl;
        }
        else {
            cout << "Breadth First Search Failed!" << endl;
        }
    }
    catch (const std::exception& e) {
        cout <<"Error: " << e.what() << endl;
    }

    cout << endl << "--- BFS Traversal Grid ---" << endl;
    printGridTraversal(exploredBFS, startNode.row, startNode.col, foundRowBFS, foundColBFS);

    /*
    9)
    The main difference between DFS and BFS is how they explore the grid. DFS uses a stack (LIFO),
    while BFS uses a queue (FIFO). This means that DFS traverses one path as far as it can,
    while BFS goes through all the nearest positions to the starting point first.
    They might therefore find different positions or nodes for the target if there are multiple targets,
    with BFS finding the target that is the fewest steps away from the starting point
    and DFS finding the first target along its search path, which is not necessarily the closest.

    If you just need a way out of a labyrinth, you might want to use DFS because it could find a solution
    faster than BFS if it gets lucky with its starting path. However, DFS might also end up searching through
    many paths that do not lead to a solution. BFS, on the other hand, explores the labyrinth level by level
    to find the shortest path, which might require checking more positions before finding an exit.
    BFS can also require more memory because it may need to store many positions in its queue.
     */

}


