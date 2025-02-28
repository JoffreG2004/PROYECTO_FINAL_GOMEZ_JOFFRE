import pygame
import json
import os
import time
import networkx as nx

def construir_grafo(filas, columnas):
    G = nx.grid_2d_graph(filas, columnas)
    exit1 = (0, columnas)
    exit2 = (filas - 1, columnas)
    G.add_node(exit1)
    G.add_node(exit2)
    G.add_edge((0, columnas - 1), exit1, weight=1)
    G.add_edge((filas - 1, columnas - 1), exit2, weight=1)
    return G

def obtener_mejor_ruta(start, G, salida):
    if salida == 1:
        try:
            ruta = nx.dijkstra_path(G, start, (0, 10))
        except nx.NetworkXNoPath:
            ruta = None
        return ruta
    elif salida == 2:
        try:
            ruta = nx.dijkstra_path(G, start, (9, 10))
        except nx.NetworkXNoPath:
            ruta = None
        return ruta
    else:
        exit1 = (0, 10)
        exit2 = (9, 10)
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

def draw_grid(screen, estado, font, filas, columnas, offset_x, offset_y, road_offset_x, road_offset_y, car_image):
    if background:
        screen.blit(background, (0, 0))
    else:
        screen.fill(WHITE)
    pygame.draw.rect(screen, BLUE, (road_offset_x, road_offset_y, ROAD_WIDTH, SCREEN_HEIGHT - road_offset_y - 50))
    for j in range(road_offset_y, SCREEN_HEIGHT - 50, 40):
        pygame.draw.line(screen, WHITE, (road_offset_x + ROAD_WIDTH // 2, j),
                         (road_offset_x + ROAD_WIDTH // 2, j + 20), 4)
    for i in range(filas):
        for j in range(columnas):
            x = j * (CELL_WIDTH + 20) + offset_x
            y = i * (CELL_HEIGHT + 20) + 50 + offset_y
            pygame.draw.rect(screen, YELLOW, (x - 2, y - 2, CELL_WIDTH + 4, CELL_HEIGHT + 4), 4)
            id_espacio = i * columnas + j
            text = font.render(str(id_espacio), True, BLACK)
            screen.blit(text, (x + 10, y + 10))
            ocupado = any(e["id"] == id_espacio and e["ocupado"] for e in estado["espacios"])
            if ocupado:
                screen.blit(car_image, (x + 5, y + 5))
    entrance_x1 = road_offset_x + 20
    exit_x1 = entrance_x1 + 60
    screen.blit(entrance_image, (entrance_x1, road_offset_y + 20))
    screen.blit(exit_image, (exit_x1, road_offset_y + 20))
    entrance_x2 = road_offset_x + 20
    exit_x2 = entrance_x2 + 60
    screen.blit(entrance_image, (entrance_x2, road_offset_y + 800))
    screen.blit(exit_image, (exit_x2, road_offset_y + 800))

def simular_movimiento_carro(screen, ruta, simulador_image, exit_image, CELL_WIDTH, CELL_HEIGHT,
                              offset_x, offset_y, estado, font, filas, columnas, road_offset_x, road_offset_y, car_image, salida):
    print(f"Usando salida {salida}")
    if ruta:
        fila, columna = ruta[0]
        for espacio in estado["espacios"]:
            if espacio["id"] == fila * columnas + columna:
                espacio["ocupado"] = False
    for i, nodo in enumerate(ruta):
        draw_grid(screen, estado, font, filas, columnas, offset_x, offset_y, road_offset_x, road_offset_y, car_image)
        fila, columna = nodo
        x = columna * (CELL_WIDTH + 20) + offset_x
        y = fila * (CELL_HEIGHT + 20) + 50 + offset_y
        if i < len(ruta) - 1:
            screen.blit(simulador_image, (x + 5, y + 5))
        else:
            print("Salida alcanzada, el carro salió.")
            screen.blit(exit_image, (x + 5, y + 5))
        pygame.display.flip()
        time.sleep(1)
    time.sleep(2)

def cargar_estado_parqueadero():
    try:
        with open(estado_parqueadero_path, "r") as file:
            return json.load(file)
    except Exception as e:
        print("Error al cargar el estado del parqueadero:", e)
        return {"espacios": []}

def cargar_posicion_coche():
    try:
        with open(posicion_coche_path, "r") as file:
            return json.load(file)
    except Exception as e:
        print("Error al cargar la posición del coche:", e)
        return {}

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (169, 169, 169)
YELLOW = (255, 255, 0)
BLUE = (30, 30, 30)

pygame.init()

SCREEN_WIDTH = pygame.display.Info().current_w
SCREEN_HEIGHT = pygame.display.Info().current_h

CELL_WIDTH = 107
CELL_HEIGHT = 60
ROAD_WIDTH = 140

estado_parqueadero_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\estado_parqueadero.json"
posicion_coche_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\posicion_coche.json"

car_image_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\carro-deportivo.png"
background_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\back.jpg"
entrance_image_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\entrada.png"
exit_image_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\salida.png"
simulador_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\car.png"

background = None
if os.path.exists(background_path):
    background = pygame.image.load(background_path)
    background = pygame.transform.scale(background, (SCREEN_WIDTH, SCREEN_HEIGHT))

entrance_image = pygame.image.load(entrance_image_path)
entrance_image = pygame.transform.scale(entrance_image, (40, 60))

exit_image = pygame.image.load(exit_image_path)
exit_image = pygame.transform.scale(exit_image, (40, 60))

def draw_parking_lot(estado):
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
    estado = cargar_estado_parqueadero()
    posicion_info = cargar_posicion_coche()
    posiciones = []
    if "posicion" in posicion_info:
        posiciones = [posicion_info["posicion"]]
    elif "posiciones" in posicion_info:
        posiciones = posicion_info["posiciones"]
    salida = 1
    if "salida" in posicion_info:
        salida = posicion_info["salida"]
    if not posiciones:
        print("No se encontró la posición del coche en el JSON.")
        return
    filas, columnas = 10, 10
    G = construir_grafo(filas, columnas)
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.RESIZABLE)
    pygame.display.set_caption("Simulación de Salida del Parqueadero")
    font = pygame.font.Font(None, 24)
    clock = pygame.time.Clock()
    parking_lot_width = columnas * (CELL_WIDTH + 20) + ROAD_WIDTH + 20
    parking_lot_height = filas * (CELL_HEIGHT + 20) + 50
    offset_x = (SCREEN_WIDTH - parking_lot_width) // 2
    offset_y = (SCREEN_HEIGHT - parking_lot_height) // 2
    road_offset_x = offset_x + parking_lot_width - 118
    road_offset_y = offset_y - 10
    for pos in posiciones:
        start = (pos // columnas, pos % columnas)
        print(f"Posición de inicio calculada para el coche en {pos}: {start}")
        ruta = obtener_mejor_ruta(start, G, salida)
        if ruta is None:
            print(f"No se encontró una ruta de salida para el coche en la posición {pos}.")
            continue
        print(f"Ruta de salida encontrada para el coche en la posición {pos}: {ruta}")
        simular_movimiento_carro(
            screen, ruta,
            pygame.transform.scale(pygame.image.load(simulador_path), (CELL_WIDTH - 10, CELL_HEIGHT - 10)),
            exit_image,
            CELL_WIDTH, CELL_HEIGHT,
            offset_x, offset_y, estado, font, filas, columnas, road_offset_x, road_offset_y,
            pygame.transform.scale(pygame.image.load(car_image_path), (CELL_WIDTH - 10, CELL_HEIGHT - 10)),
            salida
        )
        time.sleep(1)
    draw_parking_lot(estado)

if __name__ == '__main__':
    main()
