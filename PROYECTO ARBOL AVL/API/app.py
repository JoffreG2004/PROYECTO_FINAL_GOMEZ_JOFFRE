import json
import os
from flask import Flask, jsonify
import networkx as nx
from algoritmos.grafos import cargar_estado_parqueadero, crear_grafo_parqueadero, visualizar_grafo
from algoritmos.Dijkstra import dijkstra
from algoritmos.algoritmo_voraz import encontrar_camino_minimo

def get_appdata_path():
    """
    Obtiene la ruta de AppData para almacenar los archivos de datos.
    """
    return os.path.join(os.getenv("LOCALAPPDATA"), "Parqueadero AVL", "data")

appdata_path = get_appdata_path()
os.makedirs(appdata_path, exist_ok=True)  # Crear la carpeta si no existe

estado_parqueadero_path = os.path.join(appdata_path, "estado_parqueadero.json")
ruta_json_path = os.path.join(appdata_path, "ruta.json")

app = Flask(__name__)

def guardar_estado_parqueadero(estado):
    try:
        with open(estado_parqueadero_path, 'w') as archivo:
            json.dump(estado, archivo, indent=4)  
        print("[DEBUG] Estado del parqueadero guardado correctamente en:", estado_parqueadero_path)
    except Exception as e:
        print(f"[ERROR] Error al guardar el estado del parqueadero: {e}")

def guardar_ruta(ruta):
    try:
        with open(ruta_json_path, 'w') as archivo:
            json.dump({"ruta_asignada": ruta}, archivo, indent=4)
        print("[DEBUG] Ruta guardada correctamente en:", ruta_json_path)
    except Exception as e:
        print(f"[ERROR] Error al guardar la ruta: {e}")

@app.route('/')
def index():
    return "Bienvenido a la API del Parqueadero."

@app.route('/asignar_espacio')
def asignar_espacio():
    print("[DEBUG] Cargando estado del parqueadero...")
    estado = cargar_estado_parqueadero()

    if "error" in estado:
        print(f"[DEBUG] Error al cargar el estado del parqueadero: {estado['error']}")
        return jsonify({"error": estado["error"]}), 500  

    print("[DEBUG] Creando grafo de parqueadero...")
    G, pos = crear_grafo_parqueadero(estado)
    print("[DEBUG] Grafo creado.")

    mejor_destino = None
    menor_costo = float('inf')
    filas, columnas = 10, 12  

    for espacio in estado["espacios"]:
        id_espacio = espacio["id"]
        fila = id_espacio // (columnas - 2)
        columna = id_espacio % (columnas - 2)
        nodo = (fila, columna)
        
        if espacio["ocupado"]:
            continue 
        
        if nodo not in G.nodes:
            print(f"[DEBUG] El nodo {nodo} no está en el grafo.")
            continue
        
        costo = calcular_costo_camino(G, nodo)
        if costo < menor_costo:
            menor_costo = costo
            mejor_destino = nodo

    if mejor_destino is None:
        print("[DEBUG] No hay espacios disponibles.")
        return jsonify({"error": "No hay espacios disponibles."}), 404

    nodo_asignado = mejor_destino
    id_asignado = nodo_asignado[0] * (columnas - 2) + nodo_asignado[1]
    
    for espacio in estado["espacios"]:
        if espacio["id"] == id_asignado:
            espacio["ocupado"] = True
            break

    entrada = (0, 11)  
    ruta = encontrar_camino_minimo(G, nodo_asignado)  

    guardar_estado_parqueadero(estado)
    guardar_ruta(ruta)
    print(f"[DEBUG] Espacio asignado: {nodo_asignado}")

    return jsonify({"espacio_asignado": nodo_asignado, "ruta": ruta})

def calcular_costo_camino(G, nodo_destino):
    if nodo_destino not in G:
        print(f"[DEBUG] El nodo {nodo_destino} no está en el grafo.")
        return float('inf')
    
    costo = 0
    for vecino in G.neighbors(nodo_destino):
        if G.nodes[vecino].get("espacio") == "X":
            costo += 5  
        costo += G[nodo_destino][vecino].get('peso', 1)
    return costo

@app.route('/visualizar_grafo')
def visualizar_grafo_ruta():
    estado = cargar_estado_parqueadero()
    G, pos = crear_grafo_parqueadero(estado)
    visualizar_grafo(G, pos)  
    return "Gráfico del parqueadero mostrado."

@app.route('/shutdown', methods=['POST'])
def shutdown():
    os._exit(0)
    return 'Server shutting down...'

if __name__ == '__main__':
    app.run(debug=True, use_reloader=False)