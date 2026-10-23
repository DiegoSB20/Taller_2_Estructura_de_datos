#pragma once

#include "../../Clases/Clases_h//Paciente.hpp"

class NodoAVL {
private:
    Paciente paciente;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

public:
    NodoAVL(const Paciente& paciente);
    ~NodoAVL();

    const Paciente& getPaciente() const;

    NodoAVL* getIzquierdo() const;
    NodoAVL* getDerecho() const;

    int getAltura() const;

    void setPaciente(const Paciente& paciente);
    void setIzquierdo(NodoAVL* izquierdo);
    void setDerecho(NodoAVL* derecho);
    void setAltura(int altura);
};