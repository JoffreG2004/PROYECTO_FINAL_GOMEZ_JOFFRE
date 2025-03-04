#include "ValidacionPlaca.h"
#include <unordered_set>
#include <regex>
#include <algorithm>
#include <stdexcept>
#include <conio.h>  

template <typename T>
string Placa<T>::ingresarPlaca(Nodo<T> *aux) {
    unordered_set<string> provinciasValidas = {
        "A", "B", "C", "E", "G", "H", "I", "J", "K", "L", "M", 
        "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
    };
    
    string placa;
    char tecla;

    while (true) {
        cout << "Ingrese la placa: ";
        placa.clear();

     
        while (true) {
            tecla = _getch();  
         
            if (tecla == 27) {  
                cout << endl;
                return "&";
            }
        
            else if (tecla == '\r') {  
                cout << endl;
                break;
            }
        
            else if (tecla == '\b') {  
                if (!placa.empty()) {
                    placa.pop_back();
                    cout << "\b \b";  
                }
            }
       
            else if (isalnum(tecla)) {  
            
                if (isalpha(tecla)) tecla = toupper(tecla);  

         
                if (placa.length() < 7) {  
                    placa += tecla;
                    cout << tecla;  
                }
            }
        }

        if (placa.empty()) {
            cout << "\nError: La placa no puede estar vacia." << endl;
            continue;
        }

        if (placa.length() != 7) {
            cout << "\nLa placa debe tener 7 caracteres. Intente de nuevo." << endl;
            continue;
        }

        string provincia(1, placa[0]);
        if (!provinciasValidas.count(provincia)) {
            cout << "\nInicial de provincia invalida. Intente de nuevo." << endl;
            continue;
        }

        if (!regex_match(placa, regex("^[A-Z]{1,3}[0-9]{4}$"))) {
            cout << "\nFormato incorrecto. Ejemplo: ABC1234." << endl;
            continue;
        }

        break;  // Placa válida
    }

    return placa;
}

template class Placa<Coche>;