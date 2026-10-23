#pragma once

#include "NodoDecision.hpp"
#include <string>

class ArbolDecision {
private:
    NodoDecision* raiz;

    void construir();
    void liberar(NodoDecision* nodo);

    std::string evaluar(
        NodoDecision* nodo,
        const Paciente& paciente,
        std::string& ruta
    ) const;

    void inorden(NodoDecision* nodo) const;
    void preorden(NodoDecision* nodo) const;
    void postorden(NodoDecision* nodo) const;

public:
    ArbolDecision();
    ~ArbolDecision();

    ArbolDecision(const ArbolDecision&) = delete;
    ArbolDecision& operator=(const ArbolDecision&) = delete;

    std::string evaluarPaciente(
        const Paciente& paciente,
        std::string& ruta
    ) const;

    std::string evaluarPaciente(
        const Paciente& paciente
    ) const;

    void inorden() const;
    void preorden() const;
    void postorden() const;

    void clear();
};