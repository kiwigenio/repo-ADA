#include <iostream>
#include <vector>
#include <chrono>

using matriz_cuadrada = std::vector<std::vector<int>>;

matriz_cuadrada sumar_matrices(const matriz_cuadrada& primera_matriz, const matriz_cuadrada& segunda_matriz) {
    int dimension = primera_matriz.size();
    matriz_cuadrada resultado_suma(dimension, std::vector<int>(dimension, 0));
    for (int fila = 0; fila < dimension; ++fila) {
        for (int columna = 0; columna < dimension; ++columna) {
            resultado_suma[fila][columna] = primera_matriz[fila][columna] + segunda_matriz[fila][columna];
        }
    }
    return resultado_suma;
}

matriz_cuadrada restar_matrices(const matriz_cuadrada& primera_matriz, const matriz_cuadrada& segunda_matriz) {
    int dimension = primera_matriz.size();
    matriz_cuadrada resultado_resta(dimension, std::vector<int>(dimension, 0));
    for (int fila = 0; fila < dimension; ++fila) {
        for (int columna = 0; columna < dimension; ++columna) {
            resultado_resta[fila][columna] = primera_matriz[fila][columna] - segunda_matriz[fila][columna];
        }
    }
    return resultado_resta;
}

matriz_cuadrada multiplicacion_cubica(const matriz_cuadrada& primera_matriz, const matriz_cuadrada& segunda_matriz) {
    int dimension = primera_matriz.size();
    matriz_cuadrada resultado(dimension, std::vector<int>(dimension, 0));
    for (int fila = 0; fila < dimension; ++fila) {
        for (int columna = 0; columna < dimension; ++columna) {
            for (int paso_intermedio = 0; paso_intermedio < dimension; ++paso_intermedio) {
                resultado[fila][columna] += primera_matriz[fila][paso_intermedio] * segunda_matriz[paso_intermedio][columna];
            }
        }
    }
    return resultado;
}

matriz_cuadrada multiplicacion_strassen(const matriz_cuadrada& primera_matriz, const matriz_cuadrada& segunda_matriz) {
    int dimension = primera_matriz.size();
    if (dimension <= 32) {
        return multiplicacion_cubica(primera_matriz, segunda_matriz);
    }
    int mitad = dimension / 2;
    matriz_cuadrada primera_arriba_izquierda(mitad, std::vector<int>(mitad));
    matriz_cuadrada primera_arriba_derecha(mitad, std::vector<int>(mitad));
    matriz_cuadrada primera_abajo_izquierda(mitad, std::vector<int>(mitad));
    matriz_cuadrada primera_abajo_derecha(mitad, std::vector<int>(mitad));

    matriz_cuadrada segunda_arriba_izquierda(mitad, std::vector<int>(mitad));
    matriz_cuadrada segunda_arriba_derecha(mitad, std::vector<int>(mitad));
    matriz_cuadrada segunda_abajo_izquierda(mitad, std::vector<int>(mitad));
    matriz_cuadrada segunda_abajo_derecha(mitad, std::vector<int>(mitad));

    for (int fila = 0; fila < mitad; ++fila) {
        for (int columna = 0; columna < mitad; ++columna) {
            primera_arriba_izquierda[fila][columna] = primera_matriz[fila][columna];
            primera_arriba_derecha[fila][columna] = primera_matriz[fila][columna + mitad];
            primera_abajo_izquierda[fila][columna] = primera_matriz[fila + mitad][columna];
            primera_abajo_derecha[fila][columna] = primera_matriz[fila + mitad][columna + mitad];

            segunda_arriba_izquierda[fila][columna] = segunda_matriz[fila][columna];
            segunda_arriba_derecha[fila][columna] = segunda_matriz[fila][columna + mitad];
            segunda_abajo_izquierda[fila][columna] = segunda_matriz[fila + mitad][columna];
            segunda_abajo_derecha[fila][columna] = segunda_matriz[fila + mitad][columna + mitad];
        }
    }
    matriz_cuadrada multiplicacion_primera = multiplicacion_strassen(
        sumar_matrices(primera_arriba_izquierda, primera_abajo_derecha),
        sumar_matrices(segunda_arriba_izquierda, segunda_abajo_derecha)
    );

    matriz_cuadrada multiplicacion_segunda = multiplicacion_strassen(
        sumar_matrices(primera_abajo_izquierda, primera_abajo_derecha),
        segunda_arriba_izquierda
    );

    matriz_cuadrada multiplicacion_tercera = multiplicacion_strassen(
        primera_arriba_izquierda,
        restar_matrices(segunda_arriba_derecha, segunda_abajo_derecha)
    );

    matriz_cuadrada multiplicacion_cuarta = multiplicacion_strassen(
        primera_abajo_derecha,
        restar_matrices(segunda_abajo_izquierda, segunda_arriba_izquierda)
    );

    matriz_cuadrada multiplicacion_quinta = multiplicacion_strassen(
        sumar_matrices(primera_arriba_izquierda, primera_arriba_derecha),
        segunda_abajo_derecha
    );

    matriz_cuadrada multiplicacion_sexta = multiplicacion_strassen(
        restar_matrices(primera_abajo_izquierda, primera_arriba_izquierda),
        sumar_matrices(segunda_arriba_izquierda, segunda_arriba_derecha)
    );

    matriz_cuadrada multiplicacion_septima = multiplicacion_strassen(
        restar_matrices(primera_arriba_derecha, primera_abajo_derecha),
        sumar_matrices(segunda_abajo_izquierda, segunda_abajo_derecha)
    );

    matriz_cuadrada resultado_arriba_izquierda = sumar_matrices(
        restar_matrices(sumar_matrices(multiplicacion_primera, multiplicacion_cuarta), multiplicacion_quinta),
        multiplicacion_septima
    );

    matriz_cuadrada resultado_arriba_derecha = sumar_matrices(multiplicacion_tercera, multiplicacion_quinta);

    matriz_cuadrada resultado_abajo_izquierda = sumar_matrices(multiplicacion_segunda, multiplicacion_cuarta);

    matriz_cuadrada resultado_abajo_derecha = sumar_matrices(
        sumar_matrices(restar_matrices(multiplicacion_primera, multiplicacion_segunda), multiplicacion_tercera),
        multiplicacion_sexta
    );

    matriz_cuadrada matriz_resultado(dimension, std::vector<int>(dimension));
    for (int fila = 0; fila < mitad; ++fila) {
        for (int columna = 0; columna < mitad; ++columna) {
            matriz_resultado[fila][columna] = resultado_arriba_izquierda[fila][columna];
            matriz_resultado[fila][columna + mitad] = resultado_arriba_derecha[fila][columna];
            matriz_resultado[fila + mitad][columna] = resultado_abajo_izquierda[fila][columna];
            matriz_resultado[fila + mitad][columna + mitad] = resultado_abajo_derecha[fila][columna];
        }
    }

    return matriz_resultado;
}

