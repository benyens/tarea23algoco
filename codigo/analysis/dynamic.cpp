#include "dynamic.h"
#include "costs.h"
#include <algorithm>
#include <vector>

using namespace std;

int edit_distance_dynamic(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Inicialización de la primera columna (costos de eliminación)
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = dp[i - 1][0] + cost_delete(s1[i - 1]);
    }

    // Inicialización de la primera fila (costos de inserción)
    for (int j = 1; j <= m; ++j) {
        dp[0][j] = dp[0][j - 1] + cost_insert(s2[j - 1]);
    }

    // Rellenar la matriz dp usando las operaciones de edición
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int costSub = (s1[i - 1] == s2[j - 1]) ? 0 : cost_replace(s1[i - 1], s2[j - 1]);
            dp[i][j] = min({
                dp[i - 1][j - 1] + costSub,               // Sustitución o coincidencia
                dp[i - 1][j] + cost_delete(s1[i - 1]),     // Eliminación
                dp[i][j - 1] + cost_insert(s2[j - 1])      // Inserción
            });

            // Verificación de transposición según la nueva regla
            if (i > 1 && j > 1 &&
                s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1] &&
                s1[i - 1] != s1[i - 2]) {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + cost_transpose(s1[i - 1], s1[i - 2]));
            }
        }
    }

    return dp[n][m];
}
