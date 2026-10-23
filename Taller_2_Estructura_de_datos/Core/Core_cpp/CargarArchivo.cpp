#include "../Core_h//CargarArchivo.hpp"
#include <filesystem>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>

using namespace std;

// ========================================
// FUNCIONES AUXILIARES
// ========================================

static string quitarEspacios(const string& texto) {
    size_t inicio = 0;
    size_t fin = texto.size();

    while (inicio < fin &&
           isspace(static_cast<unsigned char>(texto[inicio]))) {
        inicio++;
    }

    while (fin > inicio &&
           isspace(static_cast<unsigned char>(texto[fin - 1]))) {
        fin--;
    }

    return texto.substr(inicio, fin - inicio);
}

static string normalizarTexto(const string& texto) {
    string resultado = quitarEspacios(texto);

    for (size_t i = 0; i < resultado.size(); i++) {
        resultado[i] = static_cast<char>(
            tolower(static_cast<unsigned char>(resultado[i]))
        );
    }

    return resultado;
}

static bool convertirEntero(
    const string& texto,
    int& valor
) {
    try {
        size_t posicion = 0;

        int numero = stoi(texto, &posicion);

        if (posicion != texto.size()) {
            return false;
        }

        valor = numero;
        return true;
    }
    catch (...) {
        return false;
    }
}

static bool convertirDecimal(
    const string& texto,
    double& valor
) {
    try {
        size_t posicion = 0;

        double numero = stod(texto, &posicion);

        if (posicion != texto.size() || !isfinite(numero)) {
            return false;
        }

        valor = numero;
        return true;
    }
    catch (...) {
        return false;
    }
}

// Comprueba si el ID ya está en la Queue.
// La cola queda restaurada en el mismo orden.
static bool existePaciente(
    Queue<Paciente>& cola,
    const string& id
) {
    Queue<Paciente> auxiliar;
    bool encontrado = false;

    while (!cola.empty()) {
        Paciente paciente = cola.dequeue();

        if (paciente.getId() == id) {
            encontrado = true;
        }

        auxiliar.enqueue(paciente);
    }

    while (!auxiliar.empty()) {
        cola.enqueue(auxiliar.dequeue());
    }

    return encontrado;
}

// ========================================
// CONSTRUCTORES
// ========================================

CargaArchivo::CargaArchivo() {
    rutaArchivo = "Pacientes.txt";
}

CargaArchivo::CargaArchivo(const string& rutaArchivo) {
    this->rutaArchivo = rutaArchivo;
}

CargaArchivo::~CargaArchivo() {
}

// ========================================
// GETTERS Y SETTERS
// ========================================

string CargaArchivo::getRutaArchivo() const {
    return rutaArchivo;
}

void CargaArchivo::setRutaArchivo(const string& rutaArchivo) {
    this->rutaArchivo = rutaArchivo;
}

// ========================================
// SEPARAR CAMPOS POR ;
// ========================================

vector<string> CargaArchivo::separarCampos(
    const string& linea
) const {
    vector<string> campos;

    size_t inicio = 0;

    for (size_t i = 0; i <= linea.size(); i++) {
        if (i == linea.size() || linea[i] == ';') {
            string campo = linea.substr(inicio, i - inicio);

            campos.push_back(quitarEspacios(campo));

            inicio = i + 1;
        }
    }

    return campos;
}

// ========================================
// CARGAR PACIENTES
// ========================================

