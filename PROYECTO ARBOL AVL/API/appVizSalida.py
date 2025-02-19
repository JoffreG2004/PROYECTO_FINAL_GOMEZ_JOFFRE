import pygame
import json
import os
import time
import networkx as nx

#############################
# Funciones para el cálculo de la ruta de salida (usando Dijkstra)
#############################

def construir_grafo(filas, columnas):
    """
    Construye un grafo en forma de grilla (filas x columnas) y agrega dos nodos de salida:
      - exit1: (0, columnas)   --> salida superior
      - exit2: (filas-1, columnas)  --> salida inferior
    Se conectan a la celda contigua (última columna) de la fila correspondiente.
    """
    G = nx.grid_2d_graph(filas, columnas)
    exit1 = (0, columnas)
    exit2 = (filas - 1, columnas)
    G.add_node(exit1)
    G.add_node(exit2)
    # Conectar la salida superior a la celda (0, columnas-1)
    G.add_edge((0, columnas - 1), exit1, weight=1)
    # Conectar la salida inferior a la celda (filas-1, columnas-1)
    G.add_edge((filas - 1, columnas - 1), exit2, weight=1)
    return G

def obtener_mejor_ruta(start, G):
    """
    Calcula la ruta más corta (usando Dijkstra) desde 'start' hasta cada uno de los dos
    nodos de salida y retorna la de menor longitud.
    """
    exit1 = (0, 10)   # salida superior
    exit2 = (9, 10)   # salida inferior
    ruta1 = None
    ruta2 = None
    try:
        ruta1 = nx.dijkstra_path(G, start, exit1)
    except nx.NetworkXNoPath:
        pass
    try:
        ruta2 = nx.dijkstra_path(G, start, exit2)
    except nx.NetworkXNoPath:
        pass

    if ruta1 and ruta2:
        return ruta1 if len(ruta1) <= len(ruta2) else ruta2
    elif ruta1:
        return ruta1
    elif ruta2:
        return ruta2
    else:
        return None

#############################
# Función para dibujar la grilla del parqueadero (con coches estacionados)
#############################

