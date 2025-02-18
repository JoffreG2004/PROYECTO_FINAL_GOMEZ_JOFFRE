#include <iostream>
#include <vector>
#include <conio.h>
#include "Propietario.h"
#include "Coche.h"
#include "Lista.h"
#include <thread>
#include <stdlib.h>
#include "Validaciones.h"
#include "ValidacionPlaca.h"
#include "Menu.h"
#include "Ordenamiento.cpp"
#include <atomic>

using namespace std;

Coche coche;

void detenerFlask() {
   
    system("taskkill /IM python.exe /F"); 
}

std::atomic<bool> stopFlaskServer(false);

void iniciarFlask() {
    system("python \"C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\API\\app.py\"");
}

void stopFlask() {
    stopFlaskServer = true;
}

void iniciarFlaskThread() {
    std::thread flaskThread(iniciarFlask);
    flaskThread.detach();
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
}
void stopFlaskThread() {
    stopFlask();
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
}


void iniciarFlaskGrafico() {
    system("start python \"C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\API\\app.py\"");
}

void iniciarFlaskVisEntrada() {
    system("python \"C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\API\\appVizEntrada.py\"");
}

void iniciarFlaskVis() {
    system("python \"C:\\REPOSITORIO\\PROYECTO_FINAL_GOMEZ_JOFFRE\\PROYECTO ARBOL AVL\\API\\appVisualization.py\"");
}

void mostrarGrafico() {
    iniciarFlaskGrafico(); 
    std::this_thread::sleep_for(std::chrono::seconds(2));  
    system("start http://localhost:5000/visualizar_grafo");
}



template <typename T>
void menuEliminarPlaca(ListaCircularDoble<Propietario> &listaPropietarios)
{
    Placa<Propietario> validador;
    Validaciones validaciones;
    system("cls");
    cout << "========================================" << endl;
    cout << "========================================" << endl;
    cout << "    ELIMINAR PLACA DE PROPIETARIO       " << endl;
    cout << "========================================" << endl;
    cout << "========================================" << endl;

    string cedula = validaciones.ingresarCedula("Ingrese la cedula del propietario: ");
    Nodo<T> *aux = listaPropietarios.getPrimero();
    bool encontrado = false;

    do {
        if (aux->getDato().getCedula() == cedula) {
            encontrado = true;
            cout << "========================================" << endl;
            cout << "   PROPIETARIO REGISTRADO" << endl;
            cout << "========================================" << endl;
            cout << aux->getDato() << endl;

            vector<string> placas = aux->getDato().getPlacas();

            if (placas.empty()) {
                cout << "Este propietario no tiene placas asociadas." << endl;
                return;
            }
            
            vector<string> opcionesPlacas = placas;
            opcionesPlacas.push_back("Volver");
            int seleccion = menuInteractivo(opcionesPlacas, "Seleccionar Placa a Eliminar");

            if (seleccion == opcionesPlacas.size() - 1) {
                return;
            }

            string placa = placas[seleccion];

            vector<string> placasActualizadas = aux->getDato().eliminarPlaca(placa);

            
            Propietario propietarioActualizado(aux->getDato().getNombre(), aux->getDato().getApellido(), 
                                               aux->getDato().getCedula(), aux->getDato().getCorreo());

            propietarioActualizado.setPlacas(placasActualizadas);

            
            aux->setDato(propietarioActualizado);
            cout << aux->getDato() << endl;

            listaPropietarios.GuardarPropietarios("propietarios.txt");

            break;
        }
        aux = aux->getSiguiente();
    } while (aux != listaPropietarios.getPrimero() && !encontrado);

    if (!encontrado) {
        cout << "No se encontró un propietario con esa cédula." << endl;
    }
}