bool CargaArchivo::cargarPacientes(
    Queue<Paciente>& colaPacientes
) {
    cout << "Ruta recibida: " << rutaArchivo << endl;
    cout << "Directorio actual: "
         << filesystem::current_path() << endl;


    ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        cout << "ERROR: no se pudo abrir: "
             << rutaArchivo << endl;
        return false;
    }

     cout << "Archivo abierto correctamente." << endl;

    string linea;
    int numeroLinea = 0;
    int cargados = 0;
    int rechazados = 0;

    while (getline(archivo, linea)) {
        numeroLinea++;

        if (quitarEspacios(linea).empty()) {
            continue;
        }

        vector<string> campos = separarCampos(linea);

        // Deben existir exactamente once campos.
        if (campos.size() != 11) {
            cout << "Registro invalido en linea "
                 << numeroLinea
                 << ": se esperaban 11 campos."
                 << endl;

            rechazados++;
            continue;
        }

        // Saltar encabezado si existe.
        if (normalizarTexto(campos[0]) == "id" &&
            normalizarTexto(campos[1]) == "nombre") {
            continue;
        }

        // ------------------------------------
        // 1. EXTRAER CAMPOS
        // ------------------------------------

        string id = campos[0];
        string nombre = campos[1];

        int edad = 0;
        double temperatura = 0.0;
        double presionArterial = 0.0;
        int dolor = 0;

        string tipoDolor = normalizarTexto(campos[6]);

        int trauma = -1;
        int sintomasNeurologicos = -1;
        int requiereCirugia = -1;

        int diasHospitalizacion = 0;

        // ------------------------------------
        // 2. VALIDAR CAMPOS OBLIGATORIOS
        // ------------------------------------

        if (id.empty() || nombre.empty()) {
            cout << "Registro invalido en linea "
                 << numeroLinea
                 << ": ID y nombre son obligatorios."
                 << endl;

            rechazados++;
            continue;
        }

        // ------------------------------------
        // 3. CONVERTIR NUMEROS
        // ------------------------------------

        if (!convertirEntero(campos[2], edad) ||
            !convertirDecimal(campos[3], temperatura) ||
            !convertirDecimal(campos[4], presionArterial) ||
            !convertirEntero(campos[5], dolor) ||
            !convertirEntero(campos[7], trauma) ||
            !convertirEntero(campos[8], sintomasNeurologicos) ||
            !convertirEntero(campos[9], requiereCirugia) ||
            !convertirEntero(campos[10], diasHospitalizacion)) {

            cout << "Registro invalido en linea "
                 << numeroLinea
                 << ": existen campos numericos incorrectos."
                 << endl;

            rechazados++;
            continue;
        }

        // ------------------------------------
        // 4. VALIDAR RANGOS
        // ------------------------------------

        if (edad < 0 ||
            temperatura < 0 ||
            presionArterial < 0 ||
            dolor < 0 || dolor > 10 ||
            diasHospitalizacion < 0) {

            cout << "Registro invalido en linea "
                 << numeroLinea
                 << ": existen valores fuera de rango."
                 << endl;

            rechazados++;
            continue;
        }

        // Los campos binarios solo aceptan 0 o 1.
        if ((trauma != 0 && trauma != 1) ||
            (sintomasNeurologicos != 0 &&
             sintomasNeurologicos != 1) ||
            (requiereCirugia != 0 &&
             requiereCirugia != 1)) {

            cout << "Registro invalido en linea "
                 << numeroLinea
                 << ": los campos binarios deben ser 0 o 1."
                 << endl;

            rechazados++;
            continue;
        }

        // ------------------------------------
        // 5. VALIDAR TIPO DE DOLOR
        // ------------------------------------

        if (tipoDolor != "pecho" &&
            tipoDolor != "cabeza" &&
            tipoDolor != "abdomen" &&
            tipoDolor != "extremidad" &&
            tipoDolor != "otro") {

            cout << "Registro invalido en linea "
                 << numeroLinea
                 << ": tipo de dolor desconocido."
                 << endl;

            rechazados++;
            continue;
        }

        // ------------------------------------
        // 6. COMPROBAR IDS DUPLICADOS
        // ------------------------------------

        if (existePaciente(colaPacientes, id)) {
            cout << "Paciente duplicado, ID: "
                 << id << endl;

            rechazados++;
            continue;
        }

        // ------------------------------------
        // 7. CREAR Y ENCOLAR PACIENTE
        // ------------------------------------

        Paciente paciente(
            id,
            nombre,
            edad,
            temperatura,
            presionArterial,
            dolor,
            tipoDolor,
            trauma == 1,
            sintomasNeurologicos == 1,
            requiereCirugia == 1,
            diasHospitalizacion
        );

        colaPacientes.enqueue(paciente);

        cargados++;
    }

    archivo.close();

    //cout << "Carga de pacientes finalizada." << endl;
    //cout << "Pacientes cargados: " << cargados << endl;
    //cout << "Registros rechazados: " << rechazados << endl;

    return true;
}