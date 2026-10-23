#pragma once

#include <string>
#include "Paciente.hpp"
#include "../../Data_structures/Data_structures_h/AVL.hpp"

using namespace std;

class Servicio {
private:
    string nombreServicio;
    AVL arbolPacientes;

public:
    Servicio();
    Servicio(const string& nombreServicio);
    ~Servicio();

    string getNombreServicio() const;

    void setNombreServicio(const string& nombreServicio);

    AVL& getArbolPacientes();
    const AVL& getArbolPacientes() const;

    bool agregarPaciente(const Paciente& paciente);

    void mostrarPacientes() const;
};