#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "costs.h"
#include "brute_force.h"
#include "dynamic.h"
#include <cctype>
#include "results.h"

using namespace std;

// Función para leer los datasets.
vector<pair<string, string>> leer_datasets(const string& filename) {
    ifstream dataset_file(filename);
    if (!dataset_file) {
        cerr << "No se pudo abrir el archivo " << filename << endl;
        exit(1);
    }

    vector<pair<string, string>> pares;
    string s1, s2;

    while (getline(dataset_file, s1) && getline(dataset_file, s2)) {
        pares.emplace_back(s1, s2);
    }

    return pares;
}

// Función para medir el tiempo de ejecución.
template <typename F>
int medir_tiempo(const string& label, F f) {
    auto start = chrono::high_resolution_clock::now();
    f();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << label << "tomó " << duration.count() << " microsegundos" << endl;
    cout << "----------------------------------------" << endl;

    return duration.count();
}


void clean_string(string& str) {
    str.erase(remove_if(str.begin(), str.end(),
                             [](unsigned char c) { 
                                 return !(islower(c)); 
                             }),
              str.end());

}

int main() {
    
    cout << "Leyendo costos..." << endl;
    leer_costos();

    string s1, s2;
    

    string carpeta = "codigo/datasets/";
    string dataset_file;
    cout << "Ingrese el nombre del archivo del dataset: ";
    cin >> dataset_file;
    string ruta = carpeta + dataset_file + ".txt";
    vector<pair<string, string>> pares = leer_datasets(ruta);

    int cont = 1;
    for (auto& [s1, s2] : pares) {
        cout << "\nPar de cadenas " << cont << ":" << endl;
        cout << "Cadena 1: " << s1 << endl;
        cout << "Cadena 2: " << s2 << endl;

        clean_string(s1);
        clean_string(s2);

        if (!s1.empty() && s1.back() == '\r') {
            s1.pop_back();
        }
        if (!s2.empty() && s2.back() == '\r') {
            s2.pop_back();
        }

        int input_size = s2.size();

        cout << "\nCalculando distancia mínima usando Fuerza Bruta...\n" << endl;
        int distancia_bruta;

        int tiempo_bruta = medir_tiempo("Fuerza Bruta ", [&](){
            distancia_bruta = edit_distance_brute(s1, s2, 0, 0);
        });
        cout << "La distancia de edición mínima es: " << distancia_bruta << endl;
        
        cout << "----------------------------------------" << endl;

        cout << "\nCalculando distancia mínima usando Programación Dinámica...\n" << endl;
        int distancia_dinamica;
        int tiempo_dinamica = medir_tiempo("Programación Dinámica ", [&](){
            distancia_dinamica = edit_distance_dynamic(s1, s2);
        });
        cout << "La distancia de edición mínima es: " << distancia_dinamica << endl;
        cout << "----------------------------------------\n" << endl;

        if (distancia_bruta == distancia_dinamica) {
            cout << "Las distancias mínimas son iguales." << endl;
        } else {
            cout << "Las distancias mínimas son diferentes." << endl;
        }   
        cout << "----------------------------------------\n" << endl;

        cout << "Escribiendo resultados en results.csv...\n" << endl;

        cout << "----------------------------------------" << endl;
        cout << "----------------------------------------" << endl;
        cout << "----------------------------------------\n" << endl;

        escribir_resultados(dataset_file, to_string(cont), "Fuerza Bruta", to_string(distancia_bruta), tiempo_bruta, input_size);
        escribir_resultados(dataset_file, to_string(cont), "Programación Dinámica", to_string(distancia_dinamica), tiempo_dinamica, input_size);
        cont++;
        
    }
    return 0;
}