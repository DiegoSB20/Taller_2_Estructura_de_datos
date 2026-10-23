#pragma once

#include "Persona.hpp"
#include <string>

using namespace std;

class Paciente : public Persona {
private:
    string id;
    string servicioDestino;

    double temperatura;
    double presionArterial;
    int dolor;
    string tipoDolor;

    bool trauma;
    bool sintomasNeurologicos;
    bool requiereCirugia;

    int diasHospitalizacion;

public:
    Paciente();
    Paciente(
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
    );

    ~Paciente() override;

    string getId() const;
    string getServicioDestino() const;

    double getTemperatura() const;
    double getPresionArterial() const;
    int getDolor() const;
    string getTipoDolor() const;

    bool getTrauma() const;
    bool getSintomasNeurologicos() const;
    bool getRequiereCirugia() const;

    int getDiasHospitalizacion() const;

    void setId(const string& id);
    void setServicioDestino(const string& servicioDestino);

    void setTemperatura(double temperatura);
    void setPresionArterial(double presionArterial);
    void setDolor(int dolor);
    void setTipoDolor(const string& tipoDolor);

    void setTrauma(bool trauma);
    void setSintomasNeurologicos(bool sintomasNeurologicos);
    void setRequiereCirugia(bool requiereCirugia);

    void setDiasHospitalizacion(int diasHospitalizacion);

    void mostrarInformacion() const override;
};