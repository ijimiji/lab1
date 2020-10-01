#include <iostream>

int random(int min, int max) {
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

void FillMatrix(int**& matrix, int N) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = random(-100, 100);
        }
}

void TransposeMatrix(int**& matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = matrix[N - j - 1][N - i - 1];
        }
    }
}
void SolveTask1(int**& matrix, int N) {}
void SolveTask2(int**& matrix, int N) {}
void PrintMatrix(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
int main() {
    int n;

    do {
        std::cout << "Enter amount of rows and columns of a matrix" << std::endl;
        std::cin >> n;
    } while (n < 1 || n > 10);

    int i = n, j = n;

    int** matrix = new int* [i];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[j];
    }

    FillMatrix(matrix, n);
    TransposeMatrix(matrix, n);
    PrintMatrix(matrix, n);
    return 0;
}