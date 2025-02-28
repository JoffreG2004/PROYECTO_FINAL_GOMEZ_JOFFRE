#include <iostream>
#include <cmath>

// Comprobar si la reina de la fila k está bien colocada
// (si no está en la misma columna ni en la misma diagonal
// que cualquiera de las reinas de las filas anteriores)
// Eficiencia: O(k-1).
bool comprobar(int reinas[], int n, int k) {
    for (int i = 0; i < k; i++) {
        if ((reinas[i] == reinas[k]) || (abs(k - i) == abs(reinas[k] - reinas[i]))) {
            return false;
        }
    }
    return true;
}

// Función para imprimir el tablero
void imprimirTablero(int reinas[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (reinas[i] == j) {
                std::cout << "Q ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

// Función de backtracking para resolver el problema de las N reinas
void resolverNReinas(int reinas[], int n, int k) {
    if (k == n) {
        imprimirTablero(reinas, n);
        std::cout << std::endl;
    } else {
        for (int i = 0; i < n; i++) {
            reinas[k] = i;
            if (comprobar(reinas, n, k)) {
                resolverNReinas(reinas, n, k + 1);
            }
        }
    }
}

int main() {
    int n = 8; // Tamaño del tablero (8x8 para el problema de las 8 reinas)
    int reinas[n];
    resolverNReinas(reinas, n, 0);
    return 0;
}