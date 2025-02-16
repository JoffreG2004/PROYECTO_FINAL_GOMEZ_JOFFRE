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
        std::cerr << "La lista de coches está vacía." << std::endl;
        return;
    }

    do {
        Coche coche = nodoActual->getDato();  
        int posicionExistente = coche.getposicion();

        std::cerr << "Posición obtenida para el coche: " << posicionExistente << std::endl;

        if (posicionExistente == -1) {
            // Llamar a la API de Python para obtener el mejor espacio
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



