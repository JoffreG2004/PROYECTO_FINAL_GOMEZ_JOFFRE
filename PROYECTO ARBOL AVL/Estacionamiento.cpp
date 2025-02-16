#include <curl/curl.h>
#include "Estacionamiento.h"
#include <json/json.h>
#include <thread>
#include <nlohmann/json.hpp>


using json = nlohmann::json;
extern void iniciarFlask();


Estacionamiento::Estacionamiento() {

}

void Estacionamiento::ocuparEspacio(int espacio, Coche& coche) {
    while (espacio < 0 || espacio >= TAMANIO || espacioOcupado(espacio)) {
       
        espacio = obtenerEspacioAleatorio();  
    
    }
    
    espaciosOcupados[espacio] = coche;
    std::cout << "Coche asignado al espacio " << espacio << "." << std::endl;
}


size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        // Manejar errores de memoria
        return 0;
    }
    return newLength;
}

int Estacionamiento::obtenerEspacioOptimo() {
    // Iniciar Flask en un hilo separado
    std::thread flaskThread(iniciarFlask);
    flaskThread.detach();

    // Esperar 2 segundos para que Flask esté listo
    std::this_thread::sleep_for(std::chrono::seconds(2));

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "http://127.0.0.1:5000/asignar_espacio";
        std::cout << "[DEBUG] Solicitando espacio a: " << url << std::endl;

        // Configurar opciones de libcurl
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Realizar la solicitud HTTP
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "[ERROR] Fallo en HTTP: " << curl_easy_strerror(res) << std::endl;
            return -1;
        }

        std::cout << "[DEBUG] Respuesta cruda de la API: " << readBuffer << std::endl;

        try {
            // Parsear la respuesta JSON
            json jsonResponse = json::parse(readBuffer);

            // Extraer el array "espacio_asignado"
            if (jsonResponse.contains("espacio_asignado") && jsonResponse["espacio_asignado"].is_array()) {
                int first = jsonResponse["espacio_asignado"][0];
                int second = jsonResponse["espacio_asignado"][1];

                // Combinar los valores en un único número
                int espacio = first * 10 + second;
                std::cout << "[DEBUG] Espacio asignado por API: " << espacio << std::endl;
                return espacio;
            } else {
                std::cerr << "[ERROR] El campo 'espacio_asignado' no es un array o no existe" << std::endl;
            }
        } catch (const json::parse_error& e) {
            std::cerr << "[ERROR] Error al parsear JSON: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Error inesperado: " << e.what() << std::endl;
        }
    }

    return -1;
}




