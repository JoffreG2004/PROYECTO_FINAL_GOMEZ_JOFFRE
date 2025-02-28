import tkinter as tk
from tkinter import messagebox, ttk
from PIL import Image, ImageTk
import subprocess
import time
import os

def ejecutar_programa():
    try:
        subprocess.run(["cmd", "/c", "start", "cmd", "/k", "main.exe"], check=True)
    except subprocess.CalledProcessError as e:
        messagebox.showerror("Error", f"Error al ejecutar el programa: {e}")

def salir():
    root.destroy()

def cargar():
    for i in range(100):
        progress['value'] = i + 1
        root.update_idletasks()
        time.sleep(0.03)
    ejecutar_programa()

root = tk.Tk()
root.title("Bienvenido a Mi Parqueadero")
root.geometry("800x600")
root.configure(bg="#2c3e50")

fondo_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\fondo.jpg"
if os.path.exists(fondo_path):
    fondo = Image.open(fondo_path)
    fondo = fondo.resize((800, 600), Image.LANCZOS)
    fondo_img = ImageTk.PhotoImage(fondo)
    fondo_label = tk.Label(root, image=fondo_img)
    fondo_label.place(x=0, y=0, relwidth=1, relheight=1)
else:
    fondo_label = tk.Label(root, text="Fondo no encontrado", font=("Helvetica", 16), bg="#2c3e50", fg="white")
    fondo_label.pack(pady=20)

logo_path = "C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\UTILS\\logo.png"
if os.path.exists(logo_path):
    logo = Image.open(logo_path)
    logo = logo.resize((200, 200), Image.LANCZOS)
    logo_img = ImageTk.PhotoImage(logo)
    logo_label = tk.Label(root, image=logo_img, bg="#2c3e50")
    logo_label.pack(pady=20)
else:
    logo_label = tk.Label(root, text="Logo no encontrado", font=("Helvetica", 16), bg="#2c3e50", fg="white")
    logo_label.pack(pady=20)

frame = tk.Frame(root, bg="#000000", bd=5)
frame.place(relx=0.5, rely=0.7, anchor=tk.CENTER)  

titulo = tk.Label(frame, text="Bienvenido a Mi Parqueadero", font=("Helvetica", 24, "bold"), bg="#000000", fg="white")
titulo.pack(pady=20)


descripcion = tk.Label(frame, text="El mejor lugar para estacionar su coche", font=("Helvetica", 14), bg="#000000", fg="white")
descripcion.pack(pady=10)

style = ttk.Style()
style.theme_use('clam')
style.configure("TProgressbar", thickness=20, troughcolor='#2c3e50', background='#3498db', troughrelief='flat', bordercolor='#2c3e50', lightcolor='#3498db', darkcolor='#3498db')

progress = ttk.Progressbar(frame, orient=tk.HORIZONTAL, length=300, mode='determinate', style="TProgressbar")
progress.pack(pady=10)

btn_ejecutar = tk.Button(frame, text="Iniciar Programa", font=("Helvetica", 16), bg="#3498db", fg="white", command=cargar)
btn_ejecutar.pack(pady=10)


btn_salir = tk.Button(frame, text="Salir", font=("Helvetica", 16), bg="#e74c3c", fg="white", command=salir)
btn_salir.pack(pady=10)


root.mainloop()