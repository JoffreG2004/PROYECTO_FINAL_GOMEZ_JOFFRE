import networkx as nx


def dijkstra(G, start, end):
  
    try:
        path = nx.dijkstra_path(G, start, end)
        return path
    except nx.NetworkXNoPath:
        return None  
