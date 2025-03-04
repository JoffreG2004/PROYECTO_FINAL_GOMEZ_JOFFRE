import os
from cryptography.fernet import Fernet

# Función para obtener la ruta en AppData
def get_app_data_path():
    return os.path.join(os.getenv("LOCALAPPDATA"), "Parqueadero AVL", "data")

# Asegurar que la carpeta existe
app_data_path = get_app_data_path()
os.makedirs(app_data_path, exist_ok=True)

# Carpeta donde están los archivos a bloquear
folder_to_protect = app_data_path

# Generar una clave de cifrado si no existe
key_file = os.path.join(app_data_path, "encryption.key")
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
        # Guardar el archivo encriptado con extensión .locked
        encrypted_file_path = file_path + ".locked"
        with open(encrypted_file_path, "wb") as file:
            file.write(encrypted_data)
        os.remove(file_path)  # Eliminar el archivo original
        print(f"Archivo encriptado: {file_path}")
    except Exception as e:
        print(f"Error al encriptar el archivo {file_path}: {e}")

def encrypt_all_txt():
    try:
        # Listar todos los archivos .txt en la carpeta
        for filename in os.listdir(folder_to_protect):
            if filename.endswith(".txt"):
                file_path = os.path.join(folder_to_protect, filename)
                encrypt_file(file_path)
    except Exception as e:
        print(f"Error al encriptar los archivos: {e}")

if __name__ == "__main__":
    # Encriptar todos los archivos .txt al iniciar el programa
    encrypt_all_txt()
    print("Todos los archivos .txt han sido encriptados.")
