#include <iostream>
#include <random>
#include <chrono>

const int N = 4096;

void generateMatrix(double* matrix) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i * N + j] = dis(gen);
        }
    }
}

void multiplyMatrices(double* A, double* B, double* C) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i * N + j] = 0.0;
            for (int k = 0; k < N; ++k) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
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
    multiplyMatrices(A, B, C);
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
