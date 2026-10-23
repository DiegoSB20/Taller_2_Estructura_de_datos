#pragma once
#include "Node.hpp"

template <typename T>
class Stack {
private:
    Node<T>* top;
public:
    Stack();
    ~Stack();

    void push(T value);
    T pop();

    T peek();
    bool empty();
    void clear();
};

#include "../Data_structures_cpp/Stack.cpp"
