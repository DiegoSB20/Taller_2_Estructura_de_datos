#pragma once

#include "Paciente.hpp"
#include <string>

using namespace std;

class Atencion {
private:
    string idPaciente;
    string nombrePaciente;
    int edadPaciente;
    string servicio;

public:
    Atencion();
    Atencion(const Paciente& paciente);
    Atencion(
        const string& id,
        const string& nombre,
        int edad,
        const string& servicio
    );

    ~Atencion();

    string getIdPaciente() const;
    string getNombrePaciente() const;
    int getEdadPaciente() const;
    string getServicio() const;

    void mostrarDetalle() const;
};