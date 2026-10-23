#include "../Data_structures_h//List.hpp"

// ========================================
// CONSTRUCTOR
// ========================================

template <typename T>
List<T>::List() {
    this->start = nullptr;
}

// ========================================
// CONSTRUCTOR DE COPIA
// Copia los elementos en nodos nuevos
// ========================================

template <typename T>
List<T>::List(const List<T>& otra) {
    this->start = nullptr;

    Node<T>* cursor = otra.start;

    try {
        while (cursor != nullptr) {
            this->insertLast(cursor->getValue());
            cursor = cursor->getNext();
        }
    }
    catch (...) {
        clear();
        throw;
    }
}

// ========================================
// OPERADOR DE ASIGNACION
// ========================================

template <typename T>
List<T>& List<T>::operator=(const List<T>& otra) {
    if (this != &otra) {
        List<T> copia(otra);

        Node<T>* temporal = this->start;
        this->start = copia.start;
        copia.start = temporal;
    }

    return *this;
}

// ========================================
// DESTRUCTOR
// ========================================

template <typename T>
List<T>::~List() {
    clear();
}

// ========================================
// COMPROBAR SI ESTA VACIA
// ========================================

template <typename T>
bool List<T>::empty() const {
    return this->start == nullptr;
}

// ========================================
// CANTIDAD DE ELEMENTOS
// ========================================

template <typename T>
int List<T>::size() const {
    int cantidad = 0;
    Node<T>* cursor = this->start;

    while (cursor != nullptr) {
        cantidad++;
        cursor = cursor->getNext();
    }

    return cantidad;
}

// ========================================
// INSERTAR EN UNA POSICION
// Los indices comienzan en cero
// ========================================

template <typename T>
void List<T>::insert(T value, int index) {
    if (index < 0 || index > size()) {
        throw 0;
    }

    if (index == 0) {
        insertFirst(value);
        return;
    }

    Node<T>* cursor = this->start;

    for (int i = 0; i < index - 1; i++) {
        cursor = cursor->getNext();
    }

    Node<T>* nuevo = new Node<T>(value);

    nuevo->setNext(cursor->getNext());
    cursor->setNext(nuevo);
}

// ========================================
// INSERTAR AL PRINCIPIO
// ========================================

template <typename T>
void List<T>::insertFirst(T value) {
    Node<T>* nuevo = new Node<T>(value);

    nuevo->setNext(this->start);
    this->start = nuevo;
}

// ========================================
// INSERTAR AL FINAL
// ========================================

template <typename T>
void List<T>::insertLast(T value) {
    Node<T>* nuevo = new Node<T>(value);

    if (this->start == nullptr) {
        this->start = nuevo;
        return;
    }

    Node<T>* cursor = this->start;

    while (cursor->getNext() != nullptr) {
        cursor = cursor->getNext();
    }

    cursor->setNext(nuevo);
}

// ========================================
// OBTENER ELEMENTO POR INDICE
// Devuelve una copia
// ========================================

template <typename T>
T List<T>::get(int index) const {
    if (index < 0 || this->start == nullptr) {
        throw 0;
    }

    Node<T>* cursor = this->start;

    for (int i = 0; i < index; i++) {
        cursor = cursor->getNext();

        if (cursor == nullptr) {
            throw 0;
        }
    }

    return cursor->getValue();
}

// ========================================
// OBTENER REFERENCIA POR INDICE
// Permite modificar el elemento
// ========================================

template <typename T>
T& List<T>::getReferencia(int index) {
    if (index < 0 || this->start == nullptr) {
        throw 0;
    }

    Node<T>* cursor = this->start;

    for (int i = 0; i < index; i++) {
        cursor = cursor->getNext();

        if (cursor == nullptr) {
            throw 0;
        }
    }

    return cursor->getValueReferencia();
}

// ========================================
// OBTENER PRIMER ELEMENTO
// ========================================

template <typename T>
T List<T>::getFirst() const {
    if (this->start == nullptr) {
        throw 0;
    }

    return this->start->getValue();
}

// ========================================
// OBTENER ULTIMO ELEMENTO
// ========================================

template <typename T>
T List<T>::getLast() const {
    if (this->start == nullptr) {
        throw 0;
    }

    Node<T>* cursor = this->start;

    while (cursor->getNext() != nullptr) {
        cursor = cursor->getNext();
    }

    return cursor->getValue();
}

// ========================================
// ELIMINAR POR INDICE
// ========================================

template <typename T>
void List<T>::remove(int index) {
    if (index < 0 || this->start == nullptr) {
        throw 0;
    }

    if (index == 0) {
        Node<T>* eliminar = this->start;

        this->start = this->start->getNext();

        delete eliminar;
        return;
    }

    Node<T>* cursor = this->start;

    for (int i = 0; i < index - 1; i++) {
        cursor = cursor->getNext();

        if (cursor == nullptr) {
            throw 0;
        }
    }

    Node<T>* eliminar = cursor->getNext();

    if (eliminar == nullptr) {
        throw 0;
    }

    cursor->setNext(eliminar->getNext());

    delete eliminar;
}

// ========================================
// LIBERAR TODOS LOS NODOS
// ========================================

template <typename T>
void List<T>::clear() {
    while (this->start != nullptr) {
        Node<T>* temporal = this->start;

        this->start = this->start->getNext();

        delete temporal;
    }
}