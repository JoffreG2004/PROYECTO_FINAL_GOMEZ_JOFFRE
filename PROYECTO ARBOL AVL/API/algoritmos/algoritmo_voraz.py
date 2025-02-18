import networkx as nx
import logging

def encontrar_camino_minimo(G, destino):
    logging.basicConfig(level=logging.DEBUG)
    logger = logging.getLogger(__name__)
    
    entrada = (0, 11)  

    logger.debug(f"Buscando camino mínimo de {entrada} a {destino}")

    if destino is None or entrada not in G.nodes or destino not in G.nodes:
        logger.error("Entrada o destino inválidos.")
        return None

    try:
        camino = nx.shortest_path(G, source=entrada, target=destino, weight="peso")
        logger.info(f"Ruta encontrada: {camino}")
        return camino
    except nx.NetworkXNoPath:
        logger.warning("No se encontró un camino hacia el destino.")
        return None  