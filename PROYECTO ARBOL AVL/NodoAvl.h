#pragma once
#include "Coche.h"

class NodoAVL {
public:
    Coche* coche;
    int distancia;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(int distancia);  
    NodoAVL(Coche* coche);
};