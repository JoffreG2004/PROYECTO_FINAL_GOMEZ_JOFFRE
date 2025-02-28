#include <iostream>
#include <vector>

std::vector<int> T(const std::vector<int>& x, int k) {
    std::vector<int> t;
    for (int i = 1; i <= x.size() - 1; ++i) {
        t.push_back(i);
    }
    return t;
}

bool Bk(const std::vector<int>& x, int k) {
    return true; // Asume que siempre es válido, ajustar según el problema
}

bool isSolution(const std::vector<int>& x, int k) {
    return k == x.size() - 1; // Es una solución cuando se llena el vector
}

void printSolution(const std::vector<int>& x, int k) {
    for (int i = 1; i <= k; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;
}

void backtrack(std::vector<int>& x, int k, int n) {
    for (int i : T(x, k-1)) {
        x[k] = i;
        if (Bk(x, k)) {
            if (isSolution(x, k)) {
                printSolution(x, k); // Mostrar solución x[1..k]
            }
            backtrack(x, k+1, n);
        }
    }
}

int main() {
    int n = 10; // Example value for n
    std::vector<int> x(n+1);
    backtrack(x, 1, n);
    return 0;
}