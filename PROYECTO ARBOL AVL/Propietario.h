#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Lista.h"

using namespace std;

class Propietario
{
private:
    string nombre;
    string apellido;
    string cedula;
    string correo;
    vector<string> placas;

public:
    Propietario();
    Propietario(string nombre, string apellido, string cedula, string correo);
    Propietario(string nombre, string apellido, string cedula, string correo, vector<string> placas);

    void setNombre(const string &nombre);
    void setApellido(const string &apellido);
    void setCedula(const string &cedula);
    void setCorreo(const string &correo);
    void setPlacas(const vector<string> &placas);


    string getNombre() const;
    string getApellido() const;
    string getCedula() const;
    string getCorreo() const;

    void agregarPlaca(const string &placa);
    vector<string> eliminarPlaca(const string &placa);
    vector<string> getPlacas() const;
    

    friend ostream &operator<<(ostream &os, const Propietario &propietario);
    Propietario agregarPropietario(ListaCircularDoble<Propietario> &listaPropietarios);
    
};