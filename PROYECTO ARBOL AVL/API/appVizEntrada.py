import pygame
import json
import os
import time

# -------------------------------------------------------------------
# Configuración de la ruta similar a C++ (GetAppDataPath())
# -------------------------------------------------------------------
appdata_path = os.path.join(os.getenv("LOCALAPPDATA"), "Parqueadero AVL", "data")
if not os.path.exists(appdata_path):
    os.makedirs(appdata_path)

estado_parqueadero_path = os.path.join(appdata_path, "estado_parqueadero.json")
ruta_path = os.path.join(appdata_path, "ruta.json")

# -------------------------------------------------------------------
# Rutas de las imágenes (se mantienen igual o ajústalas según convenga)
# -------------------------------------------------------------------
car_image_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\carro-deportivo.png"
background_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\back.jpg"
entrance_image_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\entrada.png"
exit_image_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\salida.png"
simulador_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\carro-deportivo-izquierda.png"

# -------------------------------------------------------------------
# Función para simular el movimiento del carro en la ruta
# -------------------------------------------------------------------
def simular_movimiento_carro(screen, ruta, simulador_image, CELL_WIDTH, CELL_HEIGHT, offset_x, offset_y):
    """
    Simula el movimiento del carro recorriendo la ruta.
    En los nodos intermedios se dibuja la imagen, y al llegar al destino se "limpia" la celda.
    Al finalizar, se espera unos segundos para apreciar el estado especial antes de volver a la normalidad.
    """
    print(f"Ruta recibida: {ruta}")  # Depuración
    for i, nodo in enumerate(ruta):
        fila, columna = nodo
        x = columna * (CELL_WIDTH + 20) + offset_x
        y = fila * (CELL_HEIGHT + 20) + 50 + offset_y

        # En los nodos intermedios se dibuja la imagen del carro
        if i < len(ruta) - 1:
            screen.blit(simulador_image, (x + 5, y + 5))
        else:
            print("Destino alcanzado, el carro se estacionó.")
            # Al llegar al destino no se dibuja nada, dejando la celda "limpia"
        pygame.display.flip()
        time.sleep(1)  # Pausa entre nodos

    # Esperar unos segundos en el destino antes de volver a la normalidad
    time.sleep(2)
    # Retornamos sin salir de Pygame, para que la función principal pueda volver a dibujar
    return

