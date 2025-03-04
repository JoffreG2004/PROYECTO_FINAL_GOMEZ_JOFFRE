#include "Propietario.h"
#include "Lista.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include "Coche.h"
#include <algorithm>
#include <cctype>
#include <algorithm>
#include <regex>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>
#include "ruta.h"
//SI METES AQUI EL MENU.H SE DAÑA TODITO 


using namespace std;

template <typename T>
ListaCircularDoble<T>::ListaCircularDoble()
{

    primero = nullptr;
    ultimo = nullptr;
}

template <typename T>
void ListaCircularDoble<T>::insertar(T dato )
{

    Nodo<T> *nuevoCarro = new Nodo<T>(dato);

    if (primero == nullptr)
    {

        primero = nuevoCarro;
        primero->setSiguiente(primero);
        primero->setAnterior(primero);
        ultimo = primero;
    }
    else
    {

        ultimo->setSiguiente(nuevoCarro);
        nuevoCarro->setAnterior(ultimo);
        ultimo = nuevoCarro;
        ultimo->setSiguiente(primero);
        primero->setAnterior(ultimo);
    }


}

template <typename T>
void ListaCircularDoble<T>::buscarPorPlaca(string placa)
{
    if (primero == nullptr)
    {
        cout << "La lista está vacía." << endl;
        return;
    }

    Nodo<T> *aux = primero;
    bool encontrado = false;  

    do
    {
       
        if (aux->getDato().getPlaca() == placa)
        {
            if (!encontrado)
            {
                cout << "========================================" << endl;
                cout << "   AUTOMOVILES REGISTRADOS CON LA PLACA: " << placa << endl;
                cout << "========================================" << endl;
            }

            cout << aux->getDato() << endl;  
            encontrado = true;  
        }
        aux = aux->getSiguiente();
    } while (aux != primero);

    if (!encontrado)
    {
        cout << "El coche con la placa " << placa << " no está en el parqueadero." << endl;
    }
}

template <typename T>
void ListaCircularDoble<T>::mostrar(Nodo<T> *primero)
{
    if (primero == nullptr)
    {
        std::cout << "La lista esta vacia." << std::endl;
        return;
    }

    Nodo<T> *aux = primero;

    cout << "AUTOMOVIL REGISTRADO" << endl;
    cout << "========================================" << endl;
    cout << aux->getDato() << endl;

    aux = aux->getSiguiente();
    while (aux != primero)
    {
        cout << aux->getDato() << endl;
        aux = aux->getSiguiente();
    }
}

template <typename T>
void ListaCircularDoble<T>::eliminarPorPlaca(string placa)
{

    if (primero == nullptr)
    {
        cout << "La lista está vacia." << endl;
        return;
    }

    Nodo<T> *aux = primero;
    Nodo<T> *anterior = nullptr;

    auto horaEliminacion = std::chrono::system_clock::now();
    std::time_t tiempoEliminacion = std::chrono::system_clock::to_time_t(horaEliminacion);

    if (primero == ultimo && primero->getDato().getPlaca() == placa)
    {
        delete primero;
        primero = nullptr;
        ultimo = nullptr;
        cout << "El coche con la placa " << placa << " ha sido eliminado." << endl;
        GuardarArchivo("autos.txt");
        return;
    }

    do
    {
        if (aux->getDato().getPlaca() == placa)
        {

            if (aux == primero)
            {
                primero = primero->getSiguiente();
                primero->setAnterior(ultimo);
                ultimo->setSiguiente(primero);
            }

            else if (aux == ultimo)
            {
                ultimo = ultimo->getAnterior();
                ultimo->setSiguiente(primero);
                primero->setAnterior(ultimo);
            }

            else
            {
                anterior = aux->getAnterior();
                anterior->setSiguiente(aux->getSiguiente());
                aux->getSiguiente()->setAnterior(anterior);
            }

            delete aux;
            cout << "El coche con la placa " << placa << " ha sido eliminado." << endl;
            GuardarArchivo("autos.txt");
            return;
        }

        aux = aux->getSiguiente();
    } while (aux != primero);

    cout << "El coche con la placa " << placa << " no se encontro en el parqueadero." << endl;
}

