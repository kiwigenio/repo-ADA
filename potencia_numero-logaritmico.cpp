#include <iostream>
#include <chrono>

long long potencia_recursivo(long long base, int exp, long long mod) {
    if (exp == 0) return 1;
    long long mitad = potencia_recursivo(base, exp / 2, mod);
    long long resultado = (mitad * mitad) % mod;
    if (exp % 2 != 0) {
        resultado = (resultado * (base % mod)) % mod;
    }
    return resultado;
}

long long potencia_iterativo(long long base, int exp, long long mod) {
    long long resultado = 1;
    base %= mod;

    while (exp > 0) {
        if (exp & 1) {
            resultado = (resultado * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }

    return resultado;
}

int main() {
    long long base = 2;
    int exp = 1000000;
    long long mod = 1e9 + 7;

    // Medicion recursiva
    auto inicio_recursivo = std::chrono::high_resolution_clock::now();
    long long resultado_recursivo = potencia_recursivo(base, exp, mod);
    auto fin_recursivo = std::chrono::high_resolution_clock::now();
    auto duracion_recursivo = std::chrono::duration_cast<std::chrono::microseconds>(fin_recursivo - inicio_recursivo);

    // Medicion iterativa
    auto inicio_iterativo = std::chrono::high_resolution_clock::now();
    long long resultado_iterativo = potencia_iterativo(base, exp, mod);
    auto fin_iterativo = std::chrono::high_resolution_clock::now();
    auto duracion_iterativo = std::chrono::duration_cast<std::chrono::microseconds>(fin_iterativo - inicio_iterativo);

    std::cout << "Resultado (mod " << mod << "): " << resultado_recursivo << std::endl;
    std::cout << "Tiempo recursivo O(log_n): " << duracion_recursivo.count() << " us" << std::endl;
    std::cout << "Tiempo iterativo O(log_n): " << duracion_iterativo.count() << " us" << std::endl;

    return 0;
}