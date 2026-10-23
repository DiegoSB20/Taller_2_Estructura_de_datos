#include "../Core_h//SistemaHospital.hpp"

#include <iostream>
#include <iomanip>
using namespace std;

// ========================================
// CONSTRUCTOR Y DESTRUCTOR
// ========================================

SistemaHospital::SistemaHospital() {
    inicializarServicios();
}

SistemaHospital::~SistemaHospital() {
    // Los destructores de las estructuras miembro
    // liberan automáticamente su memoria.
}

// ========================================
// INICIALIZAR LOS OCHO SERVICIOS
// ========================================

void SistemaHospital::inicializarServicios() {
    servicios.insertLast(Servicio("Urgencias"));
    servicios.insertLast(Servicio("Medicina General"));
    servicios.insertLast(Servicio("Cardiología"));
    servicios.insertLast(Servicio("Neurología"));
    servicios.insertLast(Servicio("Traumatología"));
    servicios.insertLast(Servicio("Cirugía"));
    servicios.insertLast(Servicio("Pediatría"));
    servicios.insertLast(Servicio("Hospitalización"));
}

// ========================================
// BUSCAR SERVICIO POR NOMBRE
// ========================================

Servicio* SistemaHospital::buscarServicio(
    const string& nombreServicio
) {
    for (int i = 0; i < servicios.size(); i++) {
        Servicio& servicio = servicios.getReferencia(i);

        if (servicio.getNombreServicio() == nombreServicio) {
            return &servicio;
        }
    }

    return nullptr;
}

// ========================================
// BUSCAR UN ID EN LA COLA
// Se restaura el orden original.
// ========================================

bool SistemaHospital::buscarEnColaPorId(
    const string& id,
    Paciente& pacienteEncontrado
) {
    Queue<Paciente> auxiliar;
    bool encontrado = false;

    while (!colaEspera.empty()) {
        Paciente paciente = colaEspera.dequeue();

        if (!encontrado && paciente.getId() == id) {
            pacienteEncontrado = paciente;
            encontrado = true;
        }

        auxiliar.enqueue(paciente);
    }

    while (!auxiliar.empty()) {
        colaEspera.enqueue(auxiliar.dequeue());
    }

    return encontrado;
}

// ========================================
// BUSCAR UN NOMBRE EN LA COLA
// Se restaura el orden original.
// ========================================

bool SistemaHospital::buscarEnColaPorNombre(
    const string& nombre,
    Paciente& pacienteEncontrado
) {
    Queue<Paciente> auxiliar;
    bool encontrado = false;

    while (!colaEspera.empty()) {
        Paciente paciente = colaEspera.dequeue();

        if (!encontrado && paciente.getNombre() == nombre) {
            pacienteEncontrado = paciente;
            encontrado = true;
        }

        auxiliar.enqueue(paciente);
    }

    while (!auxiliar.empty()) {
        colaEspera.enqueue(auxiliar.dequeue());
    }

    return encontrado;
}

// ========================================
// COMPROBAR ID EN TODO EL SISTEMA
// Cola de espera y los ocho AVL.
// ========================================

bool SistemaHospital::existePacienteEnSistema(
    const string& id
) {
    Paciente paciente;

    if (buscarEnColaPorId(id, paciente)) {
        return true;
    }

    for (int i = 0; i < servicios.size(); i++) {
        Servicio& servicio = servicios.getReferencia(i);

        if (servicio.getArbolPacientes().buscarPorId(id)
            != nullptr) {
            return true;
        }
    }

    return false;
}

// ========================================
// CARGAR DATOS
// ========================================

bool SistemaHospital::cargarDatos(
    const string& rutaArchivo
) {
    cargador.setRutaArchivo(rutaArchivo);

    // Cargar primero a una cola temporal.
    // Así podemos comprobar IDs contra todo el hospital.
    Queue<Paciente> nuevosPacientes;

    if (!cargador.cargarPacientes(nuevosPacientes)) {
        return false;
    }

    int agregados = 0;
    int duplicados = 0;

    while (!nuevosPacientes.empty()) {
        Paciente paciente = nuevosPacientes.dequeue();

        if (existePacienteEnSistema(paciente.getId())) {
            cout << "Paciente duplicado en el sistema. ID: "
                 << paciente.getId()
                 << endl;

            duplicados++;
            continue;
        }

        colaEspera.enqueue(paciente);
        agregados++;
    }

    //cout << "Pacientes agregados a la cola: "
    //     << agregados << endl;

    if (duplicados > 0) {
        cout << "Pacientes rechazados por ID duplicado: "
             << duplicados << endl;
    }

    return true;
}

// ========================================
// MOSTRAR COLA DE ESPERA
// ========================================

