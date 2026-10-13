#include <iostream>
#include <vector>
#include <chrono>

// Definición de tipo para representar una matriz de dos por dos
using matriz_dos_por_dos = std::vector<std::vector<long long>>;
const long long modulo = 1000000007;
matriz_dos_por_dos multiplicar_matrices(const matriz_dos_por_dos& matriz_primera, const matriz_dos_por_dos& matriz_segunda, long long numero_modulo) {
    matriz_dos_por_dos matriz_resultado = {
        {0, 0},
        {0, 0}
    };
    for (int fila = 0; fila < 2; ++fila) {
        for (int columna = 0; columna < 2; ++columna) {
            for (int paso = 0; paso < 2; ++paso) {
                long long producto_parcial = (matriz_primera[fila][paso] * matriz_segunda[paso][columna]) % numero_modulo;
                matriz_resultado[fila][columna] = (matriz_resultado[fila][columna] + producto_parcial) % numero_modulo;
            }
        }
    }
    return matriz_resultado;
}

matriz_dos_por_dos potencia_matriz_recursiva(matriz_dos_por_dos matriz_base, long long exponente, long long numero_modulo) {
    if (exponente == 0) {
        return {
            {1, 0},
            {0, 1}
        };
    }
    matriz_dos_por_dos matriz_mitad = potencia_matriz_recursiva(matriz_base, exponente / 2, numero_modulo);
    matriz_dos_por_dos resultado = multiplicar_matrices(matriz_mitad, matriz_mitad, numero_modulo);
    if (exponente % 2 != 0) {
        resultado = multiplicar_matrices(resultado, matriz_base, numero_modulo);
    }
    return resultado;
}

matriz_dos_por_dos potencia_matriz_iterativa(matriz_dos_por_dos matriz_base, long long exponente, long long numero_modulo) {
    matriz_dos_por_dos acumulador = {
        {1, 0},
        {0, 1}
    };
    while (exponente > 0) {
        if (exponente % 2 != 0) {
            acumulador = multiplicar_matrices(acumulador, matriz_base, numero_modulo);
        }
        matriz_base = multiplicar_matrices(matriz_base, matriz_base, numero_modulo);
        exponente = exponente / 2;
    }
    return acumulador;
}
void imprimir_matriz(const matriz_dos_por_dos& matriz) {
    std::cout << "[ " << matriz[0][0] << " , " << matriz[0][1] << " ]\n";
    std::cout << "[ " << matriz[1][0] << " , " << matriz[1][1] << " ]\n";
}
int main() {
    matriz_dos_por_dos matriz_inicial = {
        {1, 1},
        {1, 0}
    };

    long long exponente_objetivo = 1000000;

    // Medición del enfoque recursivo
    auto tiempo_inicio_recursivo = std::chrono::high_resolution_clock::now();
    matriz_dos_por_dos resultado_recursivo = potencia_matriz_recursiva(matriz_inicial, exponente_objetivo, modulo);
    auto tiempo_final_recursivo = std::chrono::high_resolution_clock::now();
    auto duracion_recursiva = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_final_recursivo - tiempo_inicio_recursivo);

    // Medición del enfoque iterativo
    auto tiempo_inicio_iterativo = std::chrono::high_resolution_clock::now();
    matriz_dos_por_dos resultado_iterativo = potencia_matriz_iterativa(matriz_inicial, exponente_objetivo, modulo);
    auto tiempo_final_iterativo = std::chrono::high_resolution_clock::now();
    auto duracion_iterativa = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_final_iterativo - tiempo_inicio_iterativo);
    std::cout << "Matriz elevada a la " << exponente_objetivo << ":\n";
    imprimir_matriz(resultado_recursivo);
    std::cout << "\nTiempo del metodo recursivo: " << duracion_recursiva.count() << " microsegundos\n";
    std::cout << "Tiempo del metodo iterativo: " << duracion_iterativa.count() << " microsegundos\n";
    return 0;
}