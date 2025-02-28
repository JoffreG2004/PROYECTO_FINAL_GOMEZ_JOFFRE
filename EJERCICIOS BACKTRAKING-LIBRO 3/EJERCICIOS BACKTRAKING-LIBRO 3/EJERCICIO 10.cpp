#include <iostream>
#include <vector>

// x[1..k-1] almacena los colores asignados a los vértices 1..k-1
// Inicialmente, x[i] = 0
const int N = 5; // Define N as needed
std::vector<int> x(N + 1, 0); // Define x as a vector

int siguienteValor(int m, int k) {
    // Implement the logic for siguienteValor
    return (x[k] + 1) % (m + 1);
}

void colorea(int m, int k)
{
    if (k == N) {
        for (int i = 1; i <= N; ++i) {
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
    colorea(m, 1);
    return 0;
}