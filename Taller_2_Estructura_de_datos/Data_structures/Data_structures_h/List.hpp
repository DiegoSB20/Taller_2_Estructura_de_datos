#pragma once

#include "Node.hpp"

template <typename T>
class List {
private:
    Node<T>* start;

public:
    List();
    List(const List<T>& otra);
    List<T>& operator=(const List<T>& otra);
    ~List();

    void insert(T value, int index);
    void insertFirst(T value);
    void insertLast(T value);

    T get(int index) const;
    T& getReferencia(int index);
    T getFirst() const;
    T getLast() const;

    void remove(int index);

    bool empty() const;
    int size() const;

    void clear();
};

#include "../Data_structures_cpp//List.cpp"