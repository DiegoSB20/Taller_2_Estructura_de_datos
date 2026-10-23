#include "../../Data_structures/Data_structures_h/Node.hpp"

template <typename T>
Node<T>::Node(T value) {
    this->value = value;
    this->next = nullptr;
}

template <typename T>
T Node<T>::getValue() {
    return this->value;
}

template <typename T>
T& Node<T>::getValueReferencia() {
    return this->value;
}

template <typename T>
Node<T>* Node<T>::getNext() {
    return this->next;
}

template <typename T>
void Node<T>::setValue(T value) {
    this->value = value;
}

template <typename T>
void Node<T>::setNext(Node<T>* next) {
    this->next = next;
}

template <typename T>
Node<T>::~Node() {
}
