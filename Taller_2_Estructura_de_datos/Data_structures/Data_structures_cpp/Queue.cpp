#include "../../Data_structures/Data_structures_h/Queue.hpp"
template <typename T>

Queue<T>::Queue() {
    this->front = nullptr;
    this->rear = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
    clear();
}

template <typename T>
void Queue<T>::enqueue(T value) {
    Node<T>* nuevo = new Node<T>(value);
    
    if (this->empty()) {
        this->front = nuevo;
        this->rear = nuevo;
    }
    else {
        this->rear->setNext(nuevo);
        this->rear = nuevo;
    }
}

template <typename T>
T Queue<T>::dequeue() {
    if (this->empty()) throw 0;

    Node<T>* toDelete = this->front;
    T valueToReturn = toDelete->getValue();
    this->front = this->front->getNext();

    if (this->front == nullptr) {
        this->rear = nullptr;
    }

    delete toDelete;
    return valueToReturn;
}

template <typename T>
T Queue<T>::peek() {
    if (this->empty()) throw 0;
    return this->front->getValue();
}

template <typename T>
bool Queue<T>::empty() {
    return this->front == nullptr;
}

template <typename T>
void Queue<T>::clear() {
    while (!this->empty()) {
        this->dequeue();
    }
}