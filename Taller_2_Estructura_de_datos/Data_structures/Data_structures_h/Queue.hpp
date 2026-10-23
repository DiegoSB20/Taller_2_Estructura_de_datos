#pragma once
#include "Node.hpp"

template <typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
public:
    Queue();
    ~Queue();

    void enqueue(T value);
    T dequeue();
    T peek();

    bool empty();
    void clear();
};

#include "../Data_structures_cpp/Queue.cpp"