void MenuBusquedaBinaria(Estacionamiento &estacionamiento, ArbolAVL &arbolCoches, ListaCircularDoble<Coche> &lista) {
    Validaciones validaciones;
    system("cls");
    cout << "========================================" << endl;
    cout << "========================================" << endl;
    cout << "           SIMULACRO DE SALIDA          " << endl;
    cout << "========================================" << endl;
    cout << "========================================" << endl;

    vector<string> opcionesBinario = {
        "Iniciar simulacro de salida",
        "Ver orden de salida de 3 coches",
        "Buscar coche por posicion",
        "Buscar Ruta",  
        "Simulador de Ruta",
        "Volver al Menu Principal"
    };

    int seleccionBinario = menuInteractivo(opcionesBinario, "Busqueda binaria");

    switch (seleccionBinario) {
        case 0: {
            system("cls");
            cout << "========================================" << endl;
            cout << "           SIMULACRO DE SALIDA          " << endl;
            cout << "========================================" << endl;
            cout << "Este simulacro ayuda a organizar la salida rapida de vehiculos " << endl;
            cout << "en caso de emergencia o desastre." << endl;
            cout << "========================================" << endl;
            cout << "Ingrese la salida que desea utilizar: ( 1,2) ";
            
            int salida = validaciones.ingresarNumero("Ingrese el tipo de salida (1 o 2): ");

            if (salida == 1 || salida == 2) {
                Nodo<Coche>* cocheCercano  = arbolCoches.buscarCocheMasCercanoEnLista(lista, salida); 

                if (cocheCercano != nullptr) {
                    cout << "Coche mas cercano a la salida " << salida << ": " << endl;
                    cout << cocheCercano->getDato() << endl;
                } else {
                    cout << "No se encontro un coche cercano para la salida " << salida << "." << endl;
                }
            } else {
                cout << "Entrada invalida. Solo puede ingresar 1 o 2." << endl;
            }
            break; 
        }
        case 1: {
            system("cls");
            cout << "========================================" << endl;
            cout << "           GESTION DE COCHES            " << endl;
            cout << "========================================" << endl;
            cout << "Ingrese las posiciones de los 3 coches para el simulacro de salida: " << endl;

            int salida = validaciones.ingresarNumero("Ingrese el tipo de salida (1 o 2): ");

            if (salida == 1 || salida == 2) {
                vector<int> orden = arbolCoches.determinarOrdenSalida(salida, lista);

                if (orden.empty()) {
                    cout << "Error al determinar el orden de salida." << endl;
                    return;
                }
            } else {
                cout << "Entrada invalida. Solo puede ingresar 1 o 2." << endl;
            }
            break;
        }
        case 2: {
            system("cls");
            cout << "========================================" << endl;
            cout << "           BUSCAR COCHE POR POSICION    " << endl;
            cout << "========================================" << endl;
            cout << "Ingrese la posicion del coche a buscar: " << endl;

            int posicionBuscada = validaciones.ingresarNumero("Ingrese la posicion del coche: ");

            Nodo<Coche>* cocheEncontrado = arbolCoches.buscarCochePorPosicion(posicionBuscada, lista);
            cout << cocheEncontrado->getDato() << endl;

            break;
        }
        case 3: {
            system("cls");
            cout << "========================================" << endl;
            cout << "           BUSCAR RUTA                 " << endl;
            cout << "========================================" << endl;
            cout << "Realizando la busqueda de la ruta..." << endl;
            
           
            std::thread flaskThread(mostrarGrafico);
            flaskThread.detach(); 

            break;
        }
        case 4: {
            system("cls");
            cout << "========================================" << endl;
            cout << "           SIMULADOR DE RUTA            " << endl;
            cout << "========================================" << endl;
            cout << "Realizando la busqueda de la ruta..." << endl;
            
           
            std::thread flaskThread(iniciarFlaskVis);
            flaskThread.detach(); 

            break;
        }
        case 5: {
            cout << "Saliendo..." << endl;
            return;
        }
    }
}



int menuInteractivo(const vector<string> &opciones, const string &titulo)
{
    int seleccion = 0;
    const int numOpciones = opciones.size();

    while (true)
    {
        system("cls");

        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "        " << titulo << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        for (int i = 0; i < numOpciones; ++i)
        {
            if (i == seleccion)
            {
                cout << " > " << opciones[i] << " < " << endl;
            }
            else
            {
                cout << "   " << opciones[i] << endl;
            }
        }

        cout << "========================================" << endl;

        char tecla = _getch();

        if (tecla == 'a' || tecla == 72)
        {
            seleccion = (seleccion - 1 + numOpciones) % numOpciones;
        }
        else if (tecla == 's' || tecla == 80)
        {
            seleccion = (seleccion + 1) % numOpciones;
        }
        else if (tecla == 13)
        {
            return seleccion;
        }
    }
}

void menuGestionPropietarios(ListaCircularDoble<Propietario> &listaPropietarios)
{ 
    
    bool salirSubmenu = false;
    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "      Menu de Gestion de Propietarios   " << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        vector<string> opcionesPropietarios = {
            "Agregar Propietario",
            "Mostrar Propietarios",
            "Busqueda Avanzada",
            "Eliminar Placa de Propietario",
            "Volver al Menu Principal"};

        int seleccionPropietarios = menuInteractivo(opcionesPropietarios, "Menu de Gestion de Propietarios");
       
       
        switch (seleccionPropietarios)
        {
        case 0:
            {
                Propietario nuevoPropietario = nuevoPropietario.agregarPropietario(listaPropietarios);
                listaPropietarios.insertar(nuevoPropietario);
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                break;
            }
        case 1:
            listaPropietarios.mostrar(listaPropietarios.getPrimero());
            system("pause");
            break;
        case 2:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "          BUSQUEDA AVANZADA             " << endl;
                cout << "========================================" << endl;
                menuBusquedaAvanzadaPropietario(listaPropietarios);
                system("pause");
                break;
            }
        case 3:
          {
            menuEliminarPlaca<Propietario>(listaPropietarios);
           
        }
        case 4:
            salirSubmenu = true;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    }
}

