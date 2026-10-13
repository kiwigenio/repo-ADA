#include <iostream>
#include <vector>
#include <chrono>

using matriz_dos_por_dos = std::vector<std::vector<long long>>;
const long long constante_modulo = 1000000007;
matriz_dos_por_dos multiplicar_matrices(const matriz_dos_por_dos& primera_matriz, const matriz_dos_por_dos& segunda_matriz, long long valor_modulo) {
    matriz_dos_por_dos resultado_multiplicacion = {
        {0, 0},
        {0, 0}
    };
    for (int indice_fila = 0; indice_fila < 2; ++indice_fila) {
        for (int indice_columna = 0; indice_columna < 2; ++indice_columna) {
            for (int indice_intermedio = 0; indice_intermedio < 2; ++indice_intermedio) {
                long long producto_actual = (primera_matriz[indice_fila][indice_intermedio] * segunda_matriz[indice_intermedio][indice_columna]) % valor_modulo;
                resultado_multiplicacion[indice_fila][indice_columna] = (resultado_multiplicacion[indice_fila][indice_columna] + producto_actual) % valor_modulo;
            }
        }
    }
    return resultado_multiplicacion;
}

matriz_dos_por_dos potencia_logaritmica_matriz(matriz_dos_por_dos matriz_origen, long long valor_exponente, long long valor_modulo) {
    matriz_dos_por_dos matriz_acumulada = {
        {1, 0},
        {0, 1}
    };
    while (valor_exponente > 0) {
        if (valor_exponente % 2 != 0) {
            matriz_acumulada = multiplicar_matrices(matriz_acumulada, matriz_origen, valor_modulo);
        }
        matriz_origen = multiplicar_matrices(matriz_origen, matriz_origen, valor_modulo);
        valor_exponente = valor_exponente / 2;
    }
    return matriz_acumulada;
}

long long fibonacci_secuencial(long long posicion_objetivo, long long valor_modulo) {
    if (posicion_objetivo == 0) {
        return 0;
    }
    if (posicion_objetivo == 1) {
        return 1;
    }
    long long valor_anterior = 0;
    long long valor_actual = 1;
    long long valor_siguiente = 0;
    for (long long contador_paso = 2; contador_paso <= posicion_objetivo; ++contador_paso) {
        valor_siguiente = (valor_anterior + valor_actual) % valor_modulo;
        valor_anterior = valor_actual;
        valor_actual = valor_siguiente;
    }
    return valor_actual;
}

long long fibonacci_logaritmico(long long posicion_objetivo, long long valor_modulo) {
    if (posicion_objetivo == 0) {
        return 0;
    }
    matriz_dos_por_dos matriz_base_fibonacci = {
        {1, 1},
        {1, 0}
    };
    matriz_dos_por_dos matriz_potencia = potencia_logaritmica_matriz(matriz_base_fibonacci, posicion_objetivo, valor_modulo);
    return matriz_potencia[0][1];
}

void ejecutar_pruebas_rendimiento() {
    std::vector<long long> lista_tamanos = {1000, 10000, 100000, 500000, 1000000};

    std::cout << "========================================================================\n";
    std::cout << "Tamano (N)\tTiempo Secuencial (us)\tTiempo Logaritmico (us)\n";
    std::cout << "========================================================================\n";

    for (long long tamano_actual : lista_tamanos) {
        auto inicio_secuencial = std::chrono::high_resolution_clock::now();
        long long resultado_secuencial = fibonacci_secuencial(tamano_actual, constante_modulo);
        auto final_secuencial = std::chrono::high_resolution_clock::now();
        auto duracion_secuencial = std::chrono::duration_cast<std::chrono::microseconds>(final_secuencial - inicio_secuencial);

        auto inicio_logaritmico = std::chrono::high_resolution_clock::now();
        long long resultado_logaritmico = fibonacci_logaritmico(tamano_actual, constante_modulo);
        auto final_logaritmico = std::chrono::high_resolution_clock::now();
        auto duracion_logaritmico = std::chrono::duration_cast<std::chrono::microseconds>(final_logaritmico - inicio_logaritmico);

        std::cout << tamano_actual << "\t\t"
                  << duracion_secuencial.count() << " us\t\t\t"
                  << duracion_logaritmico.count() << " us\n";
    }

    std::cout << "========================================================================\n";
}

int main() {
    ejecutar_pruebas_rendimiento();
    return 0;
}