template <typename T>
void ListaCircularDoble<T>::BusquedaAvanzada(string criterio, string valorInicio, string valorFin)
{
    if (primero == nullptr)
    {
        cout << "La lista esta vacia." << endl;
        return;
    }

    
    if (criterio != "hora" && criterio != "fecha")
    {
        transform(valorInicio.begin(), valorInicio.end(), valorInicio.begin(), ::tolower);
    }

    Nodo<T> *aux = primero;
    bool encontrado = false;

    do
    {
        if (criterio == "marca")
        {
            string marca = aux->getDato().getMarca();
            transform(marca.begin(), marca.end(), marca.begin(), ::tolower);
            if (marca == valorInicio)
            {
                cout << "========================================" << endl;
                cout << "   AUTOMOVIL REGISTRADO POR MARCA" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true;
            }
        }

        else if (criterio == "modelo")
        {
            string modelo = aux->getDato().getModelo();
            transform(modelo.begin(), modelo.end(), modelo.begin(), ::tolower);
            if (modelo == valorInicio)
            {
                cout << "========================================" << endl;
                cout << "   AUTOMOVIL REGISTRADO POR MODELO" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true;
            }
        }

        else if (criterio == "color")
        {
            string color = aux->getDato().getColor();
            transform(color.begin(), color.end(), color.begin(), ::tolower);
            if (color == valorInicio)
            {
                cout << "========================================" << endl;
                cout << "   AUTOMOVIL REGISTRADO POR COLOR" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true;
            }
        }

        else if (criterio == "hora")
        {
            chrono::system_clock::time_point horaIngreso = aux->getDato().getHora();
            time_t tiempo = chrono::system_clock::to_time_t(horaIngreso);
            tm *tm = localtime(&tiempo);

            char horaActual[9];
            strftime(horaActual, sizeof(horaActual), "%H:%M:%S", tm);

            
            auto estaEnIntervalo = [&valorInicio, &valorFin, &horaActual]()
            {
                return valorInicio <= horaActual && horaActual <= valorFin;
            };

            if (estaEnIntervalo())
            {
                cout << "========================================" << endl;
                cout << "   AUTOMOVIL REGISTRADO POR HORA" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true;
            }
        }


 else if (criterio == "Año" || criterio == "fecha") {
    
    std::chrono::system_clock::time_point horaIngreso = aux->getDato().getHora();
    std::time_t tiempo = std::chrono::system_clock::to_time_t(horaIngreso);
    std::tm* tm = std::localtime(&tiempo);

    char fechaActual[11];
    std::strftime(fechaActual, sizeof(fechaActual), "%d-%m-%Y", tm); 

    
    auto convertirFechaAFechaSistema = [](const std::string &fechaStr) -> std::chrono::system_clock::time_point {
        std::tm tmFecha = {};
        std::istringstream ss(fechaStr);
        ss >> std::get_time(&tmFecha, "%d-%m-%Y"); 
        return std::chrono::system_clock::from_time_t(std::mktime(&tmFecha)); 
    };

    std::chrono::system_clock::time_point fechaInicioConv = convertirFechaAFechaSistema(valorInicio);
    std::chrono::system_clock::time_point fechaFinConv = convertirFechaAFechaSistema(valorFin);
    
   
    auto estaEnIntervaloFecha = [&fechaInicioConv, &fechaFinConv, &fechaActual]() {
     
        std::tm tmFechaActual = {};
        std::istringstream ss(fechaActual);
        ss >> std::get_time(&tmFechaActual, "%d-%m-%Y");
        std::chrono::system_clock::time_point fechaActualConv = std::chrono::system_clock::from_time_t(std::mktime(&tmFechaActual));
        
        return fechaInicioConv <= fechaActualConv && fechaActualConv <= fechaFinConv;
    };

    if (estaEnIntervaloFecha()) {
        cout << "========================================" << endl;
        cout << "   AUTOMOVIL REGISTRADO POR FECHA" << endl;
        cout << "========================================" << endl;
        cout << aux->getDato() << endl;
        encontrado = true;
    }
}

        aux = aux->getSiguiente();
    } while (aux != primero);

    if (!encontrado)
    {
        cout << "No se encontro ningun automovil con el criterio de busqueda: " << criterio << endl;
    }
}


