#include <iostream>
#include <chrono>

long long potenciaSecuencial(long long base, int exp) {
    long long resultado = 1;
    for (int i = 0; i < exp; ++i) {
        resultado *= base;
    }
    return resultado;
}

long long potenciaSecuencialMod(long long base, int exp, long long mod) {
    long long resultado = 1;
    base %= mod;
    for (int i = 0; i < exp; ++i) {
        resultado = (resultado * base) % mod;
    }
    return resultado;
}

int main() {
    long long base = 2;
    int exp = 1000000; 
    long long mod = 1e9 + 7;

    auto inicio = std::chrono::high_resolution_clock::now();
    long long res = potenciaSecuencialMod(base, exp, mod);
    auto fin = std::chrono::high_resolution_clock::now();

    auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);

    std::cout << "Resultado mod " << mod << ": " << res << std::endl;
    std::cout << "Tiempo de ejecucion: " << duracion.count() << " us" << std::endl;

    return 0;
}