void menuBusquedaAvanzadaPropietario(ListaCircularDoble<Propietario> &listaPropietarios)
{

  Validaciones validaciones;
    vector<string> opcionesBusqueda = {
        "Buscar por Cedula",
        "Buscar por Correo",
        "Buscar por Nombre",
        "Buscar por Apellido",
        "Volver al Menu Principal"};

    while (true)
    {
        int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda Avanzada");

        switch (seleccionBusqueda)
        {
        case 0:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Cedula" << endl;
            cout << "========================================" << endl;
            string cedula;
            cout << "Ingrese la cedula: ";
            cedula = validaciones.ingresarCedula("Ingrese la cedula: ");
            listaPropietarios.BusquedaAvanzadaPropietario("cedula", cedula, "");
            break;
        }
        case 1:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Correo" << endl;
            cout << "========================================" << endl;
            string correo;
            cout << "Ingrese el correo: ";
            correo = validaciones.ingresarCorreo("Ingrese el correo: ");
            listaPropietarios.BusquedaAvanzadaPropietario("correo", correo, "");
            break;
        }
        case 2:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Nombre" << endl;
            cout << "========================================" << endl;
            string nombre;
            cout << "Ingrese el nombre: ";
            nombre = validaciones.ingresarString("Ingrese el nombre: ");
            listaPropietarios.BusquedaAvanzadaPropietario("nombre", nombre, "");
            break;
        }
        case 3:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Apellido" << endl;
            cout << "========================================" << endl;
            string apellido;
            cout << "Ingrese el apellido: ";
            apellido = validaciones.ingresarString("Ingrese el apellido: ");
            listaPropietarios.BusquedaAvanzadaPropietario("apellido", apellido, "");
            break;
        }
        case 4:
        {
            cout << "Saliendo..." << endl;
            return;
        }
        default:
            cout << "Opción invalida. Intentalo de nuevo." << endl;
            break;
        }

        system("pause");
    }


}