template <typename T>
void ListaCircularDoble<T>::CargarArchivo(std::string nombreArchivo)
{
  
    std::string fullPath = GetAppDataPath() + nombreArchivo;
    std::ifstream archivo(fullPath);

    if (!archivo.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << ". Creando archivo vacío..." << std::endl;
        std::ofstream nuevoArchivo(nombreArchivo); 
        if (!nuevoArchivo.is_open())
        {
            std::cerr << "Error: No se pudo crear el archivo " << nombreArchivo << std::endl;
            return;
        }
        nuevoArchivo.close(); 
        return;
    }

    std::string linea;
    std::set<int> posicionesOcupadas;
    while (std::getline(archivo, linea))
    {
        std::istringstream ss(linea);
        std::string placa, modelo, color, marca, fechaIngreso, horaSalida, distanciaStr;
        int distancia;

        if (std::getline(ss, placa, ',') &&
            std::getline(ss, modelo, ',') &&
            std::getline(ss, color, ',') &&
            std::getline(ss, marca, ',') &&
            std::getline(ss, fechaIngreso, ',') &&
            std::getline(ss, horaSalida, ',') &&
            std::getline(ss, distanciaStr, ','))  // Leer la distancia
        {
            // Convertir distancia a entero
            try
            {
                distancia = std::stoi(distanciaStr);
            }
            catch (const std::invalid_argument& e)
            {
                std::cerr << "Error al convertir la distancia: " << distanciaStr << std::endl;
                continue;
            }

            placa = descifrarTexto(placa);

            std::tm tm = {};
            std::istringstream ssFecha(fechaIngreso);
            ssFecha >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
            if (ssFecha.fail())
            {
                std::cerr << "Error en el formato de la fecha de ingreso: " << fechaIngreso << std::endl;
                continue;
            }
            auto horaIngreso = std::chrono::system_clock::from_time_t(std::mktime(&tm));

            std::chrono::system_clock::time_point horaSalidaParsed;
            if (horaSalida == "N/A" || horaSalida.empty())
            {
                horaSalidaParsed = std::chrono::system_clock::time_point();
            }
            else
            {
                std::tm tmSalida = {};
                std::istringstream ssHoraSalida(horaSalida);
                ssHoraSalida >> std::get_time(&tmSalida, "%a %b %d %H:%M:%S %Y");
                if (ssHoraSalida.fail())
                {
                    std::cerr << "Error en el formato de la hora de salida: " << horaSalida << std::endl;
                    horaSalidaParsed = std::chrono::system_clock::time_point();
                }
                else
                {
                    horaSalidaParsed = std::chrono::system_clock::from_time_t(std::mktime(&tmSalida));
                }
            }

           
            T coche(placa, modelo, color, marca, horaIngreso, horaSalidaParsed, distancia);  

            this->insertar(coche);
        }
        else
        {
            std::cerr << "Error: Formato de línea inválido: " << linea << std::endl;
        }
    }

    archivo.close();
}


