import os
from cryptography.fernet import Fernet

# Carpeta donde están los archivos a bloquear
folder_to_protect = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL"

# Generar una clave de cifrado si no existe
key_file = "encryption.key"
if not os.path.exists(key_file):
    key = Fernet.generate_key()
    with open(key_file, "wb") as keyfile:
        keyfile.write(key)
else:
    with open(key_file, "rb") as keyfile:
        key = keyfile.read()

cipher = Fernet(key)

def encrypt_file(file_path):
    try:
        with open(file_path, "rb") as file:
            file_data = file.read()
        encrypted_data = cipher.encrypt(file_data)
        with open(file_path + ".locked", "wb") as file:
            file.write(encrypted_data)
        os.remove(file_path)
    except Exception as e:
        print(f"Error al encriptar el archivo {file_path}: {e}")

def encrypt_all_txt():
    for filename in os.listdir(folder_to_protect):
        if filename.endswith(".txt"):
            encrypt_file(os.path.join(folder_to_protect, filename))
    return True

if __name__ == "__main__":
    # Encriptar todos los archivos .txt al iniciar el programa
    encrypt_all_txt()
    print("Todos los archivos .txt han sido encriptados.")