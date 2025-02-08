#pragma once
#include "Nodo.h"

using namespace std;

template <typename T>
class ListaCircularDoble {
private:
      
    Nodo<T>* ultimo;    
    Nodo<T>* primero;
public:
     
  Nodo<T>* getPrimero() {
        return primero;
    }
    ListaCircularDoble();     
    void insertar(T dato);    
    void buscarPorPlaca(string placa);
    void BusquedaAvanzada(string criterio, string valorInicio, string valorFin);      
    void eliminarPorPlaca(string placa);    
    void mostrar(Nodo<T> *aux);  
    void CargarArchivo(string nombreArchivo);
    void GuardarArchivo(string nombreArchivo);
    void salirDelParqueadero(const std::string& placa);
    static std::string cifrarTexto(const std::string &texto); 
    static std::string descifrarTexto(const std::string &texto);
    bool estaVacia() const;
    void GuardarPropietarios(const std::string& nombreArchivo);
    void CargarPropietarios(const std::string& nombreArchivo);
    void BusquedaAvanzadaPropietario(string criterio, string valorInicio, string valorFin);
};

#include "Lista.cpp"

