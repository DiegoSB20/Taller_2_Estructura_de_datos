#pragma once

#include <string>
#include <vector>

#include "../../data_structures/Data_structures_h//Queue.hpp"
#include "../../Clases/Clases_h//Paciente.hpp"

using namespace std;

class CargaArchivo {
private:
    string rutaArchivo;

    vector<string> separarCampos(const string& linea) const;

public:
    CargaArchivo();
    CargaArchivo(const string& rutaArchivo);
    ~CargaArchivo();

    string getRutaArchivo() const;
    void setRutaArchivo(const string& rutaArchivo);

    bool cargarPacientes(Queue<Paciente>& colaPacientes);
};