//
// Created by krist on 07.11.2026.
//

#ifndef TQUEUE_H
#define TQUEUE_H
#define MAX_SIZE 12'000



class TQueue {
private:
    int values[MAX_SIZE];
    int front_idx = -1;
    int back_idx = -1;
public:
    void Enqueue(int item);
    int Dequeue();
    int Peek();
    bool IsEmpty();
    bool IsFull();
};



#endif //TQUEUE_H
