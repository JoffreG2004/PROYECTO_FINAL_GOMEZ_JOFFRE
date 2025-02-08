# Algoritmo Voraz para minimizar la congestión
def algoritmo_voraz(G):
    # Crear una lista de nodos con sus "congestiones" (cantidad de autos alrededor)
    congestiones = {}
    for node in G.nodes():
        # Calcula la congestión de un nodo basado en los autos alrededor
        congestiones[node] = 0
        for neighbor in G.neighbors(node):
            if G.nodes[neighbor]["espacio"] == "X":  # Si está ocupado
                congestiones[node] += 1  # Aumentar la congestión

    # Ordenar los nodos por congestión (de menos a más)
    nodos_ordenados = sorted(congestiones, key=congestiones.get)

    # Asignar el primer espacio menos congestionado
    for nodo in nodos_ordenados:
        if G.nodes[nodo]["espacio"] == "[ ]":  # Si está vacío
            return nodo  # Asignar este espacio

    return None  # Si no hay espacios libres

