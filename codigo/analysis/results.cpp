#include "results.h"
#include <iostream>
#include <fstream>

using namespace std;

void escribir_resultados(const string& tipo_caso, const string& caso, const string& algorithm, const string& resultado, const int& tiempo, const int& input_size) {
    ofstream results_file("codigo/results/results.csv", ios::app);

    if (!results_file) {
        cerr << "No se pudo abrir el archivo results.csv" << endl;
        exit(1);
    }

    // Si el archivo está vacío, se escribe la cabecera
    if (results_file.tellp() == 0) {
        results_file << "Tipo de caso,Número de caso,Algoritmo,Resultado,Tiempo (microsegundos), Tamaño de entrada" << endl;
    }
    

    results_file << tipo_caso << ","  << caso << "," << algorithm << "," << resultado << "," << tiempo << "," << input_size << endl;
}