void menu(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial, ListaCircularDoble<Propietario> &listaPropietarios,  Estacionamiento &estacionamiento, Parqueadero &parqueadero, ArbolAVL &arbolCoches)
{
    Placa<Coche> validador;
    parqueadero.cargarYAsignarParqueadero(lista, arbolCoches);
    parqueadero.mostrarEstadoParqueadero();
      parqueadero.ObtenerEstadoJSON();
     

    

    vector<string> opciones = {
        "Insertar Coche",
        "Mostrar Lista de Coches",
        "Busqueda de Coche Por Placa",
        "Busqueda Avanzada",
        "Menu de Gestion de Propietarios",
        "Liberar el parqueadero",
        "Ordenar Lista",
        "Ayuda",
        "Mostrar Arbol AVL",
        "Busqueda binaria",
        "Salir"};

    string archivo = "autos.txt";
    string archivoHistorial = "autos_historial.txt";
      
      


    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Parqueadero");

        switch (seleccion)
        {
        case 0:
        {

             parqueadero.mostrarEstadoParqueadero();

            if (listaPropietarios.estaVacia())
            {
                cout << "No hay propietarios registrados. Por favor, registre un propietario antes de continuar." << endl;
                break;
            }

            int espacioLibre = estacionamiento.obtenerEspacioOptimo();
            detenerFlask();
            Coche nuevoCoche = nuevoCoche.InsertarDatos(lista, listaHistorial, listaPropietarios,espacioLibre);
            lista.insertar(nuevoCoche);
            iniciarFlaskVisEntrada();
            lista.GuardarArchivo("autos.txt");
            listaHistorial.insertar(nuevoCoche);
            listaHistorial.GuardarArchivo("autos_historial.txt");

            parqueadero.agregarCoche(nuevoCoche,espacioLibre);
            parqueadero.mostrarEstadoParqueadero();
            parqueadero.ObtenerEstadoJSON();

         

            break;
        }
        case 1:
        {
            bool salirSubmenu = false;

            while (!salirSubmenu)
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "========================================" << endl;
                cout << "         Menu de Lista de Coches        " << endl;
                cout << "========================================" << endl;
                cout << "========================================" << endl;

                vector<string> opcionesLista = {
                    "Mostrar Coches en Parqueadero",
                    "Mostrar Historial Completo de Coches",
                    "Volver al Menu Principal"};

                int seleccionLista = menuInteractivo(opcionesLista, "Menu de Lista de Coches");

                switch (seleccionLista)
                {
                case 0:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "   LISTA DE COCHES EN EL PARQUEADERO    " << endl;
                    cout << "========================================" << endl;
                    lista.mostrar(lista.getPrimero());
                    system("pause");
                    break;
                }
                case 1:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "   HISTORIAL COMPLETO DE COCHES         " << endl;
                    cout << "========================================" << endl;
                    listaHistorial.mostrar(listaHistorial.getPrimero());
                    system("pause");
                    break;
                }
                case 2:
                {
                    cout << "Regresando al menu principal..." << endl;
                    salirSubmenu = true;
                    break;
                }
                default:
                    cout << "Opción inválida. Inténtelo de nuevo." << endl;
                    system("pause");
                    break;
                }
            }
            break;
        }
        case 2:
        {
            bool salirSubmenu = false;
            while (!salirSubmenu)
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "========================================" << endl;
                cout << "        Menu de Busqueda por Placa      " << endl;
                cout << "========================================" << endl;
                cout << "========================================" << endl;

                vector<string> opcionesBusqueda = {
                    "Buscar en Parqueadero",
                    "Buscar en Historial",
                    "Volver al Menu Principal"};

                int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda por Placa");

                switch (seleccionBusqueda)
                {
                case 0:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "   BUSQUEDA DE PLACA EN PARQUEADERO     " << endl;
                    cout << "========================================" << endl;
                    string placa;
                    cout << "Ingrese la placa a buscar(Utilize mayusculas para validar su placa): ";
                    cin >> placa;
                    lista.buscarPorPlaca(placa);
                    system("pause");
                    break;
                }
                case 1:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "   BUSQUEDA DE PLACA EN HISTORIAL       " << endl;
                    cout << "========================================" << endl;
                    string placa;
                    cout << "Ingrese la placa a buscar(Utilize mayusculas para validar su placa): ";
                    cin >> placa;
                    listaHistorial.buscarPorPlaca(placa);
                    system("pause");
                    break;
                }
                case 2:
                {
                    cout << "Regresando al menu principal..." << endl;
                    salirSubmenu = true;
                    break;
                }
                default:
                    cout << "Opción inválida. Inténtelo de nuevo." << endl;
                    system("pause");
                    break;
                }
            }
            break;
        }
        case 3:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "     BIENVENIDOS A LA BUSQUEDA AVANZADA  " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;

            menuBusquedaAvanzada(lista, listaHistorial);
            break;
        }
        case 4:
            menuGestionPropietarios(listaPropietarios);
            break;
        case 5:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "  BIENVENIDOS A LA GESTION DE ESTACIONAMIENTO " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            string placa;
            cout << "Ingrese la placa del coche que  va a  dejar el estacionamiento: ";
            cin >> placa;

            listaHistorial.salirDelParqueadero(placa);
            lista.eliminarPorPlaca(placa);
            parqueadero.inicializarSemilla();
            parqueadero.cargarYAsignarParqueadero(lista, arbolCoches);
            parqueadero.mostrarEstadoParqueadero();
            parqueadero.ObtenerEstadoJSON();
            break;
        }
        case 6:
        {
            menuOrdenar(lista, listaHistorial, listaPropietarios);
            break;
        }
        case 7:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "               (i)AYUDA                 " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            string archivo = "ayuda.html";
            string comando = "start " + archivo;
            system(comando.c_str());
            break;
        }

         case 8:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "          MOSTRAR ARBOL                 " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;

             int altura = arbolCoches.obtenerAltura(arbolCoches.obtenerRaiz()) -1;
                cout << "Altura del arbol: " << altura << endl;

            int profundidad = arbolCoches.obtenerprofundidad(arbolCoches.obtenerRaiz())-1;
            cout << "Profundidad del arbol: " << profundidad << endl;

             cout << "Recorrido Inorden: "; 
              arbolCoches.recorridoInorden(arbolCoches.obtenerRaiz()), cout << endl;
             cout<< "Recorrido Preorden: ";
              arbolCoches.recorridoPreorden(arbolCoches.obtenerRaiz()), cout << endl;
                cout<< "Recorrido Postorden: ";
               arbolCoches.recorridoPostorden(arbolCoches.obtenerRaiz()), cout << endl;


           sf::RenderWindow ventana(sf::VideoMode(1000, 1000), "Menu de Parqueadero");
        sf::Font fuente;
    if (!fuente.loadFromFile("C:\\Windows\\Fonts\\times.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
        return;
    }

   
    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();  
            }
        }

      
        ventana.clear(sf::Color::Black);

       
        sf::Text texto("Mostrando Arbol AVL ", fuente, 24);
texto.setFillColor(sf::Color::White);


sf::FloatRect bounds = texto.getLocalBounds();


float centerX = (ventana.getSize().x - bounds.width) / 2; 
float topY = 10; 

texto.setPosition(centerX, topY);
ventana.draw(texto); 

      

      
        arbolCoches.mostrarArbol(ventana, fuente); 

       
        ventana.display();
    }

            break;
        }

        case 9:
        {
            MenuBusquedaBinaria(estacionamiento, arbolCoches, lista);
            break;
        }
        

        case 10:
        {
            cout << "Saliendo..." << endl;
            return;
        }
        default:
            cout << "Opcion invalida. Inténtelo de nuevo." << endl;
            break;
        }

        system("pause");
    }
}

