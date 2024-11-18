#include "brute_force.h"
#include "costs.h"
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

int edit_distance_brute(const string& s1, const string& s2, size_t i, size_t j) {
    // Caso base: si hemos llegado al final de s1
    if (i == s1.length()) {
        int cost = 0;
        for (size_t k = j; k < s2.length(); ++k) {
            cost += cost_insert(s2[k]);
        }
        return cost;
    }

    // Caso base: si hemos llegado al final de s2
    if (j == s2.length()) {
        int cost = 0;
        for (size_t k = i; k < s1.length(); ++k) {
            cost += cost_delete(s1[k]);
        }
        return cost;
    }

    // Costo de sustitución
    int costSub = (s1[i] == s2[j]) ? 0 : cost_replace(s1[i], s2[j]);
    int substitute = costSub + edit_distance_brute(s1, s2, i + 1, j + 1);

    // Costo de inserción
    int insert = cost_insert(s2[j]) + edit_distance_brute(s1, s2, i, j + 1);

    // Costo de eliminación
    int remove = cost_delete(s1[i]) + edit_distance_brute(s1, s2, i + 1, j);

    // Costo de transposición, solo si los caracteres cumplen la nueva condición
    int transpose = INT_MAX;
    if (i + 1 < s1.length() && j + 1 < s2.length() &&
        s1[i] == s2[j + 1] && s1[i + 1] == s2[j]) {
        transpose = cost_transpose(s1[i], s1[i + 1]) +
                    edit_distance_brute(s1, s2, i + 2, j + 2);
    }

    // Retornar el mínimo costo entre las operaciones
    return min({substitute, insert, remove, transpose});
}
