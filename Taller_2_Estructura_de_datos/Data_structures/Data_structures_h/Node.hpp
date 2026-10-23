#pragma once

template <typename T>
class Node {
private:
    T value;
    Node<T>* next;

public:
    Node(T value);

    T getValue();
    T& getValueReferencia();
    Node<T>* getNext();

    void setValue(T value);
    void setNext(Node<T>* next);

    ~Node();
};

#include "../Data_structures_cpp/Node.cpp"