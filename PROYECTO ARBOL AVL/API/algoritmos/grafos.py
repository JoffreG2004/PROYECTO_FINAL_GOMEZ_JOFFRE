import matplotlib.pyplot as plt
import networkx as nx
import json
import random

# Ruta del archivo JSON que contiene el estado del parqueadero
estado_parqueadero_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\estado_parqueadero.json"

def cargar_estado_parqueadero():
    try:
        with open(estado_parqueadero_path, "r") as file:
            estado_json = json.load(file)
            return estado_json
    except Exception as e:
        return {"error": str(e)}

def crear_grafo_parqueadero(estado):
    G = nx.Graph()

    filas, columnas = 10, 12  

    for i in range(filas):  
        for j in range(columnas - 2):  
            G.add_node((i, j), espacio="[ ]") 

    for i in range(filas):  
        for j in range(columnas - 2): 
            congestion = random.randint(1, 10)  
            G.add_edge((i, j), (i, j + 1), peso=congestion) 
        if i < filas - 1: 
            for j in range(columnas - 2): 
                congestion = random.randint(1, 10)  
                G.add_edge((i, j), (i + 1, j), peso=congestion)  

    for i in range(filas): 
        for j in range(10, 12):  
            G.add_node((i, j), espacio="Carretera") 

    pos = {}
    id_secuencial = 0  

    for i in range(filas):  
        for j in range(columnas - 2):  
            pos[(i, j)] = (j, -i)  
            if id_secuencial < 100: 
                id_secuencial += 1

    for i in range(filas):  
        for j in range(10, 12):  
            pos[(i, j)] = (j, -i)  
            
            G.add_edge((0, 11), (0, 10), peso=1)

    espacios = estado.get("espacios", [])
    for espacio in espacios:
        id_espacio = espacio["id"]
        ocupado = espacio["ocupado"]  
        
        fila = id_espacio // (columnas - 2) 
        columna = id_espacio % (columnas - 2)  
        
        if (fila, columna) in G.nodes:
            if ocupado:
                G.nodes[(fila, columna)]["espacio"] = "X"  
            else:
                G.nodes[(fila, columna)]["espacio"] = "[ ]"  

    for fila in range(filas):
        if fila < 5: 
            G.add_edge((fila, 10), (0, 10), peso=1)
        else:  
            G.add_edge((fila, 10), (9, 10), peso=1)

    for fila in range(filas):
       if fila < 5:
       
        G.add_edge((fila, 11), (0, 11), peso=1)
    else:
       
        G.add_edge((fila, 11), (9, 11), peso=1)

    return G, pos



def visualizar_grafo(G, pos):
    plt.figure(figsize=(14, 12))  

    node_colors = []
    for node in G.nodes():
        if 'espacio' in G.nodes[node]:
            if G.nodes[node]["espacio"] == "X":
                node_colors.append("red") 
            else:
                node_colors.append("gray")  
        else:
            node_colors.append("lightblue")  

    nx.draw(G, pos, with_labels=True, node_size=500, node_color=node_colors, edge_color="gray", font_size=8)

    edge_labels = {}
    for (i, j) in G.edges():
        congestion = G[i][j]["peso"]
        edge_labels[(i, j)] = str(congestion)

    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

    entrada_salida_posiciones = [
       ((0, 10), "Salida 1 "),  
         ((0, 11), "Entrada 1   "), 
        ((9, 10), "Salida 2 "),  
         ((9, 11), "Entrada 2"),  
    ]
    
    for (posicion, texto) in entrada_salida_posiciones:
        x, y = pos[posicion]
        plt.text(x, y, texto, fontsize=12, ha="center", va="center", bbox=dict(facecolor="yellow", edgecolor="black", boxstyle="round,pad=0.5"))

    plt.grid(True)
    plt.show()

