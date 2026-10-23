#include "../Data_structures_h//AVL.hpp"

#include <algorithm>
#include <iostream>

using namespace std;

// Constructor
AVL::AVL() {
    raiz = nullptr;
}

// Constructor de copia: realiza una copia profunda
AVL::AVL(const AVL& otro) {
    raiz = copiar(otro.raiz);
}

// Operador de asignación: evita compartir nodos entre árboles
AVL& AVL::operator=(const AVL& otro) {
    if (this != &otro) {
        NodoAVL* nuevaRaiz = copiar(otro.raiz);

        liberar(raiz);
        raiz = nuevaRaiz;
    }

    return *this;
}

// Destructor
AVL::~AVL() {
    clear();
}

// ========================================
// ALTURA Y FACTOR DE BALANCE
// ========================================

int AVL::altura(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }

    return nodo->getAltura();
}

int AVL::factorBalance(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }

    return altura(nodo->getIzquierdo())
         - altura(nodo->getDerecho());
}

// ========================================
// ROTACION SIMPLE A LA DERECHA
// Caso LL
// ========================================

NodoAVL* AVL::rotacionDerecha(NodoAVL* nodo) {
    NodoAVL* nuevoPadre = nodo->getIzquierdo();
    NodoAVL* subarbol = nuevoPadre->getDerecho();

    nuevoPadre->setDerecho(nodo);
    nodo->setIzquierdo(subarbol);

    nodo->setAltura(
        1 + max(
            altura(nodo->getIzquierdo()),
            altura(nodo->getDerecho())
        )
    );

    nuevoPadre->setAltura(
        1 + max(
            altura(nuevoPadre->getIzquierdo()),
            altura(nuevoPadre->getDerecho())
        )
    );

    return nuevoPadre;
}

// ========================================
// ROTACION SIMPLE A LA IZQUIERDA
// Caso RR
// ========================================

NodoAVL* AVL::rotacionIzquierda(NodoAVL* nodo) {
    NodoAVL* nuevoPadre = nodo->getDerecho();
    NodoAVL* subarbol = nuevoPadre->getIzquierdo();

    nuevoPadre->setIzquierdo(nodo);
    nodo->setDerecho(subarbol);

    nodo->setAltura(
        1 + max(
            altura(nodo->getIzquierdo()),
            altura(nodo->getDerecho())
        )
    );

    nuevoPadre->setAltura(
        1 + max(
            altura(nuevoPadre->getIzquierdo()),
            altura(nuevoPadre->getDerecho())
        )
    );

    return nuevoPadre;
}

// ========================================
// BALANCEAR UN NODO
// Incluye LL, RR, LR y RL
// ========================================

NodoAVL* AVL::balancear(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return nullptr;
    }

    nodo->setAltura(
        1 + max(
            altura(nodo->getIzquierdo()),
            altura(nodo->getDerecho())
        )
    );

    int balance = factorBalance(nodo);

    // Caso LL o LR: el lado izquierdo está pesado
    if (balance > 1) {
        if (factorBalance(nodo->getIzquierdo()) < 0) {
            // Caso LR: primero rotar a la izquierda
            nodo->setIzquierdo(
                rotacionIzquierda(nodo->getIzquierdo())
            );
        }

        // Caso LL o segunda rotación del caso LR
        return rotacionDerecha(nodo);
    }

    // Caso RR o RL: el lado derecho está pesado
    if (balance < -1) {
        if (factorBalance(nodo->getDerecho()) > 0) {
            // Caso RL: primero rotar a la derecha
            nodo->setDerecho(
                rotacionDerecha(nodo->getDerecho())
            );
        }

        // Caso RR o segunda rotación del caso RL
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

// ========================================
// INSERTAR
// El ID es la clave de ordenamiento
// ========================================

bool AVL::insertar(const Paciente& paciente) {
    bool insertado = false;

    raiz = insertar(raiz, paciente, insertado);

    return insertado;
}

NodoAVL* AVL::insertar(
    NodoAVL* nodo,
    const Paciente& paciente,
    bool& insertado
) {
    if (nodo == nullptr) {
        insertado = true;
        return new NodoAVL(paciente);
    }

    string idNuevo = paciente.getId();
    string idActual = nodo->getPaciente().getId();

    if (idNuevo < idActual) {
        nodo->setIzquierdo(
            insertar(
                nodo->getIzquierdo(),
                paciente,
                insertado
            )
        );
    }
    else if (idNuevo > idActual) {
        nodo->setDerecho(
            insertar(
                nodo->getDerecho(),
                paciente,
                insertado
            )
        );
    }
    else {
        // No se aceptan IDs duplicados
        return nodo;
    }

    return balancear(nodo);
}

// ========================================
// BUSCAR POR ID
// ========================================

const Paciente* AVL::buscarPorId(
    const string& id
) const {
    return buscarPorId(raiz, id);
}

const Paciente* AVL::buscarPorId(
    NodoAVL* nodo,
    const string& id
) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    string idActual = nodo->getPaciente().getId();

    if (id == idActual) {
        return &nodo->getPaciente();
    }

    if (id < idActual) {
        return buscarPorId(
            nodo->getIzquierdo(),
            id
        );
    }

    return buscarPorId(
        nodo->getDerecho(),
        id
    );
}

