import networkx as nx
import logging
import random

def encontrar_camino_minimo(G, destino):
    logging.basicConfig(level=logging.DEBUG)
    logger = logging.getLogger(__name__)

    entradas_posibles = [(0, 10), (9, 10)]
    entrada = random.choice(entradas_posibles)

    logger.debug(f"Buscando camino mínimo de {entrada} a {destino}")

    if destino is None or entrada not in G.nodes or destino not in G.nodes:
        logger.error("Entrada o destino inválidos.")
        return None

    try:
        camino = nx.shortest_path(G, source=entrada, target=destino, weight="peso")
        logger.info(f"Ruta encontrada: {camino}")

        # Verificar si el nodo destino tiene carros adyacentes
        nodos_con_carros = {nodo for nodo, datos in G.nodes(data=True) if datos.get('carro')}
        nodos_adyacentes = set(G.neighbors(destino))

        if nodos_con_carros & nodos_adyacentes:
            logger.warning("El nodo destino tiene carros adyacentes. Buscando nodo alternativo.")

            # Buscar un nodo alternativo cercano sin carros adyacentes
            for nodo in camino[::-1]:
                if not (nodos_con_carros & set(G.neighbors(nodo))):
                    logger.info(f"Nuevo destino sin carros adyacentes: {nodo}")
                    return camino[:camino.index(nodo) + 1]

        return camino
    except nx.NetworkXNoPath:
        logger.warning("No se encontró un camino hacia el destino.")
        return None