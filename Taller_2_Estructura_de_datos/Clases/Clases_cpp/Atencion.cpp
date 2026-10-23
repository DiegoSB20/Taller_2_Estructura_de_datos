#include "../Clases_h/Atencion.hpp"
#include <iostream>

using namespace std;

Atencion::Atencion() {
    idPaciente = "";
    nombrePaciente = "";
    edadPaciente = 0;
    servicio = "";
}

Atencion::Atencion(const Paciente& paciente) {
    idPaciente = paciente.getId();
    nombrePaciente = paciente.getNombre();
    edadPaciente = paciente.getEdad();
    servicio = paciente.getServicioDestino();
}

Atencion::Atencion(
    const string& id,
    const string& nombre,
    int edad,
    const string& servicio
) {
    idPaciente = id;
    nombrePaciente = nombre;
    edadPaciente = edad;
    this->servicio = servicio;
}

Atencion::~Atencion() {
}

string Atencion::getIdPaciente() const {
    return idPaciente;
}

string Atencion::getNombrePaciente() const {
    return nombrePaciente;
}

int Atencion::getEdadPaciente() const {
    return edadPaciente;
}

string Atencion::getServicio() const {
    return servicio;
}

void Atencion::mostrarDetalle() const {
    cout << "Nombre: " << nombrePaciente
         << " | Edad: " << edadPaciente
         << " | Departamento: " << servicio
         << endl;
}