void SistemaHospital::mostrarColaEspera() {
    if (colaEspera.empty()) {
        cout << "No hay pacientes en espera." << endl;
        return;
    }

    Queue<Paciente> auxiliar;
    int posicion = 1;

    cout << "=== PACIENTES EN ESPERA ===" << endl;

    while (!colaEspera.empty()) {
        Paciente paciente = colaEspera.dequeue();

        cout << posicion << ". ID: "
             << paciente.getId()
             << " | Nombre: "
             << paciente.getNombre()
             << " | Edad: "
             << paciente.getEdad()
             << endl;

        auxiliar.enqueue(paciente);
        posicion++;
    }

    // Restaurar la cola en el orden original.
    while (!auxiliar.empty()) {
        colaEspera.enqueue(auxiliar.dequeue());
    }
}

// ========================================
// ATENDER PACIENTES
// Queue -> ArbolDecision -> Servicio -> AVL
// ========================================

void SistemaHospital::atenderPacientes(int cantidad) {
    if (cantidad == 0 || cantidad < -1) {
        cout << "La cantidad debe ser mayor que cero."
             << endl;
        return;
    }

    if (colaEspera.empty()) {
        cout << "No hay pacientes para atender." << endl;
        return;
    }

    int atendidos = 0;

    while (!colaEspera.empty() &&
           (cantidad == -1 || atendidos < cantidad)) {

        Paciente paciente = colaEspera.dequeue();

        string ruta;
        string nombreServicio =
            arbolDecision.evaluarPaciente(paciente, ruta);

        if (nombreServicio.empty()) {
            cout << "No se pudo clasificar al paciente."
                 << endl;

            colaEspera.enqueue(paciente);
            break;
        }

        paciente.setServicioDestino(nombreServicio);

        Servicio* servicio = buscarServicio(nombreServicio);

        if (servicio == nullptr) {
            cout << "Servicio no valido: "
                 << nombreServicio << endl;

            colaEspera.enqueue(paciente);
            continue;
        }

        if (!servicio->agregarPaciente(paciente)) {
            cout << "No se pudo insertar el paciente "
                 << paciente.getId() << endl;
            continue;
        }

        cout << "ID: " << paciente.getId() << endl;
        cout << "Nombre: " << paciente.getNombre() << endl;
        cout << "Edad: " << paciente.getEdad() << endl;

        cout << fixed << setprecision(1);
        cout << "Temperatura: "
             << paciente.getTemperatura() << endl;

        cout.unsetf(ios::floatfield);
        cout << "Dolor: " << paciente.getDolor() << endl;
        cout << "TipoDolor: "
             << paciente.getTipoDolor() << endl;

        cout << "Trauma: "
             << (paciente.getTrauma() ? 1 : 0) << endl;

        cout << "SintomasNeurologicos: "
             << (paciente.getSintomasNeurologicos() ? 1 : 0)
             << endl;

        cout << "RequiereCirugia: "
             << (paciente.getRequiereCirugia() ? 1 : 0)
             << endl;

        cout << "DiasHospitalizacion: "
             << paciente.getDiasHospitalizacion() << endl;

        cout << "Ruta: " << ruta << endl;

        cout << "Servicio asignado: "
             << nombreServicio << endl;

        cout << "Paciente insertado en el AVL de "
             << nombreServicio << "." << endl;

        historialAtenciones.push(Atencion(paciente));

        atendidos++;
    }
}

// ========================================
// MOSTRAR DEPARTAMENTOS
// ========================================

void SistemaHospital::mostrarDepartamentos() {
    cout << "=== ESTADO DE LOS DEPARTAMENTOS ==="
         << endl;

    for (int i = 0; i < servicios.size(); i++) {
        Servicio& servicio = servicios.getReferencia(i);

        cout << servicio.getNombreServicio() << endl;

        const AVL& arbol = servicio.getArbolPacientes();

        if (arbol.empty()) {
            cout << "Sin pacientes" << endl;
        }
        else {
            cout << "Pacientes: ";
            arbol.mostrarResumen();
            cout << endl;
        }
    }
}

// ========================================
// VER DEPARTAMENTO Y SU AVL
// ========================================

void SistemaHospital::verDepartamento(int opcion) {
    if (opcion < 1 || opcion > servicios.size()) {
        cout << "Opcion de departamento invalida."
             << endl;
        return;
    }

    Servicio& servicio =
        servicios.getReferencia(opcion - 1);

    cout << "\n=== DEPARTAMENTO: "
         << servicio.getNombreServicio()
         << " ===" << endl;

    servicio.mostrarPacientes();

    const AVL& arbol = servicio.getArbolPacientes();

    cout << "Altura del AVL: "
         << arbol.altura() << endl;

    cout << "Factor de balance de la raiz: "
         << arbol.factorBalance() << endl;

    if (!arbol.empty()) {
        cout << "\nFactores de balance de los nodos:"
             << endl;

        arbol.mostrarFactoresBalance();
    }
}

