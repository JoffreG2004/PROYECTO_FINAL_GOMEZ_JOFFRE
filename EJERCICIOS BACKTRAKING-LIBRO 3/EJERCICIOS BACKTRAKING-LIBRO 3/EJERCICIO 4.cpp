#include <iostream>
#include <cmath>

// Inicialmente, k=0 y reinas[i]=-1.
void print(int reinas[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << reinas[i] << " ";
    }
    std::cout << std::endl;
}

bool comprobar(int reinas[], int n, int k) {
    for (int i = 0; i < k; i++) {
        if (reinas[i] == reinas[k] || abs(reinas[i] - reinas[k]) == abs(i - k)) {
            return false;
        }
    }
    return true;
}

void NReinas(int reinas[], int n, int k) {
    if (k == n) { // Solución (no quedan reinas por colocar)
        print(reinas, n);
    } else { // Aún quedan reinas por colocar (k < n)
        for (reinas[k] = 0; reinas[k] < n; reinas[k]++) {
            if (comprobar(reinas, n, k)) {
                NReinas(reinas, n, k + 1);
            }
        }
    }
}

int main() {
    int n = 8; // Tamaño del tablero (8x8 para el problema de las 8 reinas)
    int reinas[n];
    for (int i = 0; i < n; i++) {
        reinas[i] = -1; // Inicializar el tablero
    }
    NReinas(reinas, n, 0);
    return 0;
}