matriz_cuadrada generar_matriz_aleatoria(int dimension) {
    matriz_cuadrada matriz_generada(dimension, std::vector<int>(dimension));
    for (int fila = 0; fila < dimension; ++fila) {
        for (int columna = 0; columna < dimension; ++columna) {
            matriz_generada[fila][columna] = rand() % 10;
        }
    }
    return matriz_generada;
}
int main() {
    std::vector<int> dimensiones_prueba = {64, 128, 256, 512};

    std::cout << "========================================================================\n";
    std::cout << "Dimension (NxN)\tMultiplicacion Clasica O(n^3)\tStrassen O(n^2.81)\n";
    std::cout << "========================================================================\n";

    for (int dimension_actual : dimensiones_prueba) {
        matriz_cuadrada primera_prueba = generar_matriz_aleatoria(dimension_actual);
        matriz_cuadrada segunda_prueba = generar_matriz_aleatoria(dimension_actual);

        auto tiempo_inicio_cubico = std::chrono::high_resolution_clock::now();
        matriz_cuadrada resultado_cubico = multiplicacion_cubica(primera_prueba, segunda_prueba);
        auto tiempo_fin_cubico = std::chrono::high_resolution_clock::now();
        auto duracion_cubica = std::chrono::duration_cast<std::chrono::milliseconds>(tiempo_fin_cubico - tiempo_inicio_cubico);

        auto tiempo_inicio_strassen = std::chrono::high_resolution_clock::now();
        matriz_cuadrada resultado_strassen = multiplicacion_strassen(primera_prueba, segunda_prueba);
        auto tiempo_fin_strassen = std::chrono::high_resolution_clock::now();
        auto duracion_strassen = std::chrono::duration_cast<std::chrono::milliseconds>(tiempo_fin_strassen - tiempo_inicio_strassen);

        std::cout << dimension_actual << "x" << dimension_actual << "\t\t"
                  << duracion_cubica.count() << " ms\t\t\t\t"
                  << duracion_strassen.count() << " ms\n";
    }

    std::cout << "========================================================================\n";
    return 0;
}