void Estacionamiento::liberarEspacio(const std::string& placa) {
    try {
        
        int espacio = obtenerEspacioPorPlaca(placa); 
        
       
        if (espacioOcupado(espacio)) {
            espaciosOcupados.erase(espacio);  
            std::cout << "Espacio " << espacio << " liberado." << std::endl;
        } else {
            std::cout << "Espacio no ocupado." << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl; 
    }
}

int Estacionamiento::obtenerEspacioPorPlaca(const std::string& placa) {
   
   std::cout << "=== DEBUG: Contenido de espaciosOcupados ===" << std::endl;
if (espaciosOcupados.empty()) {
    std::cout << "El mapa está vacío, no hay coches almacenados." << std::endl;
} else {
    for (const auto& pair : espaciosOcupados) {
        std::cout << "Espacio: " << pair.first << " | Placa: " << pair.second.getPlaca() << std::endl;
    }
}
std::cout << "==========================================" << std::endl;
    for (const auto& pair : espaciosOcupados) {
        const Coche& coche = pair.second;
        std::cout << "  Comparando con placa: " << coche.getPlaca() 
                  << " en espacio " << pair.first << std::endl;

        if (coche.getPlaca() == placa) {
            std::cout << "  -> Coche encontrado en el espacio " << pair.first << std::endl;
            return pair.first;
        }
    }

    std::cout << "  -> Coche NO encontrado." << std::endl;
    throw std::invalid_argument("Coche no encontrado en el estacionamiento.");
}



void Estacionamiento::mostrarEstacionamiento() {
    std::cout << "Estado del Parqueadero:\n";
    
   std::cout << "\n";

   std::cout << " _________" << std::endl;
   std::cout << "| E1 | S1 |" << std::endl;
   std::cout << "|    |    |_____________" << std::endl;
   std::cout << "|    |_______________   |" << std::endl;
   std::cout << "|__________________  |  |" << std::endl;
    for (int i = 0; i < TAMANIO; ++i) {
       
        if (espacioOcupado(i)) {
            std::cout << "[X] ";  
        } else {
            std::cout << "[ ] ";  
         }

   
    if ((i + 1) % 5 == 0) {
        std::cout << "    ";  
    }

    if ((i + 1) % 10 == 0) {
        std::cout << std::endl;  
    }
    }
   std::cout << "                  |  |  |_________" << std::endl;
   std::cout << "                  |  |_______     |" << std::endl;
   std::cout << "                  |_____     |    |" << std::endl;
   std::cout << "                        |    |    |" << std::endl;
   std::cout << "                        | E2 | S2 |" << std::endl;
   std::cout << "                        |____|____|" << std::endl;
   

    std::cout << std::endl;
}

int Estacionamiento::obtenerEspacioAleatorio() {
    int espacio = rand() % TAMANIO;  
    
    while (espacioOcupado(espacio)) {  
        espacio = rand() % TAMANIO;  
    }
    
    return espacio;  
}

int Estacionamiento::getNumeroEspacios() const {
    return TAMANIO; 
}

bool Estacionamiento::espacioOcupado(int espacio) {
    return espaciosOcupados.find(espacio) != espaciosOcupados.end();  
}

Coche Estacionamiento::obtenerCocheEnEspacio(int espacio) {
        if (espacioOcupado(espacio)) {
            return espaciosOcupados[espacio];
        }
        return Coche();
    }


void Estacionamiento::vaciarEstacionamiento() {
    espaciosOcupados.clear();  
    std::cout << "Estacionamiento vaciado correctamente." << std::endl;
}

    vector<int> Estacionamiento::obtenerTodosLosEspacios() {
        vector<int> espacios;
        for (const auto& it : espaciosOcupados) {
            espacios.push_back(it.first);
        }
        return espacios;
    }
        int Estacionamiento::buscarCocheCercano(string salida) {
        vector<int> espacios = obtenerTodosLosEspacios();

        if (espacios.empty()) {
            cout << "No hay coches en el estacionamiento." << endl;
            return -1;
        }

       
        vector<int> prioridad = {4, 5, 3, 6, 2, 7, 1, 8, 0, 9};

       
        auto prioridadOrdenamiento = [&](int a, int b) {
            string strA = to_string(a);
            string strB = to_string(b);

            
            if (salida == "1") { 
                if (strA[0] != strB[0])
                    return strA[0] < strB[0];
            } else if (salida == "2") {
                if (strA[0] != strB[0])
                    return strA[0] > strB[0];
            }

            
            if (strA.length() > 1 && strB.length() > 1) {
                int segundoA = strA[1] - '0';
                int segundoB = strB[1] - '0';

                return find(prioridad.begin(), prioridad.end(), segundoA) <
                       find(prioridad.begin(), prioridad.end(), segundoB);
            }

            return false;
        };

       
        sort(espacios.begin(), espacios.end(), prioridadOrdenamiento);

        return espacios.front(); 
    }

    void Estacionamiento::obtenerEstadoJSON() {
        Json::Value estado;
        estado["espacios"] = Json::arrayValue;  
    
       
        for (int i = 0; i < TAMANIO; ++i) {
            Json::Value espacio;
            espacio["id"] = i; 
    
            
            bool ocupado = espacioOcupado(i);  
            espacio["ocupado"] = ocupado;  
    
            
            estado["espacios"].append(espacio);
        }
        
        
        std::string estado_json = estado.toStyledString();
        
        
        std::ofstream file("estado_parqueadero.json");
        if (file.is_open()) {
            file << estado_json;
            file.close();
            std::cout << "Estado del parqueadero guardado en estado_parqueadero.json" << std::endl;
        } else {
            std::cerr << "Error al abrir el archivo para escribir el estado" << std::endl;
        }
    }
    