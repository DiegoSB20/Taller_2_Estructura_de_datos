#include "../../Clases/Clases_h/Persona.hpp"
#include <iostream>
using namespace std;

Persona::Persona() {
    nombre = "";
    edad = 0;
}

Persona::Persona(const string& nombre, int edad) {
    this->nombre = nombre;
    this->edad = edad; }

Persona::~Persona() { }

string Persona::getNombre() const {
    return nombre;
}

int Persona::getEdad() const {
    return edad; }


void Persona::setNombre(const string& nombre) {
    this->nombre = nombre; }


void Persona::setEdad(int edad) {
    this->edad = edad; }


void Persona::mostrarInformacion() const {
    cout << "Nombre: " << nombre << " | Edad: " << edad; }