def draw_grid(screen, estado, font, filas, columnas, offset_x, offset_y, road_offset_x, road_offset_y, car_image):
    # Dibujar fondo (si hay imagen de fondo, se usa; sino se llena de blanco)
    if background:
        screen.blit(background, (0, 0))
    else:
        screen.fill(WHITE)
    # Dibujar la carretera
    pygame.draw.rect(screen, BLUE, (road_offset_x, road_offset_y, ROAD_WIDTH, SCREEN_HEIGHT - road_offset_y - 50))
    for j in range(road_offset_y, SCREEN_HEIGHT - 50, 40):
        pygame.draw.line(screen, WHITE, (road_offset_x + ROAD_WIDTH//2, j),
                         (road_offset_x + ROAD_WIDTH//2, j + 20), 4)
    # Dibujar cada celda del parqueadero
    for i in range(filas):
        for j in range(columnas):
            x = j * (CELL_WIDTH + 20) + offset_x
            y = i * (CELL_HEIGHT + 20) + 50 + offset_y
            # Dibujar borde amarillo
            pygame.draw.rect(screen, YELLOW, (x - 2, y - 2, CELL_WIDTH + 4, CELL_HEIGHT + 4), 4)
            # Dibujar el ID del espacio
            id_espacio = i * columnas + j
            text = font.render(str(id_espacio), True, BLACK)
            screen.blit(text, (x + 10, y + 10))
            # Dibujar coche si el espacio está ocupado
            ocupado = any(e["id"] == id_espacio and e["ocupado"] for e in estado["espacios"])
            if ocupado:
                screen.blit(car_image, (x + 5, y + 5))
    # Dibujar las imágenes de entrada y salida en la carretera
    entrance_x1 = road_offset_x + 20
    exit_x1 = entrance_x1 + 60
    screen.blit(entrance_image, (entrance_x1, road_offset_y + 20))
    screen.blit(exit_image, (exit_x1, road_offset_y + 20))
    entrance_x2 = road_offset_x + 20
    exit_x2 = entrance_x2 + 60
    screen.blit(entrance_image, (entrance_x2, road_offset_y + 800))
    screen.blit(exit_image, (exit_x2, road_offset_y + 800))

#############################
# Función de simulación del movimiento de salida
#############################

def simular_movimiento_carro(screen, ruta, simulador_image, exit_image, CELL_WIDTH, CELL_HEIGHT,
                              offset_x, offset_y, estado, font, filas, columnas, road_offset_x, road_offset_y, car_image):
    """
    Recorre la ruta de salida y en cada frame:
      - Redibuja todo el parqueadero (limpiando la imagen del carro de la celda anterior).
      - Dibuja la imagen del carro en la celda actual (o, en el último nodo, dibuja la imagen de salida).
    De esta forma se logra que, a medida que el carro se mueve, se "quita" la imagen del frame anterior.
    """
    print(f"Ruta de salida recibida: {ruta}")  # Depuración
    for i, nodo in enumerate(ruta):
        # Redibujar todo el parqueadero
        draw_grid(screen, estado, font, filas, columnas, offset_x, offset_y, road_offset_x, road_offset_y, car_image)
        fila, columna = nodo
        x = columna * (CELL_WIDTH + 20) + offset_x
        y = fila * (CELL_HEIGHT + 20) + 50 + offset_y

        if i < len(ruta) - 1:
            # Dibujar la imagen del carro en la celda actual
            screen.blit(simulador_image, (x + 5, y + 5))
        else:
            print("Salida alcanzada, el carro salió.")
            # En el nodo de salida: limpiar la celda y dibujar la imagen de salida
            # (la celda ya está limpia al redibujar el grid)
            screen.blit(exit_image, (x + 5, y + 5))
        pygame.display.flip()
        time.sleep(1)  # Pausa para apreciar cada frame

    # Esperar unos segundos al final para apreciar el estado final
    time.sleep(2)
    return

#############################
# Funciones para cargar datos desde JSON
#############################

def cargar_estado_parqueadero():
    """Carga el estado del parqueadero desde el archivo JSON."""
    try:
        with open(estado_parqueadero_path, "r") as file:
            return json.load(file)
    except Exception as e:
        print("Error al cargar el estado del parqueadero:", e)
        return {"espacios": []}

def cargar_posicion_coche():
    """Carga la posición del coche desde el JSON (se espera {'posicion': <número>})."""
    try:
        with open(posicion_coche_path, "r") as file:
            return json.load(file)
    except Exception as e:
        print("Error al cargar la posición del coche:", e)
        return {}

#############################
# Configuración y ejecución principal
#############################

# Definición de colores
BLACK   = (0, 0, 0)
WHITE   = (255, 255, 255)
GRAY    = (169, 169, 169)
YELLOW  = (255, 255, 0)
BLUE    = (30, 30, 30)

pygame.init()

SCREEN_WIDTH  = pygame.display.Info().current_w
SCREEN_HEIGHT = pygame.display.Info().current_h

CELL_WIDTH  = 107
CELL_HEIGHT = 60
ROAD_WIDTH  = 140

# Rutas a los archivos (ajusta según tu entorno)
estado_parqueadero_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\estado_parqueadero.json"
posicion_coche_path      = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\posicion_coche.json"

car_image_path       = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\carro-deportivo.png"
background_path      = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\back.jpg"
entrance_image_path  = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\entrada.png"
exit_image_path      = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\salida.png"
simulador_path       = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\car.png"

# Cargar imágenes globalmente (para usarlas en draw_grid y demás)
background = None
if os.path.exists(background_path):
    background = pygame.image.load(background_path)
    background = pygame.transform.scale(background, (SCREEN_WIDTH, SCREEN_HEIGHT))

entrance_image = pygame.image.load(entrance_image_path)
entrance_image = pygame.transform.scale(entrance_image, (40, 60))

exit_image = pygame.image.load(exit_image_path)
exit_image = pygame.transform.scale(exit_image, (40, 60))

def draw_parking_lot(estado, ruta):
    """
    Dibuja el parqueadero, ejecuta la simulación del movimiento de salida y luego
    deja el parqueadero en estado normal (sin la imagen del carro).
    """
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.RESIZABLE)
    pygame.display.set_caption("Simulación de Salida del Parqueadero")
    font = pygame.font.Font(None, 24)
    clock = pygame.time.Clock()

    filas, columnas = 10, 10
    parking_lot_width = columnas * (CELL_WIDTH + 20) + ROAD_WIDTH + 20
    parking_lot_height = filas * (CELL_HEIGHT + 20) + 50
    offset_x = (SCREEN_WIDTH - parking_lot_width) // 2
    offset_y = (SCREEN_HEIGHT - parking_lot_height) // 2
    road_offset_x = offset_x + parking_lot_width - 118
    road_offset_y = offset_y - 10

    # Ejecutar la simulación del movimiento (cada frame limpia la celda anterior)
    # Se usa la imagen del carro para el movimiento y, en la última celda, la imagen de salida.
    simulacion_finalizada = False
    simular_movimiento_carro(screen, ruta, 
                              pygame.transform.scale(pygame.image.load(simulador_path), (CELL_WIDTH - 10, CELL_HEIGHT - 10)),
                              exit_image,
                              CELL_WIDTH, CELL_HEIGHT,
                              offset_x, offset_y, estado, font, filas, columnas, road_offset_x, road_offset_y,
                              pygame.transform.scale(pygame.image.load(car_image_path), (CELL_WIDTH - 10, CELL_HEIGHT - 10)))
    simulacion_finalizada = True

    # Luego de la simulación, se deja el parqueadero dibujado en estado normal (sin carro)
    running = True
    while running:
        draw_grid(screen, estado, font, filas, columnas, offset_x, offset_y, road_offset_x, road_offset_y,
                  pygame.transform.scale(pygame.image.load(car_image_path), (CELL_WIDTH - 10, CELL_HEIGHT - 10)))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
        pygame.display.flip()
        clock.tick(30)
    pygame.quit()

def main():
    # Cargar estado del parqueadero
    estado = cargar_estado_parqueadero()
    # Cargar posición del coche (ej. {"posicion": 7})
    posicion_info = cargar_posicion_coche()
    pos = posicion_info.get("posicion", None)
    if pos is None:
        print("No se encontró la posición del coche en el JSON.")
        return
    # Calcular la celda de inicio (suponiendo 10 columnas)
    filas, columnas = 10, 10
    start = (pos // columnas, pos % columnas)
    print(f"Posición de inicio calculada: {start}")
    # Construir el grafo de la grilla (10x10) y agregar nodos de salida
    G = construir_grafo(filas, columnas)
    # Calcular la mejor ruta de salida (usando Dijkstra)
    ruta = obtener_mejor_ruta(start, G)
    if ruta is None:
        print("No se encontró una ruta de salida.")
        return
    print(f"Ruta de salida encontrada: {ruta}")
    # Dibujar el parqueadero y simular el movimiento de salida
    draw_parking_lot(estado, ruta)

if __name__ == '__main__':
    main()