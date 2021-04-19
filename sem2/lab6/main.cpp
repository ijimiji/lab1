#include <iostream>

template <typename A>
A** MatrixMaloc(int n, int m) {
    A** target = new A *[n];
    for (int i = 0; i < n; i++) {
        target[i] = new A[m];
    }
    return target;
}

template <typename A>
void FreeMemory(A **&target, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] target[i];
    }
    // delete[] target;
}

template <typename A>
void PrintMatrix(A**matrix, int N, int M) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

// 1. Написать 64-битное приложение, содержащее функцию с сигнатурой
// bool  IsMagicSquare(short** square, int N), 
// которая принимает двумерный массив размера NxN, 
// считает суммы в строках, столбцах и главных диагоналях и 
// возвращает истину только тогда, когда все суммы равны.

extern "C" bool IsMagicSquare(short** square, int N);

int main(){
    int N = 2;
    int M = 2;
    short** mat = MatrixMaloc<short>(N, M);
    mat[0][0] = 0;
    mat[0][1] = 1;
    mat[1][0] = 1;
    mat[1][1] = 1;
    PrintMatrix<short>(mat, N, M);
    std::cout << IsMagicSquare(mat, N) << std::endl;
    FreeMemory<short>(mat, N);
    return 0;
}