// ========================================
// BUSCAR PACIENTE POR ID
// Busca en los ocho AVL y en la cola.
// ========================================

void SistemaHospital::buscarPacientePorId(
    const string& id
) {
    for (int i = 0; i < servicios.size(); i++) {
        Servicio& servicio = servicios.getReferencia(i);

        const Paciente* paciente =
            servicio.getArbolPacientes().buscarPorId(id);

        if (paciente != nullptr) {
            cout << "\n=== PACIENTE ENCONTRADO ==="
                 << endl;

            paciente->mostrarInformacion();

            cout << "\nDepartamento: "
                 << servicio.getNombreServicio()
                 << endl;

            return;
        }
    }

    Paciente pacienteEnCola;

    if (buscarEnColaPorId(id, pacienteEnCola)) {
        cout << "\nPaciente encontrado en la cola de espera."
             << endl;

        pacienteEnCola.mostrarInformacion();

        cout << "\nTodavia no ha sido asignado a un servicio."
             << endl;

        return;
    }

    cout << "No se encontro un paciente con ID: "
         << id << endl;
}

// ========================================
// BUSCAR PACIENTE POR NOMBRE
// ========================================

void SistemaHospital::buscarPacientePorNombre(
    const string& nombre
) {
    bool encontrado = false;

    for (int i = 0; i < servicios.size(); i++) {
        Servicio& servicio = servicios.getReferencia(i);

        const Paciente* paciente =
            servicio.getArbolPacientes().buscarPorNombre(nombre);

        if (paciente != nullptr) {
            cout << "\n=== PACIENTE ENCONTRADO ==="
                 << endl;

            paciente->mostrarInformacion();

            cout << "\nDepartamento: "
                 << servicio.getNombreServicio()
                 << endl;

            encontrado = true;
        }
    }

    Paciente pacienteEnCola;

    if (buscarEnColaPorNombre(nombre, pacienteEnCola)) {
        cout << "\nPaciente encontrado en la cola de espera:"
             << endl;

        pacienteEnCola.mostrarInformacion();

        encontrado = true;
    }

    if (!encontrado) {
        cout << "No se encontro un paciente llamado: "
             << nombre << endl;
    }
}

// ========================================
// ELIMINAR PACIENTE POR ID
// La eliminacion se ejecuta sobre el AVL.
// ========================================

bool SistemaHospital::eliminarPacientePorId(
    const string& id
) {
    for (int i = 0; i < servicios.size(); i++) {
        Servicio& servicio = servicios.getReferencia(i);

        if (servicio.getArbolPacientes().eliminarPorId(id)) {
            cout << "Paciente " << id
                 << " eliminado del AVL de "
                 << servicio.getNombreServicio()
                 << "." << endl;

            return true;
        }
    }

    Paciente pacienteEnCola;

    if (buscarEnColaPorId(id, pacienteEnCola)) {
        cout << "El paciente esta en la cola de espera y "
             << "todavia no pertenece a un AVL."
             << endl;

        return false;
    }

    cout << "No existe un paciente con ID: "
         << id << endl;

    return false;
}

// ========================================
// RECORRER EL AVL DE UN DEPARTAMENTO
// tipoRecorrido: 1=inorden, 2=preorden, 3=postorden
// ========================================

void SistemaHospital::mostrarRecorridoDepartamento(
    int opcion,
    int tipoRecorrido
) {
    if (opcion < 1 || opcion > servicios.size()) {
        cout << "Opcion de departamento invalida."
             << endl;
        return;
    }

    Servicio& servicio =
        servicios.getReferencia(opcion - 1);

    const AVL& arbol = servicio.getArbolPacientes();

    if (arbol.empty()) {
        cout << "El departamento no tiene pacientes."
             << endl;
        return;
    }

    cout << "\n=== RECORRIDO DE "
         << servicio.getNombreServicio()
         << " ===" << endl;

    switch (tipoRecorrido) {
        case 1:
            cout << "INORDEN:" << endl;
            arbol.inorden();
            break;

        case 2:
            cout << "PREORDEN:" << endl;
            arbol.preorden();
            break;

        case 3:
            cout << "POSTORDEN:" << endl;
            arbol.postorden();
            break;

        default:
            cout << "Tipo de recorrido invalido."
                 << endl;
            break;
    }
}

// ========================================
// ALTURA Y FACTORES DE BALANCE
// ========================================