// ========================================
// BUSCAR POR NOMBRE
// Se revisan ambos subárboles porque el
// árbol está ordenado por ID, no por nombre.
// ========================================

const Paciente* AVL::buscarPorNombre(
    const string& nombre
) const {
    return buscarPorNombre(raiz, nombre);
}

const Paciente* AVL::buscarPorNombre(
    NodoAVL* nodo,
    const string& nombre
) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    if (nodo->getPaciente().getNombre() == nombre) {
        return &nodo->getPaciente();
    }

    const Paciente* encontrado = buscarPorNombre(
        nodo->getIzquierdo(),
        nombre
    );

    if (encontrado != nullptr) {
        return encontrado;
    }

    return buscarPorNombre(
        nodo->getDerecho(),
        nombre
    );
}

// ========================================
// ENCONTRAR EL MENOR NODO
// ========================================

NodoAVL* AVL::minimo(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    while (nodo->getIzquierdo() != nullptr) {
        nodo = nodo->getIzquierdo();
    }

    return nodo;
}

// ========================================
// ELIMINAR POR ID
// ========================================

bool AVL::eliminarPorId(const string& id) {
    bool eliminado = false;

    raiz = eliminar(raiz, id, eliminado);

    return eliminado;
}

NodoAVL* AVL::eliminar(
    NodoAVL* nodo,
    const string& id,
    bool& eliminado
) {
    if (nodo == nullptr) {
        return nullptr;
    }

    string idActual = nodo->getPaciente().getId();

    if (id < idActual) {
        nodo->setIzquierdo(
            eliminar(
                nodo->getIzquierdo(),
                id,
                eliminado
            )
        );
    }
    else if (id > idActual) {
        nodo->setDerecho(
            eliminar(
                nodo->getDerecho(),
                id,
                eliminado
            )
        );
    }
    else {
        eliminado = true;

        // Caso 1: no tiene hijo izquierdo
        if (nodo->getIzquierdo() == nullptr) {
            NodoAVL* derecho = nodo->getDerecho();

            delete nodo;

            return derecho;
        }

        // Caso 2: no tiene hijo derecho
        if (nodo->getDerecho() == nullptr) {
            NodoAVL* izquierdo = nodo->getIzquierdo();

            delete nodo;

            return izquierdo;
        }

        // Caso 3: tiene dos hijos.
        // Se reemplaza por el menor del subárbol derecho.
        NodoAVL* sucesor = minimo(nodo->getDerecho());

        nodo->setPaciente(sucesor->getPaciente());

        bool eliminadoSucesor = false;

        nodo->setDerecho(
            eliminar(
                nodo->getDerecho(),
                sucesor->getPaciente().getId(),
                eliminadoSucesor
            )
        );
    }

    return balancear(nodo);
}

// ========================================
// COMPROBAR SI ESTA VACIO
// ========================================

bool AVL::empty() const {
    return raiz == nullptr;
}

// ========================================
// ALTURA DEL ARBOL COMPLETO
// ========================================

int AVL::altura() const {
    return altura(raiz);
}

// ========================================
// FACTOR DE BALANCE DE LA RAIZ
// ========================================

