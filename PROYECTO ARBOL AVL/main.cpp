#include <iostream>
#include <cstdlib> 
#include "Menu.h"
#include "Parqueadero.h"
#include "ArbolAVL.h"
#include "Estacionamiento.h"


void iniciarFlaskInicio(){
    system("python \"C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\Inicio.py\"");
    
}

int main() {
     //iniciarFlaskInicio();

    ListaCircularDoble<Propietario> listaPropietarios;
    ArbolAVL arbolCoches;
    listaPropietarios.CargarPropietarios("propietarios.txt");
    ListaCircularDoble<Coche> listaCochesHistorial;
    listaCochesHistorial.CargarArchivo("autos_historial.txt");
    Estacionamiento estacionamiento;
    ListaCircularDoble<Coche> listaCoches;
    listaCoches.CargarArchivo("autos.txt");
    Parqueadero parqueadero;

    menu(listaCoches, listaCochesHistorial, listaPropietarios, estacionamiento, parqueadero, arbolCoches);

    return 0;
}