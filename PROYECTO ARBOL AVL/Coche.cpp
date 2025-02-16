#include <iostream>
#include "Coche.h"
#include "Menu.h"
#include "Propietario.h"
#include "ValidacionPlaca.h"
#include "Validaciones.h"
#include <string> 
#include <vector>
#include <cstdlib>

using namespace std;

Coche::Coche()
{
    this->placa = "";
    this->marca = "";
    this->modelo = "";
    this->color = "";
    this->posicion = 0;
}

Coche::Coche(int posicion) : posicion(posicion) {}

Coche::Coche(string placa, string modelo, string color, string marca, int posicion)
    : placa(placa), modelo(modelo), color(color), marca(marca), posicion(posicion), horaIngreso(chrono::system_clock::now()) {}

Coche::Coche(string placa, string modelo, string color, string marca, std::chrono::time_point<std::chrono::system_clock> horaIngreso, std::chrono::time_point<std::chrono::system_clock> horaSalida, int posicion)
: placa(placa), modelo(modelo), color(color), marca(marca),
      horaIngreso(horaIngreso), horaSalida(horaSalida), posicion(posicion) {}


Coche::Coche(string placa, string modelo, string color, string marca,
             chrono::system_clock::time_point horaIngreso, chrono::system_clock::time_point horaSalida )
    : placa(placa), modelo(modelo), color(color), marca(marca), posicion(), horaIngreso(horaIngreso), horaSalida(horaSalida) {}


void Coche::setHoraSalida(chrono::system_clock::time_point hora)
{
    horaSalida = hora;
}

void Coche::setPlaca(const string &placa)
{
    this->placa = placa;
}

void Coche::setModelo(const string &modelo)
{
    this->modelo = modelo;
}

void Coche::setMarca(const string &marca)
{
    this->marca = marca;
}

void Coche::setColor(const string &color)
{
    this->color = color;
}

void Coche::setPosicion(int posicion)
{
    this->posicion = posicion;
}

chrono::system_clock::time_point Coche::getHoraSalida() const
{
    return horaSalida;
}

string Coche::getPlaca() const
{
    return placa;
}

string Coche::getMarca() const
{
    return marca;
}

string Coche::getModelo() const
{
    return modelo;
}

string Coche::getColor() const
{
    return color;
}

int Coche::getposicion() const
{
    return posicion;
}

chrono::system_clock::time_point Coche::getHora() const
{
    return horaIngreso;
}



ostream &operator<<(ostream &os, const Coche &coche)
{
    os << "Placa: " << coche.placa << "\nMarca: " << coche.marca
       << "\nModelo: " << coche.modelo << "\nColor: " << coche.color
         << "\nPosicion: " << coche.posicion
       << "\n----------------------------------------" << endl;

    time_t tiempoIngreso = chrono::system_clock::to_time_t(coche.horaIngreso);
    os << "\nHora de Ingreso: " << ctime(&tiempoIngreso)
       << "\n----------------------------------------" << endl;

    if (coche.horaSalida == chrono::system_clock::time_point())
    {
        os << "\nHora de Salida: N/A" << endl;
    }
    else
    {
        time_t tiempoSalida = chrono::system_clock::to_time_t(coche.horaSalida);
        os << "\nHora de Salida: " << ctime(&tiempoSalida)
           << "\n----------------------------------------" << endl;
    }

    return os;
}


