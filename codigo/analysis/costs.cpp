#include "costs.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<int> costInsert(26);
vector<int> costDelete(26);
vector<vector<int>> costReplace(26, vector<int>(26));
vector<vector<int>> costTranspose(26, vector<int>(26));

void leer_costos() {
    ifstream insert_file("codigo/costos/cost_insert.txt");
    ifstream delete_file("codigo/costos/cost_delete.txt");
    ifstream replace_file("codigo/costos/cost_replace.txt");
    ifstream transpose_file("codigo/costos/cost_transpose.txt");

    if (!insert_file || !delete_file || !replace_file || !transpose_file) {
        std::cerr << "Error al abrir los archivos de costos." << std::endl;
        exit(1);
    }

    for (int i = 0; i < 26; ++i) {
        insert_file >> costInsert[i];
    }

    for (int i = 0; i < 26; ++i) {
        delete_file >> costDelete[i];
    }

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            replace_file >> costReplace[i][j];
        }
    }

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            transpose_file >> costTranspose[i][j];
        }
    }
}

int cost_replace(char a, char b) {
    if (a < 'a' || a > 'z' || b < 'a' || b > 'z') {
        std::cerr << "Error: Caracter fuera del rango esperado: " << a << ", " << b << std::endl;
        return 100;  // Valor alto, pero no lo suficiente para causar desbordamiento.
    }
    return costReplace[a - 'a'][b - 'a'];
}

int cost_insert(char b) {
    if (b < 'a' || b > 'z') {
        std::cerr << "Error: Caracter fuera del rango esperado: " << b << std::endl;
        return 100;  // Valor alto, pero no lo suficiente para causar desbordamiento.
    }
    return costInsert[b - 'a'];
}

int cost_delete(char a) {
    if (a < 'a' || a > 'z') {
        std::cerr << "Error: Caracter fuera del rango esperado: " << a << std::endl;
        return 100;  // Valor alto, pero no lo suficiente para causar desbordamiento.
    }
    return costDelete[a - 'a'];
}

int cost_transpose(char a, char b) {
    if (a < 'a' || a > 'z' || b < 'a' || b > 'z') {
        std::cerr << "Error: Caracter fuera del rango esperado: " << a << ", " << b << std::endl;
        return 100;  // Valor alto, pero no lo suficiente para causar desbordamiento.
    }
    return costTranspose[a - 'a'][b - 'a'];
}
