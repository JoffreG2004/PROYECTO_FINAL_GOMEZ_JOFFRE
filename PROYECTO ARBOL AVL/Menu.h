#pragma once
#include <iostream>
#include <vector>
#include "Lista.h"
#include "Propietario.h"
#include "Coche.h"
#include "Estacionamiento.h"
#include "Parqueadero.h"



using namespace std;

void menu(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial, ListaCircularDoble<Propietario> &listaPropietarios, Estacionamiento &estacionamiento, Parqueadero &parqueadero , ArbolAVL &arbolCoches);
int menuInteractivo(const vector<string> &opciones, const string &titulo = "Menu Interactivo");
void menuBusquedaAvanzada(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial);
void menuGestionPropietarios(ListaCircularDoble<Propietario> &listaPropietarios);
void menuOrdenar(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial,  ListaCircularDoble<Propietario> &listaPropietarios);
void menuBusquedaAvanzadaPropietario(ListaCircularDoble<Propietario> &listaPropietarios);
