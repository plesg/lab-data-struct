#include <iostream>
#include <cblas.h>
#include <chrono>
#include <random>

const int N = 4096;

// Функция для инициализации матрицы случайными значениями
void initializeMatrix(double* matrix) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i * N + j] = dis(gen);
        }
    }
}

int main() {
    // Выделение памяти для матриц
    double* A = new double[N * N];
    double* B = new double[N * N];
    double* C = new double[N * N];

    // Инициализация матриц
    initializeMatrix(A);
    initializeMatrix(B);

    // Умножение матриц с помощью cblas_dgemm
    auto start = std::chrono::high_resolution_clock::now();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, A, N, B, N, 0.0, C, N);
    auto end = std::chrono::high_resolution_clock::now();

    // Расчет времени выполнения
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    // Оценка сложности и производительности
    double complexity = 2.0 * N * N * N;
    double performance = complexity / duration * 1e-6; // MFlops

    // Вывод результатов
    std::cout << "Сложность: " << complexity << std::endl;
    std::cout << "Время: " << duration << " секунд" << std::endl;
    std::cout << "Производительность: " << performance << " MFlops" << std::endl;

    // Освобождение памяти
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
