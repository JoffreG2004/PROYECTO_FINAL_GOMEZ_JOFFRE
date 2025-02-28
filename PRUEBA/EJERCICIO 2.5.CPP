#include <iostream>
#include <cmath>

class BigOProof {
public:
    void check_functions(double n) {
        double log_n = std::log(n);
        double e_log_n = std::exp(1) * log_n;

        std::cout << "Para n = " << n << ":\n";
        std::cout << "  log(n) = " << log_n << "\n";
        std::cout << "  e * log(n) = " << e_log_n << "\n";
        std::cout << "  n = " << n << "\n";

        if (e_log_n <= n) {
            std::cout << "  e * log(n) <= n se cumple.\n";
        } else {
            std::cout << "  e * log(n) > n no se cumple.\n";
        }
    }

    void show_derivatives(double n) {
        double log_n_derivative = 1.0 / n;
        double n_derivative = 1.0;

        std::cout << "Derivadas para n = " << n << ":\n";
        std::cout << "  Derivada de log(n) = " << log_n_derivative << "\n";
        std::cout << "  Derivada de n = " << n_derivative << "\n";

        if (log_n_derivative <= n_derivative) {
            std::cout << "  La derivada de log(n) es menor o igual a la derivada de n.\n";
        } else {
            std::cout << "  La derivada de log(n) es mayor que la derivada de n.\n";
        }
    }
};

int main() {
    BigOProof proof;

    // Comprobación para diferentes valores de n
    proof.check_functions(1);
    proof.check_functions(2);
    proof.check_functions(std::exp(1)); // n = e
    proof.check_functions(5);
    proof.check_functions(10);

    std::cout << "\n";

    // Comprobación de las derivadas para diferentes valores de n
    proof.show_derivatives(1);
    proof.show_derivatives(2);
    proof.show_derivatives(std::exp(1)); // n = e
    proof.show_derivatives(5);
    proof.show_derivatives(10);

    return 0;
}