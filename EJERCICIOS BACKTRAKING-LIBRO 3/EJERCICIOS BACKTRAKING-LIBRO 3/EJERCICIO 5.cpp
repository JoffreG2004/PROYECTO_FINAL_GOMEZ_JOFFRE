#include <iostream>
#include <cmath>

bool comprobar(int reinas[], int n, int k) {
    for (int i = 0; i < k; i++) {
        if (reinas[i] == reinas[k] || abs(reinas[i] - reinas[k]) == abs(i - k)) {
            return false;
        }
    }
    return true;
}

bool NReinas(int reinas[], int n, int k) {
    if (k == n) { // Caso base: No quedan reinas por colocar
        return true;
    } else { // Aún quedan reinas por colocar (k < n)
        for (int i = 0; i < n; i++) {
            reinas[k] = i;
            if (comprobar(reinas, n, k)) {
                if (NReinas(reinas, n, k + 1)) {
                    return true;
                }
            }
        }
    }
    return false; // La solución está en reinas[] cuando ok == true
}

int main() {
    int n = 8; // Tamaño del tablero (8x8 para el problema de las 8 reinas)
    int reinas[n];
    for (int i = 0; i < n; i++) {
        reinas[i] = 0; // Inicializar el tablero
    }
    if (NReinas(reinas, n, 0)) {
        for (int i = 0; i < n; i++) {
            std::cout << reinas[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No se encontró solución" << std::endl;
    }
    return 0;
}