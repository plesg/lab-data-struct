#include <iostream>
#include <random>
#include <chrono>

const int N = 4096;
const int BLOCK_SIZE = 64; // Размер блока для оптимизации

void generateMatrix(double* matrix) {
    // Аналогично предыдущим примерам
}

void multiplyMatricesBlock(double* A, double* B, double* C) {
    for (int i = 0; i < N; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            for (int k = 0; k < N; k += BLOCK_SIZE) {
                for (int x = i; x < std::min(i + BLOCK_SIZE, N); ++x) {
                    for (int y = j; y < std::min(j + BLOCK_SIZE, N); ++y) {
                        for (int z = k; z < std::min(k + BLOCK_SIZE, N); ++z) {
                            C[x * N + y] += A[x * N + z] * B[z * N + y];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    double* A = new double[N * N];
    double* B = new double[N * N];
    double* C = new double[N * N];

    generateMatrix(A);
    generateMatrix(B);

    auto start = std::chrono::high_resolution_clock::now();
    multiplyMatricesBlock(A, B, C);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    // Оценка сложности
    double complexity = 2.0 * N * N * N;

    // Оценка производительности
    double performance = complexity / duration * 1e-6; // MFlops

    std::cout << "Сложность: " << complexity << std::endl;
    std::cout << "Время: " << duration << " секунд" << std::endl;
    std::cout << "Производительность: " << performance << " MFlops" << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
