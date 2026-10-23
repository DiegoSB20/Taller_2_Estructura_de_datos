#include "../Data_structures_h//NodoAVL.hpp"

NodoAVL::NodoAVL(const Paciente& paciente) {
    this->paciente = paciente;
    this->izquierdo = nullptr;
    this->derecho = nullptr;
    this->altura = 1;
}

NodoAVL::~NodoAVL() {
}

const Paciente& NodoAVL::getPaciente() const {
    return this->paciente;
}

NodoAVL* NodoAVL::getIzquierdo() const {
    return this->izquierdo;
}

NodoAVL* NodoAVL::getDerecho() const {
    return this->derecho;
}

int NodoAVL::getAltura() const {
    return this->altura;
}

void NodoAVL::setPaciente(const Paciente& paciente) {
    this->paciente = paciente;
}

void NodoAVL::setIzquierdo(NodoAVL* izquierdo) {
    this->izquierdo = izquierdo;
}

void NodoAVL::setDerecho(NodoAVL* derecho) {
    this->derecho = derecho;
}

void NodoAVL::setAltura(int altura) {
    this->altura = altura;
}