template <typename T>
void ListaCircularDoble<T>::GuardarArchivo(std::string nombreArchivo)
{
    std::string fullPath = GetAppDataPath() + nombreArchivo;
    std::ofstream archivo(fullPath);

    if (!archivo.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << ". Creando archivo nuevo..." << std::endl;
        std::ofstream nuevoArchivo(nombreArchivo);
        if (!nuevoArchivo.is_open())
        {
            std::cerr << "Error: No se pudo crear el archivo " << nombreArchivo << std::endl;
            return;
        }
        nuevoArchivo.close();
        return;
    }

    std::cout << "Abriendo archivo para guardar los datos..." << std::endl;

    Nodo<T> *actual = primero;
    do
    {
        T coche = actual->getDato();

        std::string placaCifrada = cifrarTexto(coche.getPlaca());
        auto horaIngreso = coche.getHora();
        std::time_t horaIngresoTime = std::chrono::system_clock::to_time_t(horaIngreso);
        std::tm tmHoraIngreso = *std::localtime(&horaIngresoTime);

        auto horaSalida = coche.getHoraSalida();
        std::ostringstream horaSalidaStream;

        if (horaSalida != std::chrono::system_clock::time_point())
        {
            std::time_t horaSalidaTime = std::chrono::system_clock::to_time_t(horaSalida);
            std::tm tmHoraSalida = *std::localtime(&horaSalidaTime);
            horaSalidaStream << std::put_time(&tmHoraSalida, "%a %b %d %H:%M:%S %Y");
        }
        else
        {
            horaSalidaStream << "N/A";
        }

        
        int posicion = coche.getposicion(); 

       
        archivo << placaCifrada << ","
                << coche.getModelo() << ","
                << coche.getColor() << ","
                << coche.getMarca() << ","
                << std::put_time(&tmHoraIngreso, "%a %b %d %H:%M:%S %Y") << ","
                << horaSalidaStream.str() << ","
                << posicion<< std::endl;  // Guardar la posicion(int)

        actual = actual->getSiguiente();
    } while (actual != primero);

    archivo.close();
}


template <typename T>
string ListaCircularDoble<T>::cifrarTexto(const std::string &texto)

{
    std::string textoCifrado = texto;

    for (char &c : textoCifrado)
    {
        if (isdigit(c))
        {
            c = ((c - '0' + 2) % 10) + '0';
        }
        else if (isalpha(c))
        {
            if (isupper(c))
            {
                c = ((c - 'A' + 2) % 26) + 'A';
            }
            else
            {
                c = ((c - 'a' + 2) % 26) + 'a';
            }
        }
    }

    return textoCifrado;
}

template <typename T>
string ListaCircularDoble<T>::descifrarTexto(const std::string &texto)
{
    std::string textoDescifrado = texto;

    for (char &c : textoDescifrado)
    {
        if (isdigit(c))
        {
            c = ((c - '0' - 2 + 10) % 10) + '0';
        }
        else if (isalpha(c))
        {
            if (isupper(c))
            {
                c = ((c - 'A' - 2 + 26) % 26) + 'A';
            }
            else
            {
                c = ((c - 'a' - 2 + 26) % 26) + 'a';
            }
        }
    }

    return textoDescifrado;
}

template <typename T>
bool ListaCircularDoble<T>::estaVacia() const
{
    return primero == nullptr;
}

template <typename T>
void ListaCircularDoble<T>::salirDelParqueadero(const std::string &placa)
{
    Nodo<T> *actual = primero;
    bool encontrado = false;

    do
    {
        T coche = actual->getDato();

        if (coche.getPlaca() == placa)
        {
            if (coche.getHoraSalida() != std::chrono::system_clock::time_point())
            {
                actual = actual->getSiguiente();
                continue;
            }

            auto ahora = std::chrono::system_clock::now();
            coche.setHoraSalida(ahora);
            actual->setDato(coche);

            std::cout << "El coche con placa " << placa << " ha salido del parqueadero." << std::endl;
            encontrado = true;
        }

        actual = actual->getSiguiente();
    } while (actual != primero);

    if (encontrado)
    {
        GuardarArchivo("autos_historial.txt");
    }
    else
    {
        std::cerr << "Coche con placa " << placa << " no encontrado en el parqueadero." << std::endl;
    }
}

