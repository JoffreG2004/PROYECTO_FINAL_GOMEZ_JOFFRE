#pragma once

#include "Estacionamiento.h"
#include "ArbolAVL.h"
#include "Coche.h"  

class Parqueadero {
private:
    Estacionamiento estacionamiento;  
    ArbolAVL arbolCoches;  
    const int TAMANIO = 100;  

public:
    Parqueadero();
    void agregarCoche(Coche coche, int espacioLibre);
    void mostrarEstadoParqueadero();
    void mostrarCoches();
    void guardarEstadoParqueadero(const std::string& nombreArchivo);
    void cargarYAsignarParqueadero(ListaCircularDoble<Coche>& listaCoches , ArbolAVL& arbolCoches);
    void liberarParqueadero(ListaCircularDoble<Coche>& listaCoches, ArbolAVL& arbolCoches);
    void inicializarSemilla();
    void ObtenerEstadoJSON();

};