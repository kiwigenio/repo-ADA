#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <climits>
#include <algorithm>
#include <iomanip>


//CUBICA n^3
int costo_cubico(std::vector<int> &vector, int size_vector){

    int mejor = INT_MIN; 
    for (int i = 0; i<size_vector; i++){
        for(int j = i ; j <size_vector; j++ ) { 
            int suma = 0 ; 
            for( int k = i ; k <= j ; k++){ 
                suma  = suma + vector[k];
            }
            mejor = std::max(mejor, suma);
        }
    }
    return mejor;
}


// CUADRATICA n^2
int costo_cuadratica( std::vector<int> &vector, int size_vector){
    int mejor = INT_MIN;
    for (int i = 0; i < size_vector; i++){
        int suma = 0; 
        for ( int j = i ; j < size_vector; j++){
            suma = suma + vector[j];
            mejor = std::max(mejor, suma);
        }
    }
    return mejor;
}

//KADANE n 
int costo_kadane(std::vector<int> &vector, int size_vector){
    int aqui = vector[0]; 
    int global = vector[0];
    for (int i = 1 ; i< size_vector; i++){
        aqui = std::max(vector[i], vector[i] + aqui);
        global = std::max(global, aqui);
    }
    return global;
}

std::vector<int>generar_vector(int size_vector){
    std::vector<int> vector(size_vector);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);
    for (int i = 0; i < size_vector; i++){
        vector[i] = dis(gen);
    }
    return vector;
}
// verificacion de las 100 pruebas
void verificacion(){ 
    int total_pruebas  = 100; 
    int verificado = true; 

    for(int i = 0 ; i<= total_pruebas; i++ ){ 
        int tamanio= 10 + (rand() % 31);
        std::vector<int> muestra = generar_vector(tamanio);
        int resultado_cubico = costo_cubico(muestra, tamanio);
        int resultado_cuadratica = costo_cuadratica(muestra, tamanio);
        int resultado_kadane = costo_kadane(muestra, tamanio);

        if (resultado_cubico != resultado_cuadratica || resultado_cuadratica != resultado_kadane){
            std::cout<< "resultado cubico: " << resultado_cubico 
            << " resultado cuadratica: " << resultado_cuadratica
            << " resultado kadane: " << resultado_kadane << std::endl;
            verificado = false;
            break;
        }
    }
    if (total_pruebas){
        std::cout<<"salio bien :) " << std::endl;
    }
}

std::vector<int> generar_vector_grande(int size_vector){
    std::vector<int> vector(size_vector);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);
    for(int i =0 ;i <size_vector; i++){
        vector[i] = dis(gen);
    }
    return vector; 
}

int main (){
    verificacion();
    return 0;
}
