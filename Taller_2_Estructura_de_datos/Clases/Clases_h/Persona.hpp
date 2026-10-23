#pragma once

#include <string>
using namespace std;

class Persona {
protected:
    string nombre;
    int edad;

public:
    Persona();
    Persona(const string& nombre, int edad);
    virtual ~Persona();

    string getNombre() const;
    int getEdad() const;

    void setNombre(const string& nombre);
    void setEdad(int edad);

    virtual void mostrarInformacion() const;
}; 