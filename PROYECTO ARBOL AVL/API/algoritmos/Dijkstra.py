import networkx as nx

# Algoritmo de Dijkstra para encontrar el camino más corto
def dijkstra(G, start, end):
    # Usamos nx.dijkstra_path para encontrar el camino más corto
    try:
        path = nx.dijkstra_path(G, start, end)
        return path
    except nx.NetworkXNoPath:
        return None  # No hay ruta entre los nodos
