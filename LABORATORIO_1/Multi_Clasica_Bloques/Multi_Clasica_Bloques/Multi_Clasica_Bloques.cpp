#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

const int SIZE = 512;  // Ajusta según el análisis
const int BLOCK_SIZE = 64;  // Ajusta según el análisis

void matrixClasica(const vector<vector<double>>& A,
    const vector<vector<double>>& B,
    vector<vector<double>>& C, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrixBloques(const vector<vector<double>>& A,
    const vector<vector<double>>& B,
    vector<vector<double>>& C, int size, int blockSize) {
    for (int ii = 0; ii < size; ii += blockSize) {
        for (int jj = 0; jj < size; jj += blockSize) {
            for (int kk = 0; kk < size; kk += blockSize) {
                for (int i = ii; i < min(ii + blockSize, size); ++i) {
                    for (int j = jj; j < min(jj + blockSize, size); ++j) {
                        double sum = 0;
                        for (int k = kk; k < min(kk + blockSize, size); ++k) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }
}

int main() {
    vector<vector<double>> A(SIZE, vector<double>(SIZE, 1.0));
    vector<vector<double>> B(SIZE, vector<double>(SIZE, 1.0));
    vector<vector<double>> C(SIZE, vector<double>(SIZE, 0.0));

    // Medición para matriz clásica
    auto start1 = chrono::high_resolution_clock::now();
    matrixClasica(A, B, C, SIZE);
    auto end1 = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion Clasica: "
        << chrono::duration<double, milli>(end1 - start1).count() << " ms" << endl;

    // Reiniciar C
    fill(C.begin(), C.end(), vector<double>(SIZE, 0.0));

    // Medición para matriz por bloques
    auto start2 = chrono::high_resolution_clock::now();
    matrixBloques(A, B, C, SIZE, BLOCK_SIZE);
    auto end2 = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion Bloques: "
        << chrono::duration<double, milli>(end2 - start2).count() << " ms" << endl;

    return 0;
}
