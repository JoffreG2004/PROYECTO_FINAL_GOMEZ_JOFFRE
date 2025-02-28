import pygame
import hashlib
import random
import string
import qrcode
import os
from pygame.locals import *

# Inicializar Pygame
pygame.init()

# Dimensiones de la ventana
ANCHO = 600
ALTO = 400
pantalla = pygame.display.set_mode((ANCHO, ALTO))
pygame.display.set_caption("Generador de Contraseña y QR")

# Colores
BLANCO = (255, 255, 255)
NEGRO = (0, 0, 0)
AZUL = (0, 121, 184)
VERDE = (0, 255, 0)
ROJO = (255, 0, 0)

# Fuente
fuente = pygame.font.SysFont("Arial", 20)

logo_path= "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\logo.png"
logo = pygame.image.load(logo_path)  # Si tienes un logo, reemplaza 'logo.png'
logo = pygame.transform.scale(logo, (100, 100))  # Escala el logo a un tamaño adecuado

fondo_path= "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\fondo.jpg"
fondo = pygame.image.load(fondo_path)  # Reemplaza con el nombre de tu fondo
fondo = pygame.transform.scale(fondo, (ANCHO, ALTO))  # Ajusta el tamaño del fondo a la ventana

# Ruta donde se guardarán los archivos generados
directorio_guardado = r'C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\CONTRASEÑA'

# Verificar si el directorio existe, si no, crearlo
if not os.path.exists(directorio_guardado):
    os.makedirs(directorio_guardado)

# Función para generar una contraseña aleatoria
def generar_contraseña_aleatoria():
    longitud = 64
    caracteres = string.ascii_letters + string.digits + string.punctuation
    contraseña = ''.join(random.choice(caracteres) for _ in range(longitud))
    return contraseña

# Función para generar el hash
def generar_hash(contraseña):
    hash_object = hashlib.sha256(contraseña.encode())
    return hash_object.hexdigest()

# Función para generar QR
def generar_qr(hash_contraseña):
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=10,
        border=4,
    )
    qr.add_data(hash_contraseña)
    qr.make(fit=True)
    img = qr.make_image(fill='black', back_color='white')

    # Guardar el QR en el directorio especificado
    ruta_qr = os.path.join(directorio_guardado, "qr_contraseña.png")
    img.save(ruta_qr)

# Función para mostrar texto
def mostrar_texto(texto, color, x, y, tamano=20):
    texto_renderizado = fuente.render(texto, True, color)
    pantalla.blit(texto_renderizado, (x, y))

# Función principal que maneja la interfaz
def interfaz_principal():
    clave_maestra = ""
    intentos = 3
    generado = False
    mensaje_error = ""  # Variable para mostrar el mensaje de error

    while True:
        pantalla.fill(BLANCO)
        pantalla.blit(fondo, (0, 0))  # Mostrar el fondo

        # Mostrar Logo
        pantalla.blit(logo, (ANCHO // 2 - 50, 30))

        # Mostrar instrucciones
        mostrar_texto("Ingrese la clave maestra para generar la contraseña:", ROJO, 50, 160)

        # Mostrar mensaje de error si es necesario
        if mensaje_error:
            mostrar_texto(mensaje_error, ROJO, 280, 320)

        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                quit()

            if event.type == KEYDOWN:
                if event.key == K_RETURN:  # Cuando se presiona "Enter"
                    if clave_maestra == "Joesgoqui20082004":  # Verificar clave
                        # Generar contraseña y su hash
                        contraseña_aleatoria = generar_contraseña_aleatoria()
                        hash_contraseña = generar_hash(contraseña_aleatoria)

                        # Guardar la contraseña y el hash en un archivo de texto
                        ruta_contraseña = os.path.join(directorio_guardado, "contraseña_generada.txt")
                        with open(ruta_contraseña, "w") as archivo:
                            archivo.write(f"Contraseña generada: {contraseña_aleatoria}\n")
                            archivo.write(f"Hash: {hash_contraseña}\n")

                        # Mostrar solo la contraseña generada en la interfaz
                        mostrar_texto(f"Contraseña: {contraseña_aleatoria}", NEGRO, 50, 230)
                        mostrar_texto("Contraseña correcta!", VERDE, 50, 320)

                        # Generar y guardar QR
                        generar_qr(hash_contraseña)

                        pygame.display.update()
                        pygame.time.wait(1500)  
                        pygame.quit()
                        quit()
                    else:
                        intentos -= 1
                        if intentos > 0:
                            mensaje_error = f"Contraseña incorrecta. Intentos restantes: {intentos}"
                        else:
                            mensaje_error = "Demasiados intentos fallidos. Cerrando..."
                            pygame.display.update()
                            pygame.time.wait(1500) 
                            pygame.quit()
                            quit()
                    clave_maestra = "" 

                elif event.key == K_BACKSPACE:  
                    clave_maestra = clave_maestra[:-1]
                else:
                    clave_maestra += event.unicode

      
        clave_oculta = "*" * len(clave_maestra)
        mostrar_texto(clave_oculta, NEGRO, 50, 190)

      
        pygame.draw.rect(pantalla, AZUL, (50, 180, 500, 40), 2)

      
        pygame.draw.rect(pantalla, AZUL, (50, 350, 200, 40), 2)
        mostrar_texto("Generar Contraseña", AZUL, 70, 360)

        pygame.display.update()


interfaz_principal()