int AVL::factorBalance() const {
    return factorBalance(raiz);
}

// ========================================
// RECORRIDO INORDEN
// Izquierda - Raíz - Derecha
// ========================================

void AVL::inorden() const {
    inorden(raiz);
}

void AVL::inorden(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    inorden(nodo->getIzquierdo());

    const Paciente& paciente = nodo->getPaciente();

    cout << paciente.getId()
         << " - "
         << paciente.getNombre()
         << " ("
         << paciente.getEdad()
         << ")"
         << endl;

    inorden(nodo->getDerecho());
}

// ========================================
// RECORRIDO PREORDEN
// Raíz - Izquierda - Derecha
// ========================================

void AVL::preorden() const {
    preorden(raiz);
}

void AVL::preorden(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    const Paciente& paciente = nodo->getPaciente();

    cout << paciente.getId()
         << " - "
         << paciente.getNombre()
         << " ("
         << paciente.getEdad()
         << ")"
         << endl;

    preorden(nodo->getIzquierdo());
    preorden(nodo->getDerecho());
}

// ========================================
// RECORRIDO POSTORDEN
// Izquierda - Derecha - Raíz
// ========================================

void AVL::postorden() const {
    postorden(raiz);
}

void AVL::postorden(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    postorden(nodo->getIzquierdo());
    postorden(nodo->getDerecho());

    const Paciente& paciente = nodo->getPaciente();

    cout << paciente.getId()
         << " - "
         << paciente.getNombre()
         << " ("
         << paciente.getEdad()
         << ")"
         << endl;
}

// ========================================
// MOSTRAR FACTORES DE BALANCE
// ========================================

void AVL::mostrarFactoresBalance() const {
    mostrarFactoresBalance(raiz);
}

void AVL::mostrarFactoresBalance(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    mostrarFactoresBalance(nodo->getIzquierdo());

    cout << "ID: "
         << nodo->getPaciente().getId()
         << " | Factor de balance: "
         << factorBalance(nodo)
         << endl;

    mostrarFactoresBalance(nodo->getDerecho());
}

// ========================================
// COPIAR UN ARBOL COMPLETO
// ========================================

NodoAVL* AVL::copiar(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    NodoAVL* nuevo = new NodoAVL(nodo->getPaciente());

    nuevo->setAltura(nodo->getAltura());

    try {
        nuevo->setIzquierdo(
            copiar(nodo->getIzquierdo())
        );

        nuevo->setDerecho(
            copiar(nodo->getDerecho())
        );
    }
    catch (...) {
        liberar(nuevo);
        throw;
    }

    return nuevo;
}

// ========================================
// LIBERAR TODOS LOS NODOS
// ========================================

void AVL::liberar(NodoAVL* nodo) const{
    if (nodo == nullptr) {
        return;
    }

    liberar(nodo->getIzquierdo());
    liberar(nodo->getDerecho());

    delete nodo;
}

// ========================================
// VACIAR EL ARBOL
// ========================================

void AVL::clear() {
    liberar(raiz);
    raiz = nullptr;
}


void AVL::mostrarResumen() const {
    bool primero = true;
    mostrarResumen(raiz, primero);
}

void AVL::mostrarResumen(
    NodoAVL* nodo,
    bool& primero
) const {
    if (nodo == nullptr) {
        return;
    }

    mostrarResumen(nodo->getIzquierdo(), primero);

    if (!primero) {
        cout << ", ";
    }

    const Paciente& paciente = nodo->getPaciente();

    cout << paciente.getNombre()
         << " (" << paciente.getId() << ")";

    primero = false;

    mostrarResumen(nodo->getDerecho(), primero);
}

string AVL::rutaBusquedaPorId(const string& id) const {
    NodoAVL* cursor = raiz;
    string ruta;

    while (cursor != nullptr) {
        if (!ruta.empty()) {
            ruta += " -> ";
        }

        ruta += cursor->getPaciente().getId();

        string idActual = cursor->getPaciente().getId();

        if (id == idActual) {
            return ruta;
        }

        if (id < idActual) {
            cursor = cursor->getIzquierdo();
        }
        else {
            cursor = cursor->getDerecho();
        }
    }

    return "";
}