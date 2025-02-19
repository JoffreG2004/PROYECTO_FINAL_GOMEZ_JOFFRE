import pygame
import json
import os
import time

def simular_movimiento_carro(screen, ruta, car_image, CELL_WIDTH, CELL_HEIGHT, offset_x, offset_y):
    """Simula el movimiento del carro frame por frame."""
    print(f"Ruta recibida: {ruta}")  # Añade esto para depuración
    for i, nodo in enumerate(ruta):
        fila, columna = nodo
        x = columna * (CELL_WIDTH + 20) + offset_x
        y = fila * (CELL_HEIGHT + 20) + 50 + offset_y
        
        # Dibujar el carro en la posición actual
        screen.blit(car_image, (x + 5, y + 5))
        pygame.display.flip()
        time.sleep(1)  # Pausa para simular el movimiento

    # Cerrar Pygame después de que el carro se haya estacionado
    pygame.quit()
    exit()

def draw_parking_lot(estado, ruta):
    """Dibuja el parqueadero y simula el movimiento del carro."""
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

    running = True
    while running:
        screen.fill(WHITE)
        if background:
            screen.blit(background, (0, 0))

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False

        pygame.draw.rect(screen, BLUE, (road_offset_x, road_offset_y, ROAD_WIDTH, SCREEN_HEIGHT - road_offset_y - 50))
        for j in range(road_offset_y, SCREEN_HEIGHT - 50, 40):
            pygame.draw.line(screen, WHITE, (ROAD_WIDTH // 2 + road_offset_x, j), (ROAD_WIDTH // 2 + road_offset_x, j + 20), 4)

        for i in range(filas):
            for j in range(columnas):
                x = j * (CELL_WIDTH + 20) + offset_x  
                y = i * (CELL_HEIGHT + 20) + 50 + offset_y  

                id_espacio = i * columnas + j
                ocupado = any(e["id"] == id_espacio and e["ocupado"] for e in espacios)

                pygame.draw.rect(screen, YELLOW, (x - 2, y - 2, CELL_WIDTH + 4, CELL_HEIGHT + 4), 4)

                if ocupado:
                    screen.blit(car_image, (x + 5, y + 5))

                text = font.render(str(id_espacio), True, BLACK)
                screen.blit(text, (x + 10, y + 10))

        entrance_x1 = road_offset_x + 20  
        exit_x1 = entrance_x1 + 60      
        screen.blit(entrance_image, (entrance_x1, road_offset_y + 20))  
        screen.blit(exit_image, (exit_x1, road_offset_y + 20))  

        entrance_x2 = road_offset_x + 20  
        exit_x2 = entrance_x2 + 60       
        screen.blit(entrance_image, (entrance_x2, road_offset_y + 800))  
        screen.blit(exit_image, (exit_x2, road_offset_y + 800)) 

        # Usar la ruta pasada como parámetro
        if ruta:
            simular_movimiento_carro(screen, ruta, simulador_image, CELL_WIDTH, CELL_HEIGHT, offset_x, offset_y)

        pygame.display.flip()
        clock.tick(30)

    pygame.quit()

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
ruta_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\ruta.json"

car_image_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\carro-deportivo.png"
background_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\back.jpg"
entrance_image_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\entrada.png"
exit_image_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\salida.png"
simulador_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\car.png"

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

def main():
    """Función principal para iniciar la visualización."""
    estado = cargar_estado_parqueadero()
    ruta = cargar_ruta()

    draw_parking_lot(estado, ruta)

if __name__ == '__main__':
    main()