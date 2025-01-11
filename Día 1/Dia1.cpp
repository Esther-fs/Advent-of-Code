#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Funcion para calcular la distancia total por divide y venceras 
int calculateDistance(vector<int>& left, vector<int>& right, int start, int end) {
    if (start == end) {
        return abs(left[start] - right[start]);
    }

    int mid = (start + end) / 2;

    // Divide: Calcula las distancias por la izquierda y la derecha 
    int leftDistance = calculateDistance(left, right, start, mid);
    int rightDistance = calculateDistance(left, right, mid + 1, end);

    // Combina los resultados
    return leftDistance + rightDistance;
}

int main() {
    int n;
    cout << " Ingrese el número de elementos en las listas: ";
    cin >> n;

    vector<int> left(n), right(n);

    cout << " Ingrese los elementos de la lista izquierda: ";
    for (int i = 0; i < n; ++i) {
        cin >> left[i];
    } 

    cout << " Ingrese los elementos de la lista derecha: ";
    for (int i = 0; i < n; ++i) {
        cin >> right[i];
    }

    // Sort both lists
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Calculate the total distance using divide and conquer
    int totalDistance = calculateDistance(left, right, 0, n - 1);

    cout << " Distancia total " << totalDistance << endl;

    return 0;
}
