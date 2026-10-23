#include "../Data_structures_h//ArbolDecision.hpp"

#include <iostream>

using namespace std;

ArbolDecision::ArbolDecision() {
    raiz = nullptr;
    construir();
}

ArbolDecision::~ArbolDecision() {
    clear();
}

// ========================================
// CONSTRUIR EL ARBOL DE DECISION
// Izquierdo = SI
// Derecho = NO
// ========================================

void ArbolDecision::construir() {
    raiz = new NodoDecision(
        CriterioDecision::EDAD_MENOR_14
    );

    // Edad < 14
    raiz->setIzquierdo(
        new NodoDecision("Pediatría")
    );

    NodoDecision* trauma =
        new NodoDecision(CriterioDecision::TRAUMA);

    raiz->setDerecho(trauma);

    // Si existe trauma, evaluar si requiere cirugía.
    NodoDecision* cirugia =
        new NodoDecision(CriterioDecision::REQUIERE_CIRUGIA);

    trauma->setIzquierdo(cirugia);

    cirugia->setIzquierdo(
        new NodoDecision("Cirugía")
    );

    cirugia->setDerecho(
        new NodoDecision("Traumatología")
    );

    // Si no existe trauma, evaluar síntomas neurológicos.
    NodoDecision* neurologia =
        new NodoDecision(
            CriterioDecision::SINTOMAS_NEUROLOGICOS
        );

    trauma->setDerecho(neurologia);

    neurologia->setIzquierdo(
        new NodoDecision("Neurología")
    );

    // Si no hay síntomas neurológicos, evaluar dolor de pecho.
    NodoDecision* dolorPecho =
        new NodoDecision(
            CriterioDecision::DOLOR_PECHO
        );

    neurologia->setDerecho(dolorPecho);

    dolorPecho->setIzquierdo(
        new NodoDecision("Cardiología")
    );

    // Si el dolor no es de pecho, evaluar urgencia.
    NodoDecision* urgencia =
        new NodoDecision(CriterioDecision::URGENCIA);

    dolorPecho->setDerecho(urgencia);

    urgencia->setIzquierdo(
        new NodoDecision("Urgencias")
    );

    // Si no es una urgencia, evaluar hospitalización.
    NodoDecision* hospitalizacion =
        new NodoDecision(
            CriterioDecision::HOSPITALIZACION
        );

    urgencia->setDerecho(hospitalizacion);

    hospitalizacion->setIzquierdo(
        new NodoDecision("Hospitalización")
    );

    hospitalizacion->setDerecho(
        new NodoDecision("Medicina General")
    );
}

// ========================================
// EVALUAR UN PACIENTE
// ========================================

string ArbolDecision::evaluarPaciente(
    const Paciente& paciente,
    string& ruta
) const {
    ruta.clear();

    return evaluar(raiz, paciente, ruta);
}

string ArbolDecision::evaluarPaciente(
    const Paciente& paciente
) const {
    string ruta;

    return evaluarPaciente(paciente, ruta);
}

string ArbolDecision::evaluar(
    NodoDecision* nodo,
    const Paciente& paciente,
    string& ruta
) const {
    if (nodo == nullptr) {
        return "";
    }

    if (nodo->esHoja()) {
        return nodo->getServicio();
    }

    bool resultado = nodo->evaluarCondicion(paciente);
    string descripcion;

    switch (nodo->getCriterio()) {
        case CriterioDecision::EDAD_MENOR_14:
            descripcion = resultado
                ? "Edad < 14"
                : "Edad >= 14";
            break;

        case CriterioDecision::TRAUMA:
            descripcion = resultado
                ? "Trauma == 1"
                : "Trauma == 0";
            break;

        case CriterioDecision::REQUIERE_CIRUGIA:
            descripcion = resultado
                ? "RequiereCirugia == 1"
                : "RequiereCirugia == 0";
            break;

        case CriterioDecision::SINTOMAS_NEUROLOGICOS:
            descripcion = resultado
                ? "SintomasNeurologicos == 1"
                : "SintomasNeurologicos == 0";
            break;

        case CriterioDecision::DOLOR_PECHO:
            descripcion = resultado
                ? "TipoDolor == pecho"
                : "TipoDolor != pecho";
            break;

        case CriterioDecision::URGENCIA:
            descripcion = resultado
                ? "Temperatura >= 38.5 o Dolor >= 8"
                : "Temperatura < 38.5 y Dolor < 8";
            break;

        case CriterioDecision::HOSPITALIZACION:
            descripcion = resultado
                ? "DiasHospitalizacion >= 2"
                : "DiasHospitalizacion < 2";
            break;

        case CriterioDecision::HOJA:
            break;
    }

    if (!ruta.empty()) {
        ruta += " -> ";
    }

    ruta += descripcion;

    if (resultado) {
        return evaluar(
            nodo->getIzquierdo(),
            paciente,
            ruta
        );
    }

    return evaluar(
        nodo->getDerecho(),
        paciente,
        ruta
    );
}

// ========================================
// RECORRIDO INORDEN
// ========================================

void ArbolDecision::inorden() const {
    inorden(raiz);
}

void ArbolDecision::inorden(NodoDecision* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    inorden(nodo->getIzquierdo());

    cout << nodo->getDescripcion() << endl;

    inorden(nodo->getDerecho());
}

// ========================================
// RECORRIDO PREORDEN
// ========================================

void ArbolDecision::preorden() const {
    preorden(raiz);
}

void ArbolDecision::preorden(NodoDecision* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    cout << nodo->getDescripcion() << endl;

    preorden(nodo->getIzquierdo());
    preorden(nodo->getDerecho());
}

// ========================================
// RECORRIDO POSTORDEN
// ========================================

void ArbolDecision::postorden() const {
    postorden(raiz);
}

void ArbolDecision::postorden(NodoDecision* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    postorden(nodo->getIzquierdo());
    postorden(nodo->getDerecho());

    cout << nodo->getDescripcion() << endl;
}

// ========================================
// LIBERAR MEMORIA
// ========================================

void ArbolDecision::liberar(NodoDecision* nodo) {
    if (nodo == nullptr) {
        return;
    }

    liberar(nodo->getIzquierdo());
    liberar(nodo->getDerecho());

    delete nodo;
}

void ArbolDecision::clear() {
    liberar(raiz);
    raiz = nullptr;
}