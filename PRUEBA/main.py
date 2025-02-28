import numpy as np
import subprocess

def check_functions(n):
    log_n = np.log(n)
    e_log_n = np.exp(1) * log_n

    print(f"Para n = {n}:")
    print(f"  log(n) = {log_n}")
    print(f"  e * log(n) = {e_log_n}")
    print(f"  n = {n}")

    if e_log_n <= n:
        print("  e * log(n) <= n se cumple.")
    else:
        print("  e * log(n) > n no se cumple.")

def show_derivatives(n):
    log_n_derivative = 1.0 / n
    n_derivative = 1.0

    print(f"Derivadas para n = {n}:")
    print(f"  Derivada de log(n) = {log_n_derivative}")
    print(f"  Derivada de n = {n_derivative}")

    if log_n_derivative <= n_derivative:
        print("  La derivada de log(n) es menor o igual a la derivada de n.")
    else:
        print("  La derivada de log(n) es mayor que la derivada de n.")

def generar_datos():
    e = np.exp(1)
    valores_n = np.linspace(-10, 10, 200)  # Rango de -10 a 10
    valores_ne = valores_n * e  # Función ne
    valores_en = np.where(valores_n >= 0, e ** valores_n, np.nan)  # Función e^n (solo para n >= 0)

    # Guardar datos en un archivo sin encabezado para MATLAB
    np.savetxt("datos.txt", np.column_stack((valores_n, valores_ne, valores_en)), fmt="%.6f")
    print("Datos guardados en datos.txt.")

def ejecutar_matlab():
    try:
        print("Abriendo MATLAB para graficar los datos...")
        subprocess.run(["matlab", "-nodesktop", "-nosplash", "-r", "run('matlab.m'); pause;"], check=True)
    except FileNotFoundError:
        print("No se encontró MATLAB. Asegúrese de que está instalado y en la variable de entorno.")
    except subprocess.CalledProcessError as e:
        print(f"Error al ejecutar MATLAB: {e}")

if __name__ == "__main__":
    while True:
        n = float(input("Introduce un valor para n (ingresa -1 para terminar): "))
        if n == -1:
            break
        check_functions(n)
        show_derivatives(n)
    generar_datos()
    ejecutar_matlab()
    print("Datos generados. Ejecute el script MATLAB para graficar los datos.")