# -------------------------------------------------------------------
# Función para dibujar el parqueadero y ejecutar la simulación
# -------------------------------------------------------------------
def draw_parking_lot(estado, ruta):
    """
    Dibuja el parqueadero y, si existe una ruta, ejecuta la simulación del movimiento.
    Mientras la simulación no haya finalizado se resalta el nodo destino de forma especial.
    Cuando la simulación finaliza, se vuelve a dibujar todo normalmente.
    """
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.RESIZABLE)
    pygame.display.set_caption("Simulación de Parqueadero")
    font = pygame.font.Font(None, 24)
    clock = pygame.time.Clock()

    filas, columnas = 10, 10
    espacios = estado.get("espacios", [])

    # Cargar imágenes
    car_image = pygame.image.load(car_image_path)
    car_image = pygame.transform.scale(car_image, (CELL_WIDTH - 10, CELL_HEIGHT - 10))

    simulador_image = pygame.image.load(simulador_path)
    simulador_image = pygame.transform.scale(simulador_image, (CELL_WIDTH - 10, CELL_HEIGHT - 10))

    background = None
    if os.path.exists(background_path):
        background = pygame.image.load(background_path)
        background = pygame.transform.scale(background, (SCREEN_WIDTH, SCREEN_HEIGHT))

    entrance_image = pygame.image.load(entrance_image_path)
    entrance_image = pygame.transform.scale(entrance_image, (40, 60))

    exit_image = pygame.image.load(exit_image_path)
    exit_image = pygame.transform.scale(exit_image, (40, 60))

    parking_lot_width = columnas * (CELL_WIDTH + 20) + ROAD_WIDTH + 20
    parking_lot_height = filas * (CELL_HEIGHT + 20) + 50
    offset_x = (SCREEN_WIDTH - parking_lot_width) // 2
    offset_y = (SCREEN_HEIGHT - parking_lot_height) // 2

    road_offset_x = offset_x + parking_lot_width - 118
    road_offset_y = offset_y - 10

    # Convertir el último nodo de la ruta a tupla (por si viene como lista)
    destino = tuple(ruta[-1]) if ruta else None

    # Bandera para indicar si la simulación ya se ejecutó
    simulacion_finalizada = False

    running = True
    while running:
        # Dibujar fondo
        if background:
            screen.blit(background, (0, 0))
        else:
            screen.fill(WHITE)

        # Procesar eventos
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False

        # Dibujar la carretera
        pygame.draw.rect(screen, BLUE, (road_offset_x, road_offset_y, ROAD_WIDTH, SCREEN_HEIGHT - road_offset_y - 50))
        for j in range(road_offset_y, SCREEN_HEIGHT - 50, 40):
            pygame.draw.line(screen, WHITE, (ROAD_WIDTH // 2 + road_offset_x, j),
                             (ROAD_WIDTH // 2 + road_offset_x, j + 20), 4)

        # Dibujar cada celda del parqueadero
        for i in range(filas):
            for j in range(columnas):
                x = j * (CELL_WIDTH + 20) + offset_x
                y = i * (CELL_HEIGHT + 20) + 50 + offset_y

                id_espacio = i * columnas + j
                ocupado = any(e["id"] == id_espacio and e["ocupado"] for e in espacios)

                # Mientras la simulación no haya finalizado, se resalta el nodo destino de forma especial
                if not simulacion_finalizada and destino and (i, j) == destino:
                    # "Limpiar" la celda: se dibuja un rectángulo relleno de blanco
                    pygame.draw.rect(screen, WHITE, (x, y, CELL_WIDTH, CELL_HEIGHT))
                    # Dibujar un borde verde para destacar el destino
                    pygame.draw.rect(screen, (0, 255, 0), (x - 2, y - 2, CELL_WIDTH + 4, CELL_HEIGHT + 4), 6)
                    # Escribir la etiqueta "DESTINO"
                    destino_text = font.render("DESTINO", True, BLACK)
                    screen.blit(destino_text, (x + 10, y + 10))
                else:
                    # Dibujo normal de la celda: borde amarillo
                    pygame.draw.rect(screen, YELLOW, (x - 2, y - 2, CELL_WIDTH + 4, CELL_HEIGHT + 4), 4)
                    # Si el espacio está ocupado, se dibuja la imagen del carro
                    if ocupado:
                        screen.blit(car_image, (x + 5, y + 5))
                    # Mostrar el ID del espacio
                    text = font.render(str(id_espacio), True, BLACK)
                    screen.blit(text, (x + 10, y + 10))

        # Dibujar las imágenes de entrada y salida en la carretera
        entrance_x1 = road_offset_x + 20
        exit_x1 = entrance_x1 + 60
        screen.blit(entrance_image, (entrance_x1, road_offset_y + 20))
        screen.blit(exit_image, (exit_x1, road_offset_y + 20))

        entrance_x2 = road_offset_x + 20
        exit_x2 = entrance_x2 + 60
        screen.blit(entrance_image, (entrance_x2, road_offset_y + 800))
        screen.blit(exit_image, (exit_x2, road_offset_y + 800))

        # Si aún no se ha ejecutado la simulación y existe una ruta, se la ejecuta
        if not simulacion_finalizada and ruta:
            simular_movimiento_carro(screen, ruta, simulador_image, CELL_WIDTH, CELL_HEIGHT, offset_x, offset_y)
            simulacion_finalizada = True

        pygame.display.flip()
        clock.tick(30)

    pygame.quit()

# -------------------------------------------------------------------
# Definición de colores y configuración de Pygame
# -------------------------------------------------------------------
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

# -------------------------------------------------------------------
# Funciones para cargar el estado del parqueadero y la ruta
# -------------------------------------------------------------------
def cargar_estado_parqueadero():
    """Carga el estado del parqueadero desde el archivo JSON."""
    try:
        with open(estado_parqueadero_path, "r") as file:
            return json.load(file)
    except Exception as e:
        print("Error al cargar el estado del parqueadero:", e)
        return {"espacios": []}

def cargar_ruta():
    """Carga la ruta desde el archivo JSON."""
    try:
        with open(ruta_path, "r") as file:
            data = json.load(file)
            return data.get("ruta_asignada", [])
    except Exception as e:
        print("Error al cargar la ruta:", e)
        return []

# -------------------------------------------------------------------
# Función principal para iniciar la visualización
# -------------------------------------------------------------------
def main():
    estado = cargar_estado_parqueadero()
    ruta = cargar_ruta()
    draw_parking_lot(estado, ruta)

if __name__ == '__main__':
    main()
