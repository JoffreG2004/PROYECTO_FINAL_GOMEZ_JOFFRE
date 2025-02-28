#include <iostream>
#include <vector>
#include <algorithm>

int N = 5; // Define N with an appropriate value
std::vector<int> x(N + 1); // Define x with size N+1

// x[1..k-1] almacena los vértices ya asignados
void hamiltoniano(int k);
void print(const std::vector<int>& x);
int siguienteValor(int k); // Declare siguienteValor function

void hamiltoniano(int k)
{
    if (k == N) {
        print(x); // Solución
    } else {
        do {
            x[k] = siguienteValor(k);
            if (x[k] != 0)
                hamiltoniano(k + 1);
        } while (x[k] != 0);
    }
}

void print(const std::vector<int>& x) {
    for (int i = 1; i < x.size(); ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;
}

int siguienteValor(int k) {
    static int G[6][6] = { // Define G
        {0, 1, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1},
        {0, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 0}
    };

    do {
        x[k]++;
        if (x[k] > N) x[k] = 0;
        if (G[x[k-1]][x[k]] && std::find(x.begin() + 1, x.begin() + k, x[k]) == x.begin() + k) {
            return x[k];
        }
    } while (x[k] != 0);
    return 0;
}

int main() {
    x[1] = 1; // Inicializar el primer vértice
    hamiltoniano(2);
    return 0;
}