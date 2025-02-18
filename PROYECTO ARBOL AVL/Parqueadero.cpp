#include "Parqueadero.h"

Parqueadero::Parqueadero() {
}


void Parqueadero::agregarCoche(Coche coche, int espacioLibre) {
   
    estacionamiento.ocuparEspacio(espacioLibre, coche);  

   
    arbolCoches.agregarDistancia(espacioLibre);

}


void Parqueadero::mostrarEstadoParqueadero() {
    estacionamiento.mostrarEstacionamiento();  
}


void Parqueadero::mostrarCoches() {
    std::cout << "Coches estacionados:" << std::endl;
    arbolCoches.mostrarDistancias();  
}

void Parqueadero::cargarYAsignarParqueadero(ListaCircularDoble<Coche>& listaCoches, ArbolAVL& arbolCoches) {
    estacionamiento.vaciarEstacionamiento();
    arbolCoches.vaciarArbol();

    Nodo<Coche>* nodoActual = listaCoches.getPrimero();

    if (nodoActual == nullptr) {
        return;
    }

    do {
        Coche coche = nodoActual->getDato();  
        int posicionExistente = coche.getposicion();


        if (posicionExistente == -1) {
           
            posicionExistente = estacionamiento.obtenerEspacioOptimo();
            coche.setPosicion(posicionExistente);
        }

        estacionamiento.ocuparEspacio(posicionExistente, coche);  
        arbolCoches.agregarDistancia(posicionExistente);
        nodoActual = nodoActual->getSiguiente();
    } while (nodoActual != listaCoches.getPrimero());  
}


void Parqueadero::inicializarSemilla() {
    std::srand(0);  
}

void Parqueadero::ObtenerEstadoJSON()
{
    estacionamiento.obtenerEstadoJSON();
}



