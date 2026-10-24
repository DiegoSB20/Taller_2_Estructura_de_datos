#include "../Core_h//Menu.hpp"

#include <iostream>
#include <limits>

using namespace std;

Menu::Menu() {
}

Menu::~Menu() {
}

void Menu::mostrarMenuPrincipal() {
    cout << "=== HOSPITAL MARMAJA ===" << endl;
    cout << "1. Atender pacientes" << endl;
    cout << "2. Ver departamentos" << endl;
    cout << "3. Buscar paciente" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccionar opcion: ";
}

void Menu::iniciar() {
    bool cargado = sistema.cargarDatos("Pacientes.txt");

    if (!cargado) {
        cargado = sistema.cargarDatos("../Pacientes.txt");
    }

    if (!cargado) {
        cout << "No se pudo cargar el archivo de pacientes."
             << endl;
    }

    int opcion = 0;
    int numeroOpcion = 2;
    //bool primeraVez = true;

    while (opcion != 4) {
        //if (!primeraVez) {
         //   cout << "------------------- Opción "
          //       << numeroOpcion
          //       << " -------------------"
          //       << endl;
        //}

        mostrarMenuPrincipal();

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Opcion invalida." << endl;
            continue;
        }

        switch (opcion) {
            case 1:
                opcionAtender();
                break;

            case 2:
                opcionVerDepartamentos();
                break;

            case 3:
                opcionBuscarPaciente();
                break;

            case 4:
                cout << "menu finalizado." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
                break;
        }

        if (opcion != 4) {
            //primeraVez = false;
            numeroOpcion++;
        }
    }
}

void Menu::opcionAtender() {
    cout << "=== ATENDIENDO PACIENTES ===" << endl;

    // Atender todos los pacientes que estén en la Queue.
    sistema.atenderPacientes();
}

void Menu::opcionVerDepartamentos() {
    sistema.mostrarDepartamentos();
}

void Menu::opcionBuscarPaciente() {
    cout << "=== BUSCAR PACIENTE ===" << endl;

    cout << "Indique el ID o Nombre del paciente: ";

    string consulta;

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    if (!getline(cin, consulta) || consulta.empty()) {
        cout << "Consulta invalida." << endl;
        return;
    }

    cout << "Buscando en AVL..." << endl;

    sistema.buscarPaciente(consulta);
}