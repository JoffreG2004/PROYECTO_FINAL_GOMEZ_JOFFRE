import networkx as nx
import random
import logging

def calcular_costo(G, destino, prioridad_por_ruta=True):
    """
    Calcula el costo de un destino basándose en la congestión de las aristas,
    y penaliza la proximidad a otros autos solo si es necesario.
    :param G: Grafo del parqueadero.
    :param destino: Lista de nodos que representan el destino.
    :param prioridad_por_ruta: Si True, da más peso a la ruta rápida, si False, prioriza evitar proximidad.
    :return: El costo total del destino.
    """
    costo = 0
    for i in range(len(destino) - 1):
        nodo_actual = destino[i]
        nodo_siguiente = destino[i + 1]
        peso = G[nodo_actual][nodo_siguiente].get('peso', 1)
        
        # Si la prioridad es por ruta, se prioriza el peso de la arista
        if prioridad_por_ruta:
            costo += peso
        else:
            costo += 1  # Agregar un costo constante si no es por ruta rápida

        # Penalización por proximidad a un espacio ocupado solo si es necesario
        if G.nodes[nodo_siguiente]["espacio"] == "X":  # Si el nodo siguiente está ocupado
            costo += 2  # Penalización por acercarse a un espacio ocupado

        # Penalización por estar al lado de un carro (solo si es necesario)
        vecinos = [v for v in G.neighbors(nodo_siguiente)]
        for vecino in vecinos:
            if G.nodes[vecino]["espacio"] == "X":  # Si el vecino está ocupado
                costo += 2  # Penalización por estar cerca de otro vehículo

    return costo

def encontrar_camino_minimo(G, destino):
    """
    Algoritmo para encontrar el camino mínimo en un parqueadero, primero priorizando la ruta rápida,
    y luego evaluando la proximidad a otros autos solo si es necesario.
    :param G: Grafo del parqueadero.
    :param destino: Nodo final (tupla, p. ej., (i, j)).
    :return: Lista con el camino mínimo encontrado o None si no se encuentra camino.
    """
    logging.basicConfig(level=logging.DEBUG)
    logger = logging.getLogger(__name__)
    
    entrada = (0, 11)  # Punto de entrada fijo
    
    logger.debug(f"Buscando camino mínimo de {entrada} a {destino}")
    
    # Comprobaciones básicas
    if destino is None:
        logger.error("Destino no proporcionado.")
        return None
    
    if not isinstance(entrada, tuple) or not isinstance(destino, tuple):
        logger.error(f"Entrada o destino no son tuplas válidas. Entrada: {entrada}, Destino: {destino}")
        return None

    if entrada not in G.nodes or destino not in G.nodes:
        logger.error(f"Entrada o destino no existen en el grafo. Entrada: {entrada}, Destino: {destino}")
        return None

    camino = [entrada]
    actual = entrada
    visitados = set()
    
    while actual != destino:
        visitados.add(actual)
        # Se consideran solo vecinos no visitados y que no estén ocupados
        vecinos = [v for v in G.neighbors(actual) if v not in visitados and G.nodes[v].get("espacio") != "X"]
        if not vecinos:
            logger.warning("No hay vecinos disponibles, ruta interrumpida")
            return None
        
        # Se evalúa el costo de cada vecino dependiendo de la prioridad por ruta o proximidad
        siguiente = min(vecinos, key=lambda nodo: calcular_costo(G, camino + [nodo], prioridad_por_ruta=True))
        logger.debug(f"Moviéndonos de {actual} a {siguiente} con costo {calcular_costo(G, camino + [siguiente], prioridad_por_ruta=True)}")
        camino.append(siguiente)
        actual = siguiente

    logger.info(f"Ruta encontrada: {camino}")
    return camino
