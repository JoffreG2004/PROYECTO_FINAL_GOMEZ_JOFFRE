#pragma once

#include <unordered_map>
#include "Coche.h"
#include <vector>

class Estacionamiento {
private:
    const int TAMANIO = 100;  
    std::unordered_map<int, Coche> espaciosOcupados;  

public:
    Estacionamiento();  
    void ocuparEspacio(int espacio, Coche& coche);  
    void liberarEspacio(const std::string& placa); 
    void mostrarEstacionamiento();  
    int obtenerEspacioAleatorio();  
    int getNumeroEspacios() const;  
    bool espacioOcupado(int espacio);  
    Coche obtenerCocheEnEspacio(int espacio);  
    int obtenerEspacioPorPlaca(const std::string& placa);
    void vaciarEstacionamiento();
    int buscarCocheCercano(string salida);
    vector<int> obtenerTodosLosEspacios();
    void obtenerEstadoJSON();
};