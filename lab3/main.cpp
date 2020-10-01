#include <iostream>

void FreeMemory(int**& matrix, int N) {
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
}

void CopyMatrix(int** source, int**& destination, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

void AllocateMemory(int**& target, int N) {
    target = new int* [N];
    for (int i = 0; i < N; i++) {
        target[i] = new int[N];
    }
}

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
    int** matrixCopy;
    AllocateMemory(matrixCopy, N);
    CopyMatrix(matrix, matrixCopy, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = matrixCopy[N - j - 1][N - i - 1];
        }
    }
    FreeMemory(matrixCopy, N);
}

void SolveTask1(int** matrix, int N) {
    bool isNegative = false;
    long int product = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] < 0) {
                isNegative = true;
                break;
            }
        }
        if (!isNegative) {
            for (int j = 0; j < N; ++j) {
                product *= matrix[i][j];
            }
            std::cout << "Product of the " << i+1 << "th row is equal ";
            std::cout << product << std::endl;
            product = 1;
        }
        isNegative = false;
    }
}


void SolveTask2(int**& matrix, int N) {

}

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
    int** matrix;

    do {
        std::cout << "Enter amount of rows and columns of a matrix" << std::endl;
        std::cin >> n;
    } while (n < 1 || n > 10);

    AllocateMemory(matrix, n);
    FillMatrix(matrix, n);
    TransposeMatrix(matrix, n);
    PrintMatrix(matrix, n);
    SolveTask1(matrix, n);
    // SolveTask2(matrix, n);
    FreeMemory(matrix, n);
    return 0;
}