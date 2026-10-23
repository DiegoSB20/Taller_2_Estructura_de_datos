#pragma once

#include <string>
#include "../../Clases/Clases_h//Paciente.hpp"

enum class CriterioDecision {
    EDAD_MENOR_14,
    TRAUMA,
    REQUIERE_CIRUGIA,
    SINTOMAS_NEUROLOGICOS,
    DOLOR_PECHO,
    URGENCIA,
    HOSPITALIZACION,
    HOJA
};

class NodoDecision {
private:
    CriterioDecision criterio;
    std::string servicio;

    NodoDecision* izquierdo;
    NodoDecision* derecho;

public:
    explicit NodoDecision(CriterioDecision criterio);
    explicit NodoDecision(const std::string& servicio);

    ~NodoDecision();

    bool esHoja() const;

    CriterioDecision getCriterio() const;
    const std::string& getServicio() const;

    NodoDecision* getIzquierdo() const;
    NodoDecision* getDerecho() const;

    void setIzquierdo(NodoDecision* izquierdo);
    void setDerecho(NodoDecision* derecho);

    bool evaluarCondicion(const Paciente& paciente) const;
    std::string getDescripcion() const;
};