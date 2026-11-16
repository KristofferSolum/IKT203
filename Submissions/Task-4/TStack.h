//
// Created by krist on 07.11.2026.
//

#ifndef TSTACK_H
#define TSTACK_H
#define MAX_SIZE 12'000

class TStack {
private:
    int values[MAX_SIZE];
    int top_idx = -1;

public:
    void Push(int item);
    int Pop();
    int Peek();
    bool IsEmpty();
};



#endif //TSTACK_H