template <typename T>
void ListaCircularDoble<T>::GuardarPropietarios(const std::string& nombreArchivo)
{
    std::string fullPath = GetAppDataPath() + nombreArchivo;
    std::ofstream archivo(fullPath);
    
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo para escritura: " << nombreArchivo << endl;
        return;
    }

    Nodo<T>* actual = primero;
    do {
        archivo << actual->getDato().getNombre() << ","
                << actual->getDato().getApellido() << ","
                << actual->getDato().getCedula() << ","
                << actual->getDato().getCorreo() << ",";

        vector<string> placas = actual->getDato().getPlacas();
        for (size_t i = 0; i < placas.size(); ++i)
        {
            archivo << placas[i];
            if (i < placas.size() - 1)
            {
                archivo << ",";
            }
        }
        archivo << endl;
        actual = actual->getSiguiente();
    } while (actual != primero);

    archivo.close();
}

template <typename T>
void ListaCircularDoble<T>::CargarPropietarios(const std::string& nombreArchivo)
{
    std::string fullPath = GetAppDataPath() + nombreArchivo;
    std::ifstream archivo(fullPath);

    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo para lectura: " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string nombre, apellido, cedula, correo, placasStr;

        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, cedula, ',');
        getline(ss, correo, ',');
        getline(ss, placasStr);

        vector<string> placas;
        stringstream ssPlacas(placasStr);
        string placa;
        while (getline(ssPlacas, placa, ','))
        {
            placas.push_back(placa);
        }

        T propietario(nombre, apellido, cedula, correo);
        for (const auto& p : placas)
        {
            propietario.agregarPlaca(p);
        }

        this->insertar(propietario);
    }

    archivo.close();
}
template <typename T>
void ListaCircularDoble<T>::BusquedaAvanzadaPropietario(string criterio, string valorInicio, string valorFin)
{
    if (primero == nullptr)
    {
        cout << "La lista esta vacia." << endl;
        return;
    }

    if (criterio != "hora")
    {
        transform(valorInicio.begin(), valorInicio.end(), valorInicio.begin(), ::tolower);
    }

    Nodo<T> *aux = primero;
    bool encontrado = false;

    do
    {
        if (criterio == "cedula")
        {
            string cedula = aux->getDato().getCedula();
            transform(cedula.begin(), cedula.end(), cedula.begin(), ::tolower);
            if (cedula == valorInicio)
            {
                cout << "========================================" << endl;
                cout << "   PROPIETARIO REGISTRADO POR CEDULA" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true;
            }
        }
        else if (criterio == "correo")
        {
            string correo = aux->getDato().getCorreo();
            transform(correo.begin(), correo.end(), correo.begin(), ::tolower);
            if (correo == valorInicio)
            {
                cout << "========================================" << endl;
                cout << "   PROPIETARIO REGISTRADO POR CORREO" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true;
            }
        }
        else if (criterio == "nombre")
        {
            string nombre = aux->getDato().getNombre();
            transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
            if (nombre == valorInicio)
            {
                cout << "========================================" << endl;
                cout << "   PROPIETARIO REGISTRADO POR NOMBRE" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true;
            }
        }
        else if (criterio == "apellido")
        {
            string apellido = aux->getDato().getApellido();
            transform(apellido.begin(), apellido.end(), apellido.begin(), ::tolower);
            if (apellido == valorInicio)
            {
                cout << "========================================" << endl;
                cout << "   PROPIETARIO REGISTRADO POR APELLIDO" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true;
            }
        }

        aux = aux->getSiguiente();
    } while (aux != primero);

    if (!encontrado)
    {
        cout << "No se encontro ningun propietario con el criterio de busqueda: " << criterio << endl;
    }
}
