#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

const int MAX = 1000;

int main() {
    // Usar una sola memoria contigua para A
    vector<double> A(MAX * MAX);
    vector<double> x(MAX);
    vector<double> y(MAX, 0.0);

    // Generador de números aleatorios más eficiente
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    // Inicializar A y x
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            A[i * MAX + j] = dis(gen);
        }
        x[i] = dis(gen);
    }

    // Primer par de bucles
    auto start1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            y[i] += A[i * MAX + j] * x[j];
        }
    }
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo1 = end1 - start1;
    cout << "Tiempo de ejecucion del primer par de bucles: " << tiempo1.count() << " ms" << endl;

    fill(y.begin(), y.end(), 0.0);

    // Segundo par de bucles
    auto start2 = chrono::high_resolution_clock::now();
    for (int j = 0; j < MAX; ++j) {
        for (int i = 0; i < MAX; ++i) {
            y[i] += A[i * MAX + j] * x[j];
        }
    }
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo2 = end2 - start2;
    cout << "Tiempo de ejecucion del segundo par de bucles: " << tiempo2.count() << " ms" << endl;

    return 0;
}
