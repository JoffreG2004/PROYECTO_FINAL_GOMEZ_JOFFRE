#pragma once

#include "NodoAVL.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Coche.h"

class ArbolAVL {
private:
    NodoAVL* raiz;

   
   
    int obtenerFactorBalance(NodoAVL* nodo);
    NodoAVL* rotarDerecha(NodoAVL* y);
    NodoAVL* rotarIzquierda(NodoAVL* x);
    NodoAVL* insertar(NodoAVL* nodo, int distancia);
    void dibujarNodo(NodoAVL* nodo, sf::RenderWindow &ventana, sf::Font &fuente, float x, float y, float offset);

public:
 
    ArbolAVL();

 
    NodoAVL* obtenerRaiz();
    void agregarDistancia(int distancia);
    void mostrarDistancias();  
    void mostrarArbol(sf::RenderWindow& ventana, sf::Font& fuente);  
    void vaciarArbol();
    void recorridoInorden(NodoAVL* nodo);
    void recorridoPreorden(NodoAVL* nodo);
    void recorridoPostorden(NodoAVL* nodo);
    Coche* buscarCocheMasCercano(int salida);
    Nodo<Coche>* buscarCocheMasCercanoEnLista(ListaCircularDoble<Coche>& listaCoches, int salida);
    bool validarPosicion(int posicion);
    std::vector<int> determinarOrdenSalida(int salida, ListaCircularDoble<Coche>& listaCoches);
    Nodo<Coche>* buscarCochePorPosicion(int posicion, ListaCircularDoble<Coche>& listaCoches);
     int obtenerAltura(NodoAVL* nodo);
    int obtenerprofundidad(NodoAVL* nodo);
    void buscarPosicionPorPlaca(const std::string& placa, ListaCircularDoble<Coche>& listaCoches);
};
