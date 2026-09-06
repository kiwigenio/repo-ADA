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

// Mediciones con los valores de { 1000, 2000, 4000, 8000}
void mediciones(){
    
    std::vector<int>tamanio = {1000, 2000, 4000, 8000};
    std::vector<double>tiempo_cubico, tiempo_cuadratica, tiempo_kadane;
    std::cout << "Tabla de mediciones y razones: " << std::endl;
    std::cout << std::setw(6) << "n"
                << std::setw(15) << "Tiempo Cubico"
                << std::setw(10) << "Razon"
                << std::setw(16) << "Tiempo cuadratica"
                << std::setw(10) << "Razon"
                << std::setw(14) << "Tiempo kadane"
                << std::setw(10) << "Razon" << std::endl;
    std::cout << std::string(81, '-') << std::endl;
    for(size_t i = 0 ; i < tamanio.size(); i++ ){
        int n = tamanio[i]; 
        std::vector<int> datos = generar_vector(n);
        // Cubico
        auto inicio = std::chrono::high_resolution_clock::now();
        costo_cubico(datos, n);
        auto fin = std::chrono::high_resolution_clock::now();
        double cubico = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
        tiempo_cubico.push_back(cubico);
        // Cuadratica
        inicio = std::chrono::high_resolution_clock::now();
        costo_cuadratica(datos, n);
        fin = std::chrono::high_resolution_clock::now();
        double cuadratica = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
        tiempo_cuadratica.push_back(cuadratica);
        // Kadane 
        inicio = std::chrono::high_resolution_clock::now();
        costo_kadane(datos, n);
        fin = std::chrono::high_resolution_clock::now();
        double kadane = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
        tiempo_kadane.push_back(kadane);
        std::cout<<std::fixed << std::setprecision(2);
        std::cout<< std::setw(0) <<n; 

        std::cout <<std::setw(13) << (cubico / 1000000.0) << " s";
        if(i == 0 ) std::cout <<std::setw(10) << "-";
        else std::cout <<std::setw(9)<< (cubico / tiempo_cubico[i-1]) << "x"; 

        std::cout<< std::setw(13) << (cuadratica / 1000.0) << "ms"; 
        if(i ==0) std::cout <<std::setw(10) << "-"; 
        else std::cout <<std::setw(9) << (cuadratica / tiempo_cuadratica[i-1]) << "x";

        std::cout << std::setw(11) << (long long)kadane << "us"; 
        if(i== 0) std::cout <<std::setw(10) << "-"; 
        else std::cout <<std::setw(9) << (kadane / tiempo_kadane[i-1]) << "x";

        std::cout <<"\n"; 
    }
    std::cout << std::string(81, '-') <<std::endl;
}

long long  costo_kadane(const std::vector<int> &vector, int size_vector){
    long long aqui = vector[0];
    long long global = vector[0];
    for(int i = 1; i< size_vector; i++){
        aqui = std::max((long long)vector[i], (long long )vector[i] + aqui);
        global = std::max(global, aqui);
    }
    return global;
}

int main(){
    verificacion();
    //mediciones();
    // Prueba con un vector grande
    std::cout << "\nprueba con vector grande 10^8 usando kadane" << std::endl;
    int n= 100000000;
    std::vector<int> vector_grande = generar_vector_grande(n);
    auto inicio = std::chrono::high_resolution_clock::now();
    long long mejor = costo_kadane(vector_grande, n);
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();

    std::cout << "Mejor suma: " << mejor << std::endl;
    std::cout << "Tiempo de ejecucion: " << duracion << " ms" << std::endl;

    return 0;
}
