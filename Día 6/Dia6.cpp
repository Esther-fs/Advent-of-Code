#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

struct Nodo {
    int i, j, movi, dir;
};

// Función para convertir las coordenadas a una clave única
string generarClave(int i, int j) {
    return to_string(i) + "," + to_string(j);
}

bool esValido(int i, int j, const vector<vector<char>>& tabla) {
    return i >= 0 && j >= 0 && i < tabla.size() && j < tabla[i].size() && tabla[i][j] != 'X' && tabla[i][j] != '#';
}

int Movimiento(vector<vector<char>>& tabla, int i, int j) {
    // Direcciones: 0=Arriba, 1=Derecha, 2=Abajo, 3=Izquierda
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, 1, 0, -1};

    // Crear una tabla hash (unordered_map) para las posiciones visitadas
    unordered_map<string, int> visitados;

    // Usamos una cola para el algoritmo de búsqueda en anchura (BFS)
    queue<Nodo> q;
    q.push({i, j, 0, 0});  // Empujamos el nodo inicial

    while (!q.empty()) {
        Nodo nodo = q.front();
        q.pop();

        int x = nodo.i, y = nodo.j, movi = nodo.movi, dir = nodo.dir;

        // Generamos la clave única para la posición
        string clave = generarClave(x, y);

        // Si ya hemos visitado esta posición con el mismo número de movimientos, la saltamos
        if (visitados.find(clave) != visitados.end()) {
            continue;
        }

        // Marcamos la posición como visitada con el número de movimientos
        visitados[clave] = movi;

        // Si llegamos a una posición válida
        if (tabla[x][y] != 'X' && tabla[x][y] != '#') {
            if (tabla[x][y] != '^') {
                tabla[x][y] = '^';  // Marcamos el camino
                movi++;
            }

            // Probar las 4 direcciones
            for (int d = 0; d < 4; d++) {
                int ni = x + dx[d], nj = y + dy[d];
                if (esValido(ni, nj, tabla)) {
                    q.push({ni, nj, movi, d});
                    tabla[x][y] = 'X';  // Marcamos como visitado
                }
            }
        }
    }
    return -1;  // No encontramos un camino
}

void Busqueda(vector<vector<char>>& tabla, int& i, int& j) {
    for (int I = 0; I < tabla.size(); I++) {
        for (int J = 0; J < tabla[I].size(); J++) {
            if (tabla[I][J] == '^') {
                i = I;
                j = J;
                return;
            }
        }
    }
}

int main() {
    ifstream file("input6.txt");
    string linea;
    vector<vector<char>> tabla;
    int i = 0, j = 0;

    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return 1;
    }

    while (getline(file, linea)) {
        vector<char> c(linea.begin(), linea.end());
        tabla.push_back(c);
    }
    file.close();

    // Buscamos la posición de inicio
    Busqueda(tabla, i, j);
    cout << "Posición inicial: " << i << " " << j << endl;

    int movi = Movimiento(tabla, i, j);
    
    // Mostramos la tabla final
    for (const auto& fila : tabla) {
        for (char c : fila) {
            cout << c;
        }
        cout << endl;
    }
    
    cout << "Movimientos: " << movi << endl;
    return 0;
}