void menuBusquedaAvanzada(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial)
{

    Validaciones validaciones;
    vector<string> opciones = {
        "Buscar en Parqueadero",
        "Buscar en Historial de Coches",
        "Volver al Menu Principal"};

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Busqueda Avanzada");

        switch (seleccion)
        {
        case 0:
        {
            vector<string> opcionesBusqueda = {
                "Buscar por Modelo",
                "Buscar por Color",
                "Buscar por Anio/Fecha",
                "Buscar por Marca",
                "Buscar por Hora",
                "Volver al Menu Principal"};

            int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda en Parqueadero");

            switch (seleccionBusqueda)
            {
            case 0:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Modelo" << endl;
                cout << "========================================" << endl;
                string modelo;
                cout << "Ingrese el modelo: ";
                modelo = validaciones.ingresarString("Ingrese el modelo: ");
                lista.BusquedaAvanzada("modelo", modelo, "");
                break;
            }
            case 1:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Color" << endl;
                cout << "========================================" << endl;
                string color;
                cout << "Ingrese el color: ";
                color = validaciones.ingresarString("Ingrese el color: ");

                lista.BusquedaAvanzada("color", color, "");
                break;
            }
   case 2: {
    system("cls");
    cout << "========================================" << endl;
    cout << "  Buscar por Anio/Fecha" << endl;
    cout << "========================================" << endl;

    string fechaInicio, fechaFin;

    cout << "Ingrese la fecha de inicio (DD-MM-AAAA): ";
    cin >> fechaInicio;

   
    std::tm tmFechaInicio = {};
    std::istringstream ssInicio(fechaInicio);
    ssInicio >> std::get_time(&tmFechaInicio, "%d-%m-%Y");
    std::chrono::system_clock::time_point fechaInicioConv = std::chrono::system_clock::from_time_t(std::mktime(&tmFechaInicio));

    std::string fechaMinimaStr = "09-11-2024";
    std::tm tmFechaMinima = {};
    std::istringstream ssMinima(fechaMinimaStr);
    ssMinima >> std::get_time(&tmFechaMinima, "%d-%m-%Y");
    std::chrono::system_clock::time_point fechaMinimaConv = std::chrono::system_clock::from_time_t(std::mktime(&tmFechaMinima));

    std::time_t tiempoHoy = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm* tmHoy = std::localtime(&tiempoHoy);
    char fechaHoy[11];
    std::strftime(fechaHoy, sizeof(fechaHoy), "%d-%m-%Y", tmHoy);
    std::chrono::system_clock::time_point fechaHoyConv = std::chrono::system_clock::from_time_t(std::mktime(tmHoy));

    if (fechaInicioConv < fechaMinimaConv) {
        cout << "La fecha de inicio debe ser a partir del 9 de noviembre de 2024." << endl;
        system("pause");
        break;
    }

    if (fechaInicioConv > fechaHoyConv) {
        cout << "La fecha de inicio no puede ser posterior al dia de hoy (" << fechaHoy << ")." << endl;
        system("pause");
        break;
    }

    cout << "Ingrese la fecha de fin (DD-MM-AAAA): ";
    cin >> fechaFin;

    lista.BusquedaAvanzada("fecha", fechaInicio, fechaFin);

    break;
}
            case 3:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Marca" << endl;
                cout << "========================================" << endl;
                string marca;
                cout << "Ingrese la marca: ";
                marca = validaciones.ingresarString("Ingrese la marca: ");

                lista.BusquedaAvanzada("marca", marca, "");
                break;
            }
            case 4:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Hora" << endl;
                cout << "========================================" << endl;
                string HoraEntrada1, HoraEntrada2;
                cout << "Ingrese la hora de entrada 1: ";
                cin >> HoraEntrada1;
                cout << "Ingrese la hora de entrada 2: ";
                cin >> HoraEntrada2;
                lista.BusquedaAvanzada("hora", HoraEntrada1, HoraEntrada2);
                break;
            }
            case 5:
            {
                cout << "Saliendo..." << endl;
                return;
            }
            default:
                cout << "Opcion invalida. Intentalo de nuevo." << endl;
                break;
            }
            break;
        }

        case 1:
        {
            vector<string> opcionesBusqueda = {
                "Buscar por Modelo",
                "Buscar por Color",
                "Buscar por Año/Fecha",
                "Buscar por Marca",
                "Buscar por Hora",
                "Volver al Menu Principal"};

            int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda en Historial");

            switch (seleccionBusqueda)
            {
            case 0:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Modelo" << endl;
                cout << "========================================" << endl;
                string modelo;
                cout << "Ingrese el modelo: ";
                modelo = validaciones.ingresarString("Ingrese el modelo: ");
                listaHistorial.BusquedaAvanzada("modelo", modelo, "");
                break;
            }
            case 1:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Color" << endl;
                cout << "========================================" << endl;
                string color;
                cout << "Ingrese el color: ";
                color = validaciones.ingresarString("Ingrese el color: ");
                listaHistorial.BusquedaAvanzada("color", color, "");
                break;
            }
            case 2:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Año/Fecha" << endl;
                cout << "========================================" << endl;
                string fecha;
                cout << "Ingrese la fecha (DD-MM-AAAA): ";
                cin >> fecha;
                listaHistorial.BusquedaAvanzada("fecha", fecha, "");
                break;
            }
            case 3:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Marca" << endl;
                cout << "========================================" << endl;
                string marca;
                cout << "Ingrese la marca: ";
                marca = validaciones.ingresarString("Ingrese la marca: ");
                listaHistorial.BusquedaAvanzada("marca", marca, "");
                break;
            }
            case 4:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "  Buscar por Hora" << endl;
                cout << "========================================" << endl;
                string HoraEntrada1, HoraEntrada2;
                cout << "Ingrese la hora de entrada 1: ";
                cin >> HoraEntrada1;
                cout << "Ingrese la hora de entrada 2: ";
                cin >> HoraEntrada2;
                listaHistorial.BusquedaAvanzada("hora", HoraEntrada1, HoraEntrada2);
                break;
            }
            case 5:
            {
                cout << "Saliendo..." << endl;
                return;
            }
            default:
                cout << "Opcion invalida. Intentalo de nuevo." << endl;
                break;
            }
            break;
        }

        case 2:
            cout << "Saliendo..." << endl;
            return;

        default:
            cout << "Opcion invalida. Intentalo de nuevo." << endl;
            break;
        }

        system("pause");
    }
}

