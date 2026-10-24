#pragma once

#include "SistemaHospital.hpp"
#include <string>

class SistemaHospital;

class Menu {
private:
    SistemaHospital sistema;

    void mostrarMenuPrincipal();
    void opcionAtender();
    void opcionVerDepartamentos();
    void opcionBuscarPaciente();

public:
    Menu();
    ~Menu();

    void iniciar();
};