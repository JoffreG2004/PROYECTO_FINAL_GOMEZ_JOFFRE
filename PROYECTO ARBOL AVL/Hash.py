import os
import pygame
import pyperclip
import cv2
from cryptography.fernet import Fernet
from pygame.locals import *
from tkinter import Tk, filedialog

# Inicializar Pygame
pygame.init()

# Dimensiones de la ventana
ANCHO = 600
ALTO = 400
pantalla = pygame.display.set_mode((ANCHO, ALTO))
pygame.display.set_caption("Desencriptar Archivos")

# Colores
BLANCO = (255, 255, 255)
NEGRO = (0, 0, 0)
AZUL = (0, 121, 184)
VERDE = (0, 255, 0)
ROJO = (255, 0, 0)

# Fuente
fuente = pygame.font.SysFont("Arial", 20)

logo_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\logo.png"
logo = pygame.image.load(logo_path)  # Si tienes un logo, reemplaza 'logo.png'
logo = pygame.transform.scale(logo, (100, 100))  # Escala el logo a un tamaño adecuado

fondo_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\fondo.jpg"
fondo = pygame.image.load(fondo_path)  # Reemplaza con el nombre de tu fondo
fondo = pygame.transform.scale(fondo, (ANCHO, ALTO))  # Ajusta el tamaño del fondo a la ventana

# Ruta de la contraseña correcta
txt_password_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\CONTRASEÑA\\contraseña_generada.txt"
# Carpeta donde están los archivos a bloquear
folder_to_protect = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL"

# Leer la clave de cifrado
key_file = "encryption.key"
with open(key_file, "rb") as keyfile:
    key = keyfile.read()

cipher = Fernet(key)

def decrypt_file(file_path):
    try:
        with open(file_path, "rb") as file:
            encrypted_data = file.read()
        decrypted_data = cipher.decrypt(encrypted_data)
        original_file_path = file_path.replace(".locked", "")
        with open(original_file_path, "wb") as file:
            file.write(decrypted_data)
        os.remove(file_path)
    except Exception as e:
        print(f"Error al desencriptar el archivo {file_path}: {e}")

def decrypt_all_txt():
    for filename in os.listdir(folder_to_protect):
        if filename.endswith(".locked"):
            decrypt_file(os.path.join(folder_to_protect, filename))

def read_password_hash():
    try:
        with open(txt_password_path, "r", encoding="latin-1") as f:
            lines = f.readlines()
            for line in lines:
                if line.startswith("Hash:"):
                    return line.split("Hash:")[1].strip()
    except Exception as e:
        print(f"Error al leer el archivo de contraseña: {e}")
    return ""

def scan_qr_from_image(image_path):
    detector = cv2.QRCodeDetector()
    img = cv2.imread(image_path)
    if img is None:
        print(f"Error: No se pudo abrir el archivo de imagen {image_path}.")
        return ""
    data, _, _ = detector.detectAndDecode(img)
    return data.strip() if data else ""

def select_image_file():
    root = Tk()
    root.withdraw()  # Ocultar la ventana principal de Tkinter
    file_path = filedialog.askopenfilename(filetypes=[("Image files", "*.png;*.jpg;*.jpeg")])
    root.destroy()
    return file_path

# Función para mostrar texto
def mostrar_texto(texto, color, x, y, tamano=20):
    texto_renderizado = fuente.render(texto, True, color)
    pantalla.blit(texto_renderizado, (x, y))

# Función principal que maneja la interfaz
def interfaz_principal():
    clave_maestra = ""
    intentos = 3
    mensaje_error = ""  # Variable para mostrar el mensaje de error

    while True:
        pantalla.fill(BLANCO)
        pantalla.blit(fondo, (0, 0))  # Mostrar el fondo

        # Mostrar Logo
        pantalla.blit(logo, (ANCHO // 2 - 50, 30))

        # Mostrar instrucciones
        mostrar_texto("Ingrese la clave maestra para desbloquear los archivos:", ROJO, 50, 160)

        # Mostrar mensaje de error si es necesario
        if mensaje_error:
            mostrar_texto(mensaje_error, ROJO, 50, 320)

        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                quit()

            if event.type == KEYDOWN:
                if event.key == K_RETURN:  # Cuando se presiona "Enter"
                    correct_password = read_password_hash()
                    if clave_maestra == correct_password:  # Verificar clave
                        # Desbloquear archivos
                        decrypt_all_txt()
                        # Borrar el archivo de contraseña y el QR
                        if os.path.exists(txt_password_path):
                            os.remove(txt_password_path)
                        if os.path.exists("password_qr.png"):
                            os.remove("password_qr.png")
                        mostrar_texto("Contraseña correcta! Archivos desbloqueados.", VERDE, 50, 320)
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
                elif event.key == pygame.K_v and pygame.key.get_mods() & pygame.KMOD_CTRL:
                    clave_maestra += pyperclip.paste()
                elif event.key == pygame.K_i:
                    image_path = select_image_file()
                    if image_path:
                        clave_maestra = scan_qr_from_image(image_path)
                        if clave_maestra:
                            os.remove(image_path)
                else:
                    clave_maestra += event.unicode

        clave_oculta = "*" * len(clave_maestra)
        mostrar_texto(clave_oculta, NEGRO, 50, 190)

        pygame.draw.rect(pantalla, AZUL, (50, 180, 500, 40), 2)

        pygame.display.update()

if __name__ == "__main__":
    interfaz_principal()