void SistemaHospital::mostrarEstadisticasDepartamento(
    int opcion
) {
    if (opcion < 1 || opcion > servicios.size()) {
        cout << "Opcion de departamento invalida."
             << endl;
        return;
    }

    Servicio& servicio =
        servicios.getReferencia(opcion - 1);

    const AVL& arbol = servicio.getArbolPacientes();

    cout << "\n=== ESTADISTICAS DEL AVL ===" << endl;
    cout << "Departamento: "
         << servicio.getNombreServicio() << endl;

    cout << "Altura: "
         << arbol.altura() << endl;

    cout << "Factor de balance de la raiz: "
         << arbol.factorBalance() << endl;

    if (arbol.empty()) {
        cout << "El arbol esta vacio." << endl;
        return;
    }

    cout << "\nFactor de balance por nodo:" << endl;
    arbol.mostrarFactoresBalance();
}

// ========================================
// RECORRIDOS DEL ARBOL DE DECISION
// tipoRecorrido: 1=inorden, 2=preorden, 3=postorden
// ========================================

void SistemaHospital::mostrarRecorridoArbolDecision(
    int tipoRecorrido
) {
    cout << "\n=== ARBOL DE DECISION ===" << endl;

    switch (tipoRecorrido) {
        case 1:
            cout << "INORDEN:" << endl;
            arbolDecision.inorden();
            break;

        case 2:
            cout << "PREORDEN:" << endl;
            arbolDecision.preorden();
            break;

        case 3:
            cout << "POSTORDEN:" << endl;
            arbolDecision.postorden();
            break;

        default:
            cout << "Tipo de recorrido invalido."
                 << endl;
            break;
    }
}

// ========================================
// MOSTRAR HISTORIAL DE ATENCIONES
// Se conserva la pila original.
// ========================================

void SistemaHospital::mostrarHistorial() {
    cout << "\n=== HISTORIAL DE ATENCIONES ==="
         << endl;

    if (historialAtenciones.empty()) {
        cout << "No hay atenciones registradas."
             << endl;
        return;
    }

    Stack<Atencion> auxiliar;

    while (!historialAtenciones.empty()) {
        Atencion atencion = historialAtenciones.pop();

        atencion.mostrarDetalle();

        auxiliar.push(atencion);
    }

    // Restaurar el historial original.
    while (!auxiliar.empty()) {
        historialAtenciones.push(auxiliar.pop());
    }
}


void SistemaHospital::buscarPaciente(
    const string& consulta
) {
    const Paciente* encontrado = nullptr;
    string departamento;
    string ruta;

    // Primero, buscar por ID en los ocho AVL.
    for (int i = 0; i < servicios.size(); i++) {
        Servicio& servicio = servicios.getReferencia(i);

        const Paciente* paciente =
            servicio.getArbolPacientes().buscarPorId(consulta);

        if (paciente != nullptr) {
            encontrado = paciente;
            departamento = servicio.getNombreServicio();

            ruta = servicio.getArbolPacientes()
                           .rutaBusquedaPorId(consulta);
            break;
        }
    }

    // Si no se encontró por ID, buscar por nombre.
    if (encontrado == nullptr) {
        for (int i = 0; i < servicios.size(); i++) {
            Servicio& servicio = servicios.getReferencia(i);

            const Paciente* paciente =
                servicio.getArbolPacientes()
                        .buscarPorNombre(consulta);

            if (paciente != nullptr) {
                encontrado = paciente;
                departamento = servicio.getNombreServicio();
                ruta = "Busqueda por nombre en el AVL";
                break;
            }
        }
    }

    if (encontrado == nullptr) {
        cout << "Paciente no encontrado." << endl;
        return;
    }

    cout << "Paciente encontrado:" << endl;
    cout << "-------" << endl;

    cout << "ID: " << encontrado->getId() << endl;
    cout << "Nombre: " << encontrado->getNombre() << endl;
    cout << "Edad: " << encontrado->getEdad() << endl;

    cout << "Departamento: " << departamento << endl;

    cout << fixed << setprecision(1);
    cout << "T: " << encontrado->getTemperatura() << "°";

    cout.unsetf(ios::floatfield);

    cout << " | D: " << encontrado->getDolor();
    cout << " | TD: " << encontrado->getTipoDolor();

    cout << " | T: "
         << (encontrado->getTrauma() ? "Si" : "No");

    cout << " | SN: "
         << (encontrado->getSintomasNeurologicos()
             ? "Si" : "No");

    cout << " | RC: "
         << (encontrado->getRequiereCirugia()
             ? "Si" : "No");

    cout << " | DH: ";

    if (encontrado->getDiasHospitalizacion() == 0) {
        cout << "Ninguno";
    }
    else {
        cout << encontrado->getDiasHospitalizacion();
    }

    cout << endl;
    cout << "-------" << endl;
    cout << endl;

    cout << "Ruta de busqueda:" << endl;
    cout << ruta << endl;
}