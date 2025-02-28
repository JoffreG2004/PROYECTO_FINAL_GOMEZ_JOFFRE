#include <algorithm> // Include this header for std::find
#include <iostream>

// La función siguienteValor(k) devuelve el siguiente vértice
// válido para la posición k (o 0 si no queda ninguno)
int siguienteValor(int k) {
    static const int N = 5; // Define N
    static int x[N + 1] = {0}; // Define x
    static int G[N + 1][N + 1] = { // Define G
        {0, 1, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1},
        {0, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 0}
    };

    // x[1..k-1] almacena los vértices ya asignados y G[][] es la
    // matriz de adyacencia que representa el grafo de N vértices
    do {
        x[k]++;
        if (G[x[k-1]][x[k]]
            && std::find(x + 1, x + k, x[k]) == x + k
            && (k < N || (k == N && G[x[k]][x[1]]))) {
            return x[k];
        }
    } while (x[k] < N);
    x[k] = 0;
    return 0;
}

void hamiltoniano(int k) {
    static const int N = 5;
    static int x[N + 1] = {0}; // Define x
    if (k == 1) x[k] = 1; // Inicializar el primer vértice
    do {
        siguienteValor(k);
        if (x[k] == 0) return;
        if (k == N) {
            for (int i = 1; i <= N; ++i) {
                std::cout << x[i] << " ";
            }
            std::cout << x[1] << std::endl;
        } else {
            hamiltoniano(k + 1);
        }
    } while (true);
}

int main() {
    hamiltoniano(1);
    return 0;
}