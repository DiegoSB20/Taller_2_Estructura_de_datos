#include "../Clases_h/Paciente.hpp"
#include <iostream>

using namespace std;

Paciente::Paciente() : Persona() {
    id = "";
    servicioDestino = "";

    temperatura = 0.0;
    presionArterial = 0.0;
    dolor = 0;
    tipoDolor = "";

    trauma = false;
    sintomasNeurologicos = false;
    requiereCirugia = false;

    diasHospitalizacion = 0;
}

Paciente::Paciente(
    const string& id,
    const string& nombre,
    int edad,
    double temperatura,
    double presionArterial,
    int dolor,
    const string& tipoDolor,
    bool trauma,
    bool sintomasNeurologicos,
    bool requiereCirugia,
    int diasHospitalizacion
) : Persona(nombre, edad) {

    this->id = id;
    this->servicioDestino = "";

    this->temperatura = temperatura;
    this->presionArterial = presionArterial;
    this->dolor = dolor;
    this->tipoDolor = tipoDolor;

    this->trauma = trauma;
    this->sintomasNeurologicos = sintomasNeurologicos;
    this->requiereCirugia = requiereCirugia;

    this->diasHospitalizacion = diasHospitalizacion;
}

Paciente::~Paciente() {
}

string Paciente::getId() const {
    return id;
}

string Paciente::getServicioDestino() const {
    return servicioDestino;
}

double Paciente::getTemperatura() const {
    return temperatura;
}

double Paciente::getPresionArterial() const {
    return presionArterial;
}

int Paciente::getDolor() const {
    return dolor;
}

string Paciente::getTipoDolor() const {
    return tipoDolor;
}

bool Paciente::getTrauma() const {
    return trauma;
}

bool Paciente::getSintomasNeurologicos() const {
    return sintomasNeurologicos;
}

bool Paciente::getRequiereCirugia() const {
    return requiereCirugia;
}

int Paciente::getDiasHospitalizacion() const {
    return diasHospitalizacion;
}

void Paciente::setId(const string& id) {
    this->id = id;
}

void Paciente::setServicioDestino(
    const string& servicioDestino
) {
    this->servicioDestino = servicioDestino;
}

void Paciente::setTemperatura(double temperatura) {
    this->temperatura = temperatura;
}

void Paciente::setPresionArterial(double presionArterial) {
    this->presionArterial = presionArterial;
}

void Paciente::setDolor(int dolor) {
    this->dolor = dolor;
}

void Paciente::setTipoDolor(const string& tipoDolor) {
    this->tipoDolor = tipoDolor;
}

void Paciente::setTrauma(bool trauma) {
    this->trauma = trauma;
}

void Paciente::setSintomasNeurologicos(
    bool sintomasNeurologicos
) {
    this->sintomasNeurologicos = sintomasNeurologicos;
}

void Paciente::setRequiereCirugia(bool requiereCirugia) {
    this->requiereCirugia = requiereCirugia;
}

void Paciente::setDiasHospitalizacion(
    int diasHospitalizacion
) {
    this->diasHospitalizacion = diasHospitalizacion;
}

void Paciente::mostrarInformacion() const {
    cout << "ID: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Edad: " << edad << endl;
    cout << "Temperatura: " << temperatura << endl;
    cout << "Presion arterial: " << presionArterial << endl;
    cout << "Dolor: " << dolor << endl;
    cout << "Tipo de dolor: " << tipoDolor << endl;

    cout << "Trauma: "
         << (trauma ? "Si" : "No") << endl;

    cout << "Sintomas neurologicos: "
         << (sintomasNeurologicos ? "Si" : "No") << endl;

    cout << "Requiere cirugia: "
         << (requiereCirugia ? "Si" : "No") << endl;

    cout << "Dias de hospitalizacion: "
         << diasHospitalizacion << endl;

    cout << "Servicio: " << servicioDestino << endl;
}