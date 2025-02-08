from flask import Flask, jsonify
from algoritmos.grafos import cargar_estado_parqueadero, crear_grafo_parqueadero, visualizar_grafo
from algoritmos.Dijkstra import dijkstra
from algoritmos.algoritmo_voraz import algoritmo_voraz
import os

app = Flask(__name__)

@app.route('/')
def index():
    return "Bienvenido a la API del Parqueadero."

@app.route('/grafo')
def grafo():
    estado = cargar_estado_parqueadero()
    if "error" in estado:
        return jsonify({"error": estado["error"]}), 500  

  
    G = crear_grafo_parqueadero(estado)

   
    visualizar_grafo(G)

    return "Grafo generado y visualizado."

@app.route('/ruta/<int:x>/<int:y>')
def ruta(x, y):
    estado = cargar_estado_parqueadero()
    if "error" in estado:
        return jsonify({"error": estado["error"]}), 500  

   
    G = crear_grafo_parqueadero(estado)

  
    entrada = (0, 0)  
    destino = (x, y) 

    
    path = dijkstra(G, entrada, destino)
    
    if path:
        return jsonify({"ruta": path})
    else:
        return jsonify({"error": "No se pudo encontrar una ruta."}), 404

@app.route('/asignar_espacio')
def asignar_espacio():
    estado = cargar_estado_parqueadero()
    if "error" in estado:
        return jsonify({"error": estado["error"]}), 500  

   
    G = crear_grafo_parqueadero(estado)

    espacio_asignado = algoritmo_voraz(G)

    if espacio_asignado:
        return jsonify({"espacio_asignado": espacio_asignado})
    else:
        return jsonify({"error": "No hay espacios libres."}), 404


@app.route('/shutdown', methods=['POST'])
def shutdown():
    os._exit(0)  
    return 'Server shutting down...'

if __name__ == '__main__':
    app.run(debug=True, use_reloader=False)  
