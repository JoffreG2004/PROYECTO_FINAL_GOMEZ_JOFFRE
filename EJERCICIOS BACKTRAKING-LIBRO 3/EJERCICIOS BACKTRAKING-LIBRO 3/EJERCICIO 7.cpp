// X[1..k-1] ya determinados, W[j] en orden creciente.
// Se supone que W[1]<=M y que Σ1..nW[i]>=M.
#include <iostream>
#include <vector>

void print(const std::vector<int>& X, int k) {
    for (int i = 1; i <= k; ++i) {
        std::cout << X[i] << " ";
    }
    std::cout << std::endl;
}

void SumaSubconjuntos(int k, int s, int r, const std::vector<int>& W, std::vector<int>& X, int M) { // s = Σ1..k-1W[i]X[i]
    // r = ΣΣk..nW[j]
    X[k] = 1; // Nótese que s+W[k] <= M, ya que Bk-1 == true
    if (s + W[k] == M) { // Solución
        print(X, k);
    } else {
        if (s + W[k] + W[k + 1] <= M)
            SumaSubconjuntos(k + 1, s + W[k], r - W[k], W, X, M);
        if ((s + r - W[k] >= M) && (s + W[k + 1] <= M)) {
            X[k] = 0;
            SumaSubconjuntos(k + 1, s, r - W[k], W, X, M);
        }
    }
}

int main() {
    int n = 6; // Número de elementos en el conjunto
    int M = 30; // Suma objetivo
    std::vector<int> W = {0, 5, 10, 12, 13, 15, 18}; // Conjunto de elementos (W[0] no se usa)
    std::vector<int> X(n + 1, 0); // Vector de solución

    int totalSum = 0;
    for (int i = 1; i <= n; ++i) {
        totalSum += W[i];
    }

    SumaSubconjuntos(1, 0, totalSum, W, X, M);
    return 0;
}