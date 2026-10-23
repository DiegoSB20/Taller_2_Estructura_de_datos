#include "../Clases_h//Servicio.hpp"
#include <iostream>

using namespace std;

Servicio::Servicio() {
    nombreServicio = "";
}

Servicio::Servicio(const string& nombreServicio) {
    this->nombreServicio = nombreServicio;
}

Servicio::~Servicio() {
}

string Servicio::getNombreServicio() const {
    return nombreServicio;
}

void Servicio::setNombreServicio(
    const string& nombreServicio
) {
    this->nombreServicio = nombreServicio;
}

AVL& Servicio::getArbolPacientes() {
    return arbolPacientes;
}

const AVL& Servicio::getArbolPacientes() const {
    return arbolPacientes;
}

bool Servicio::agregarPaciente(const Paciente& paciente) {
    return arbolPacientes.insertar(paciente);
}

void Servicio::mostrarPacientes() const {
    cout << "=== ESTADO " << nombreServicio << " ==="
         << endl;

    if (arbolPacientes.empty()) {
        cout << "No hay pacientes en el departamento."
             << endl;
        return;
    }

    cout << "Pacientes ordenados por ID:" << endl;

    arbolPacientes.inorden();
}