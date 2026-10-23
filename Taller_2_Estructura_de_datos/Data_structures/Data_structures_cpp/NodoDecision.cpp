#include "../Data_structures_h//NodoDecision.hpp"

#include <algorithm>
#include <cctype>

using namespace std;

NodoDecision::NodoDecision(CriterioDecision criterio) {
    this->criterio = criterio;
    this->servicio = "";

    this->izquierdo = nullptr;
    this->derecho = nullptr;
}

NodoDecision::NodoDecision(const string& servicio) {
    this->criterio = CriterioDecision::HOJA;
    this->servicio = servicio;

    this->izquierdo = nullptr;
    this->derecho = nullptr;
}

NodoDecision::~NodoDecision() {
    // ArbolDecision administra la memoria de los nodos.
}

bool NodoDecision::esHoja() const {
    return criterio == CriterioDecision::HOJA;
}

CriterioDecision NodoDecision::getCriterio() const {
    return criterio;
}

const string& NodoDecision::getServicio() const {
    return servicio;
}

NodoDecision* NodoDecision::getIzquierdo() const {
    return izquierdo;
}

NodoDecision* NodoDecision::getDerecho() const {
    return derecho;
}

void NodoDecision::setIzquierdo(NodoDecision* izquierdo) {
    this->izquierdo = izquierdo;
}

void NodoDecision::setDerecho(NodoDecision* derecho) {
    this->derecho = derecho;
}

// Normaliza el texto para aceptar, por ejemplo,
// "Pecho", "pecho" y " pecho ".
static string normalizarTexto(const string& texto) {
    string resultado = texto;

    while (!resultado.empty() &&
           isspace(static_cast<unsigned char>(resultado.front()))) {
        resultado.erase(resultado.begin());
    }

    while (!resultado.empty() &&
           isspace(static_cast<unsigned char>(resultado.back()))) {
        resultado.pop_back();
    }

    transform(
        resultado.begin(),
        resultado.end(),
        resultado.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        }
    );

    return resultado;
}

bool NodoDecision::evaluarCondicion(
    const Paciente& paciente
) const {
    switch (criterio) {
        case CriterioDecision::EDAD_MENOR_14:
            return paciente.getEdad() < 14;

        case CriterioDecision::TRAUMA:
            return paciente.getTrauma();

        case CriterioDecision::REQUIERE_CIRUGIA:
            return paciente.getRequiereCirugia();

        case CriterioDecision::SINTOMAS_NEUROLOGICOS:
            return paciente.getSintomasNeurologicos();

        case CriterioDecision::DOLOR_PECHO:
            return normalizarTexto(
                paciente.getTipoDolor()
            ) == "pecho";

        case CriterioDecision::URGENCIA:
            return paciente.getTemperatura() >= 38.5 ||
                   paciente.getDolor() >= 8;

        case CriterioDecision::HOSPITALIZACION:
            return paciente.getDiasHospitalizacion() >= 2;

        case CriterioDecision::HOJA:
            return false;
    }

    return false;
}

string NodoDecision::getDescripcion() const {
    switch (criterio) {
        case CriterioDecision::EDAD_MENOR_14:
            return "Edad < 14";

        case CriterioDecision::TRAUMA:
            return "Trauma == 1";

        case CriterioDecision::REQUIERE_CIRUGIA:
            return "RequiereCirugia == 1";

        case CriterioDecision::SINTOMAS_NEUROLOGICOS:
            return "SintomasNeurologicos == 1";

        case CriterioDecision::DOLOR_PECHO:
            return "TipoDolor == pecho";

        case CriterioDecision::URGENCIA:
            return "Temperatura >= 38.5 o Dolor >= 8";

        case CriterioDecision::HOSPITALIZACION:
            return "DiasHospitalizacion >= 2";

        case CriterioDecision::HOJA:
            return "Servicio: " + servicio;
    }

    return "Criterio desconocido";
}