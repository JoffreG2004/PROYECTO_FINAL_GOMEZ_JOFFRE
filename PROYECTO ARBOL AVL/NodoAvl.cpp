#include "NodoAVL.h"
#include "Coche.h"

NodoAVL::NodoAVL(int distancia) {
    this->distancia = distancia;
    this->izquierdo = nullptr;
    this->derecho = nullptr;
    this->altura = 1;  
}
NodoAVL::NodoAVL(Coche* coche) {
    this->coche = coche;   
    this->izquierdo = nullptr;  
    this->derecho = nullptr;
    this->altura = 1;  
}