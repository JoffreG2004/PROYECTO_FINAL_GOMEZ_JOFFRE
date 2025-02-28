#include <iostream>
#include <vector>

void backtrack(std::vector<int>& x, int n) {
    int k = 1;
    while (k > 0) {
        if (k <= n) { // Ajustar la condición para que k no exceda n
            if (x[k-1] < n) {
                x[k-1] = x[k-1] + 1;
                k = k + 1;
            } else {
                x[k-1] = 0;
                k = k - 1;
            }
            for (int i = 0; i < k; ++i) {
                std::cout << x[i] << " ";
            }
            std::cout << std::endl; // Mostrar solución x[1..k]
        } else {
            k = k - 1;
        }
    }
}

int main() {
    std::vector<int> x(10); // Tamaño de ejemplo, ajustar según sea necesario
    int n = x.size();
    backtrack(x, n);
    return 0;
}