#include <iostream>
#include <vector>

// La función siguienteValor(k) devuelve el siguiente color
// válido para el vértice k (o 0 si no queda ninguno)
int siguienteValor(int m, int k) {
    static int x[100]; // Assuming a maximum of 100 vertices
    int conflictos;
    int i;
    static int G[100][100] = { // Assuming a maximum of 100 vertices
        {0, 1, 1, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0}
    };

    x[k]++; // Siguiente color…
    while (x[k] <= m) {
        conflictos = 0;
        for (i = 0; i < k; i++)
            if (G[i][k] && x[i] == x[k]) // Vértice adyacente
                conflictos++; // del mismo color.
        if (conflictos == 0)
            return x[k];
        else
            x[k]++;
    }
    return 0; // Ya se han probado los m colores permitidos.
}

void colorea(int m, int k) {
    static int x[100] = {0}; // Inicializar x
    if (k == 5) { // Suponiendo que N = 5
        for (int i = 0; i < 5; ++i) {
            std::cout << x[i] << " "; // Solución con m colores
        }
        std::cout << std::endl;
    } else {
        do {
            x[k] = siguienteValor(m, k);
            if (x[k] != 0)
                colorea(m, k + 1);
        } while (x[k] != 0);
    }
}

int main() {
    int m = 3; // Número de colores
    colorea(m, 0);
    return 0;
}