#include <iostream>
#include <cmath>
using namespace std;

bool comprobar(int reinas[], int n, int k) {
    for (int i = 0; i < k; i++) {
        if (reinas[i] == reinas[k] || abs(reinas[i] - reinas[k]) == abs(i - k)) {
            return false;
        }
    }
    return true;
}

void print(int reinas[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (reinas[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void NReinas(int reinas[], int n) {
    int k = 0; // Fila actual = k
    for (int i = 0; i < n; i++) reinas[i] = -1; // Configuración inicial
    while (k >= 0) {
        reinas[k]++; // Colocar reina k en la siguiente columna…
        while ((reinas[k] < n) && !comprobar(reinas, n, k))
            reinas[k]++;
        if (reinas[k] < n) { // Reina colocada
            if (k == n - 1) {
                print(reinas, n); // Solución
            } else {
                k++;
                reinas[k] = -1;
            }
        } else {
            k--;
        }
    }
}

int main() {
    int n = 8; // Tamaño del tablero (8x8 para el problema de las 8 reinas)
    int reinas[n];
    NReinas(reinas, n);
    return 0;
}