Coche Coche::InsertarDatos(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial, ListaCircularDoble<Propietario> &listaPropietarios, int posicion )
{
    Validaciones validaciones;
    Placa<Coche> validador;

    string placa, modelo, color, marca, cedula;

    Nodo<Propietario> *propietarioNodo = nullptr;
    bool propietarioEncontrado = false;

    while (!propietarioEncontrado)
    {
        do {
            cedula = validaciones.ingresarCedula("Ingrese la cedula del propietario: ");
            if (!validaciones.validarCedula(cedula)) {
                cout << "Cedula invalida. Intente de nuevo." << endl;
            }
        } while (!validaciones.validarCedula(cedula));
    
        propietarioNodo = listaPropietarios.getPrimero();

        do {
            if (propietarioNodo->getDato().getCedula() == cedula) {
                propietarioEncontrado = true;
                break;
            }
            propietarioNodo = propietarioNodo->getSiguiente();
        } while (propietarioNodo != listaPropietarios.getPrimero());

        if (!propietarioEncontrado) {
            cout << "No se encontro un propietario con esa cedula. Por favor, intente de nuevo." << endl;
        }
    }

    while (true)
    {
        placa = validador.ingresarPlaca(lista.getPrimero());
        
        Nodo<Coche> *temp = lista.getPrimero();
        bool placaDuplicada = false;

        if (temp != nullptr)
        {
            do
            {
                Coche cocheActual = temp->getDato();

                if (cocheActual.getPlaca() == placa && cocheActual.getHoraSalida() == chrono::system_clock::time_point())
                {
                    cout << "\nEl coche con la placa " << placa << " ya esta en el parqueadero. Ingrese una placa nueva." << endl;
                    placaDuplicada = true;
                    break;
                }

                temp = temp->getSiguiente();
            } while (temp != lista.getPrimero());
        }

        if (!placaDuplicada)
        {
            break;
        }
    }

    Nodo<Coche> *tempHistorial = listaHistorial.getPrimero();
    if (tempHistorial != nullptr)
    {
        do
        {
            Coche cocheHistorial = tempHistorial->getDato();

            if (cocheHistorial.getPlaca() == placa)
            {
                cout << "\nLa placa " << placa << " fue encontrada en el historial. Recuperando datos..." << endl;
                modelo = cocheHistorial.getModelo();
                color = cocheHistorial.getColor();
                marca = cocheHistorial.getMarca();

                cout << "Marca: " << marca << "\nColor: " << color << "\nModelo: " << modelo << "\n";

                vector<string> opciones = {"Si", "No"};
                int seleccion = menuInteractivo(opciones, "Auto encontrado en el sistema.\n¿Desea sobreescribir los datos del historial?");

                if (seleccion == 0) 
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "        Datos Recuperados Exitosamente  " << endl;
                    cout << "========================================" << endl;
                    cout << "\nMarca:    " << marca << endl;
                    cout << "Modelo:   " << modelo << endl;
                    cout << "Color:    " << color << endl;
                    cout << "Placa:    " << placa << endl;


                    
                    Propietario propietarioActualizado(propietarioNodo->getDato().getNombre(), 
                                                        propietarioNodo->getDato().getApellido(), 
                                                        propietarioNodo->getDato().getCedula(),
                                                        propietarioNodo->getDato().getCorreo(),
                                                        propietarioNodo->getDato().getPlacas());
                    propietarioActualizado.agregarPlaca(placa);
                    
                    
                    propietarioNodo->setDato(propietarioActualizado);

                    listaPropietarios.GuardarPropietarios("propietarios.txt");

                    return Coche(placa, modelo, color, marca, posicion);
                }
                else 
                {
                    system("cls");
                    cout << "\nPor favor, ingrese los datos manualmente:" << endl;
                    break;
                }
            }

            tempHistorial = tempHistorial->getSiguiente();
        } while (tempHistorial != listaHistorial.getPrimero());
    }

    marca = validaciones.ingresarString("Ingrese la marca: ");
    color = validaciones.ingresarString("Ingrese el color: ");
    modelo = validaciones.ingresarString("Ingrese el modelo: ");

  
    Propietario propietarioActualizado(propietarioNodo->getDato().getNombre(), 
                                        propietarioNodo->getDato().getApellido(), 
                                        propietarioNodo->getDato().getCedula(),
                                        propietarioNodo->getDato().getCorreo(),
                                        propietarioNodo->getDato().getPlacas());
    propietarioActualizado.agregarPlaca(placa);

   
    propietarioNodo->setDato(propietarioActualizado);

    listaPropietarios.GuardarPropietarios("propietarios.txt");

    return Coche(placa, modelo, color, marca, posicion);
}