//
// Created by krist on 06.11.2026.
//

#ifndef CONTEXTPOINTERS_HPP
#define CONTEXTPOINTERS_HPP

template <typename T>
class TDataAggregator {
private:
    T stateTotal = 0;
public:
    T GetStateTotal() {
        return stateTotal;
    }
    void Accumulate(T& val) {
        stateTotal += val;
        val *= 2;
    }
    static void StaticCallback(T& val, void* context) {
        auto aggregator = static_cast<TDataAggregator<T>*> (context);
        aggregator->Accumulate(val);
    }
};

template <typename T>
using FContextFunc = void(*)(T&, void*);

template <typename T>
void ProcessWithContext(T* arr, int size, FContextFunc<T> callback, void* context) {
    for (int i = 0; i < size; i++) {
        callback(arr[i], context);
    }
}
#endif //CONTEXTPOINTERS_HPP