void menuOrdenarCoches(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial)
{
    bool salirSubmenu = false;

    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "           Menu de Ordenamiento de Coches         " << endl;
        cout << "========================================" << endl;

        vector<string> opcionesMetodo = {
            "Quick Sort",
            "Bucket Sort",
            "Bubble Sort",
            "Shell Sort",
            "Radix sort",
            "Volver al Menu Principal"};

        int seleccionMetodo = menuInteractivo(opcionesMetodo, "Seleccione el metodo de ordenamiento:");

        if (seleccionMetodo == 5)
        {
            salirSubmenu = true;
            continue;
        }

        vector<string> opcionesOrdenar = {
            "Ordenar por Placa",
            "Ordenar por Color",
            "Ordenar por Modelo",
            "Ordenar por Marca",
            "Volver al Menu Principal"};

        int seleccionOrdenar = menuInteractivo(opcionesOrdenar, "Seleccione el criterio de ordenamiento:");

        if (seleccionOrdenar == 4)
        {
            continue;
        }

        system("cls");
        if (seleccionMetodo == 0)
        {
            switch (seleccionOrdenar)
            {
            case 0:
                ordenarLista(lista, [](const Coche &a, const Coche &b)
                             { return a.getPlaca() < b.getPlaca(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por placa y guardada exitosamente." << endl;
                break;
            case 1:
                ordenarLista(lista, [](const Coche &a, const Coche &b)
                             { return a.getColor() < b.getColor(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por color y guardada exitosamente." << endl;
                break;
            case 2:
                ordenarLista(lista, [](const Coche &a, const Coche &b)
                             { return a.getModelo() < b.getModelo(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por modelo y guardada exitosamente." << endl;
                break;
            case 3:
                ordenarLista(lista, [](const Coche &a, const Coche &b)
                             { return a.getMarca() < b.getMarca(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por marca y guardada exitosamente." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        }
        else if (seleccionMetodo == 1)
        {
            std::function<std::string(const Coche &)> getKeyCoche;

            switch (seleccionOrdenar)
            {
            case 0:
                getKeyCoche = [](const Coche &item)
                { return item.getPlaca(); };
                ordenarListaBucket(lista, getKeyCoche);
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por placa y guardada exitosamente." << endl;
                break;
            case 1:
                getKeyCoche = [](const Coche &item)
                { return item.getColor(); };
                ordenarListaBucket(lista, getKeyCoche);
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por color y guardada exitosamente." << endl;
                break;
            case 2:
                getKeyCoche = [](const Coche &item)
                { return item.getModelo(); };
                ordenarListaBucket(lista, getKeyCoche);
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por modelo y guardada exitosamente." << endl;
                break;
            case 3:
                getKeyCoche = [](const Coche &item)
                { return item.getMarca(); };
                ordenarListaBucket(lista, getKeyCoche);
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por marca y guardada exitosamente." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                continue;
            }
        }
        else if (seleccionMetodo == 2)
        {
            switch (seleccionOrdenar)
            {
            case 0:
                ordenarListaBubbleSort(lista, [](const Coche &a, const Coche &b)
                                       { return a.getPlaca() < b.getPlaca(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por placa y guardada exitosamente." << endl;
                break;
            case 1:
                ordenarListaBubbleSort(lista, [](const Coche &a, const Coche &b)
                                       { return a.getColor() < b.getColor(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por color y guardada exitosamente." << endl;
                break;
            case 2:
                ordenarListaBubbleSort(lista, [](const Coche &a, const Coche &b)
                                       { return a.getModelo() < b.getModelo(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por modelo y guardada exitosamente." << endl;
                break;
            case 3:
                ordenarListaBubbleSort(lista, [](const Coche &a, const Coche &b)
                                       { return a.getMarca() < b.getMarca(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por marca y guardada exitosamente." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
            }
        }
        else if (seleccionMetodo == 3)
        { // Shell Sort
            switch (seleccionOrdenar)
            {
            case 0:
                ordenarListaShellSort(lista, [](const Coche &a, const Coche &b)
                                      { return a.getPlaca() < b.getPlaca(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por placa y guardada exitosamente." << endl;
                break;
            case 1:
                ordenarListaShellSort(lista, [](const Coche &a, const Coche &b)
                                      { return a.getColor() < b.getColor(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por color y guardada exitosamente." << endl;
                break;
            case 2:
                ordenarListaShellSort(lista, [](const Coche &a, const Coche &b)
                                      { return a.getModelo() < b.getModelo(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por modelo y guardada exitosamente." << endl;
                break;
            case 3:
                ordenarListaShellSort(lista, [](const Coche &a, const Coche &b)
                                      { return a.getMarca() < b.getMarca(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por marca y guardada exitosamente." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        }
        else if (seleccionMetodo == 4)
        { // Radix
            switch (seleccionOrdenar)
            {
            case 0:
                ordenarListaPorRadix(lista, [](const Coche &coche)
                                     { return coche.getPlaca(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por placa y guardada exitosamente." << endl;
                break;
            case 1:
                ordenarListaPorRadix(lista, [](const Coche &coche)
                                     { return coche.getColor(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por color y guardada exitosamente." << endl;
                break;
            case 2:
                ordenarListaPorRadix(lista, [](const Coche &coche)
                                     { return coche.getModelo(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por modelo y guardada exitosamente." << endl;
                break;
            case 3:
                ordenarListaPorRadix(lista, [](const Coche &coche)
                                     { return coche.getMarca(); });
                lista.GuardarArchivo("autos.txt");
                cout << "Lista ordenada por marca y guardada exitosamente." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        }

        system("pause");
    }
}



void menuOrdenarPropietarios(ListaCircularDoble<Propietario> &listaPropietarios)
{
    bool salirSubmenu = false;

    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "           Menu de Ordenamiento de Propietarios         " << endl;
        cout << "========================================" << endl;

        vector<string> opcionesMetodo = {
            "Quick Sort",
            "Bucket Sort",
            "Bubble Sort",
            "Shell Sort",
            "Radix sort",
            "Volver al Menu Principal"};

        int seleccionMetodo = menuInteractivo(opcionesMetodo, "Seleccione el metodo de ordenamiento:");

        if (seleccionMetodo == 5)
        {
            salirSubmenu = true;
            continue;
        }

        vector<string> opcionesOrdenar = {
            "Ordenar por Nombre",
            "Ordenar por Apellido",
            "Ordenar por Cedula",
            "Ordenar por Correo",
            "Volver al Menu Principal"};

        int seleccionOrdenar = menuInteractivo(opcionesOrdenar, "Seleccione el criterio de ordenamiento:");

        if (seleccionOrdenar == 4)
        {
            continue;
        }

        system("cls");
        if (seleccionMetodo == 0)
        {
            switch (seleccionOrdenar)
            {
            case 0:
                ordenarLista(listaPropietarios, [](const Propietario &a, const Propietario &b)
                             { return a.getNombre() < b.getNombre(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por nombre y guardada exitosamente." << endl;
                break;
            case 1:
                ordenarLista(listaPropietarios, [](const Propietario &a, const Propietario &b)
                             { return a.getApellido() < b.getApellido(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por apellido y guardada exitosamente." << endl;
                break;
            case 2:
                ordenarLista(listaPropietarios, [](const Propietario &a, const Propietario &b)
                             { return a.getCedula() < b.getCedula(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por cedula y guardada exitosamente." << endl;
                break;
            case 3:
                ordenarLista(listaPropietarios, [](const Propietario &a, const Propietario &b)
                             { return a.getCorreo() < b.getCorreo(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por correo y guardada exitosamente." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        }
        else if (seleccionMetodo == 1)
        {
            std::function<std::string(const Propietario &)> getKeyPropietario;

            switch (seleccionOrdenar)
            {
            case 0:
                getKeyPropietario = [](const Propietario &item)
                { return item.getNombre(); };
                ordenarListaBucket(listaPropietarios, getKeyPropietario);
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por nombre y guardada exitosamente." << endl;
                break;
            case 1:
                getKeyPropietario = [](const Propietario &item)
                { return item.getApellido(); };
                ordenarListaBucket(listaPropietarios, getKeyPropietario);
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por apellido y guardada exitosamente." << endl;
                break;
            case 2:
                getKeyPropietario = [](const Propietario &item)
                { return item.getCedula(); };
                ordenarListaBucket(listaPropietarios, getKeyPropietario);
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por cedula y guardada exitosamente." << endl;
                break;
            case 3:
                getKeyPropietario = [](const Propietario &item)
                { return item.getCorreo(); };
                ordenarListaBucket(listaPropietarios, getKeyPropietario);
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por correo y guardada exitosamente." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                continue;
            }
        }
        else if (seleccionMetodo == 2)
        {
            switch (seleccionOrdenar)
            {
            case 0:
                ordenarListaBubbleSort(listaPropietarios, [](const Propietario &a, const Propietario &b)
                                       { return a.getNombre() < b.getNombre(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por nombre y guardada exitosamente." << endl;
                break;
            case 1:
                ordenarListaBubbleSort(listaPropietarios, [](const Propietario &a, const Propietario &b)
                                       { return a.getApellido() < b.getApellido(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por apellido y guardada exitosamente." << endl;
                break;
            case 2:
                ordenarListaBubbleSort(listaPropietarios, [](const Propietario &a, const Propietario &b)
                                       { return a.getCedula() < b.getCedula(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por cedula y guardada exitosamente." << endl;
                break;
            case 3:
                ordenarListaBubbleSort(listaPropietarios, [](const Propietario &a, const Propietario &b)
                                       { return a.getCorreo() < b.getCorreo(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por correo y guardada exitosamente." << endl;
                break;
            default:
                cout << "Opción invalida. Intente de nuevo." << endl;
                break;
            }
        }
        else if (seleccionMetodo == 3)
        { // Shell Sort
            switch (seleccionOrdenar)
            {
            case 0:
                ordenarListaShellSort(listaPropietarios, [](const Propietario &a, const Propietario &b)
                                      { return a.getNombre() < b.getNombre(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por nombre y guardada exitosamente." << endl;
                break;
            case 1:
                ordenarListaShellSort(listaPropietarios, [](const Propietario &a, const Propietario &b)
                                      { return a.getApellido() < b.getApellido(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por apellido y guardada exitosamente." << endl;
                break;
            case 2:
                ordenarListaShellSort(listaPropietarios, [](const Propietario &a, const Propietario &b)
                                      { return a.getCedula() < b.getCedula(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por cedula y guardada exitosamente." << endl;
                break;
            case 3:
                ordenarListaShellSort(listaPropietarios, [](const Propietario &a, const Propietario &b)
                                      { return a.getCorreo() < b.getCorreo(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por correo y guardada exitosamente." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        }
        else if (seleccionMetodo == 4)
        { // Radix
            switch (seleccionOrdenar)
            {
            case 0:
                ordenarListaPorRadix(listaPropietarios, [](const Propietario &propietario)
                                     { return propietario.getNombre(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por nombre y guardada exitosamente." << endl;
                break;
            case 1:
                ordenarListaPorRadix(listaPropietarios, [](const Propietario &propietario)
                                     { return propietario.getApellido(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por apellido y guardada exitosamente." << endl;
                break;
            case 2:
                ordenarListaPorRadix(listaPropietarios, [](const Propietario &propietario)
                                     { return propietario.getCedula(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por cedula y guardada exitosamente." << endl;
                break;
            case 3:
                ordenarListaPorRadix(listaPropietarios, [](const Propietario &propietario)
                                     { return propietario.getCorreo(); });
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                cout << "Lista ordenada por correo y guardada exitosamente." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        }

        system("pause");
    }
}

void menuOrdenar(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial, ListaCircularDoble<Propietario> &listaPropietarios)
{
    bool salirMenu = false;

    while (!salirMenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "           Menu de Ordenamiento         " << endl;
        cout << "========================================" << endl;

        vector<string> opcionesTipo = {
            "Ordenar por Coche",
            "Ordenar por Propietario",
            "Volver al Menu Principal"};

        int seleccionTipo = menuInteractivo(opcionesTipo, "Seleccione el tipo de ordenamiento:");

        if (seleccionTipo == 2)
        {
            salirMenu = true;
            continue;
        }

        if (seleccionTipo == 0)
        {
            menuOrdenarCoches(lista, listaHistorial);
        }
        else if (seleccionTipo == 1)
        {
            menuOrdenarPropietarios(listaPropietarios);
        }
    }
}