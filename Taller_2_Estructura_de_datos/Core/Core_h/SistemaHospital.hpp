#pragma once

#include <string>

#include "../../Data_structures/Data_structures_h/Queue.hpp"
#include "../../Data_structures/Data_structures_h/Stack.hpp"
#include "../../Data_structures/Data_structures_h/List.hpp"
#include "../../Data_structures/Data_structures_h/ArbolDecision.hpp"

#include "../../Clases/Clases_h/Paciente.hpp"
#include "../../Clases/Clases_h/Atencion.hpp"
#include "../../Clases/Clases_h/Servicio.hpp"

#include "CargarArchivo.hpp"

using namespace std;

class SistemaHospital {
private:
    Queue<Paciente> colaEspera;
    Stack<Atencion> historialAtenciones;
    List<Servicio> servicios;

    CargaArchivo cargador;
    ArbolDecision arbolDecision;

    void inicializarServicios();

    Servicio* buscarServicio(const string& nombreServicio);

    bool buscarEnColaPorId(
        const string& id,
        Paciente& pacienteEncontrado
    );

    bool buscarEnColaPorNombre(
        const string& nombre,
        Paciente& pacienteEncontrado
    );

    bool existePacienteEnSistema(const string& id);

public:
    SistemaHospital();
    ~SistemaHospital();

    bool cargarDatos(const string& rutaArchivo);

    void mostrarColaEspera();
    void atenderPacientes(int cantidad = -1);
    void buscarPaciente(const string& consulta);

    void mostrarDepartamentos();
    void verDepartamento(int opcion);

    void buscarPacientePorId(const string& id);
    void buscarPacientePorNombre(const string& nombre);

    bool eliminarPacientePorId(const string& id);

    void mostrarRecorridoDepartamento(
        int opcion,
        int tipoRecorrido
    );

    void mostrarEstadisticasDepartamento(int opcion);

    void mostrarRecorridoArbolDecision(int tipoRecorrido);

    void mostrarHistorial();
};