#include <iostream>

enum Command { RandomlyFillMatrix = 0, ManuallyFillMatrix = 1 };

// Using **& in the functions will make it more memory efficient

void FreeMemory(int **&matrix, int N) {
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
}

int GetMatrixElement(int **&matrix, int i, int j, int N) {
    // The sum is bigger than N for elements in the second triangle
    if (i + j >= N) {
        return matrix[N - 1 - j][N - 1 - i];
    } else
        return matrix[i][j];
}

void AllocateMemory(int **&target, int N) {
    target = new int *[N];
    for (int i = 0; i < N; i++) {
        target[i] = new int[N - i];
    }
}

int RandInt(int min, int max) {
    static bool first = true;
    if (first) {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

void FillMatrixFromRandom(int **&matrix, int N) {
    int minRand, maxRand;
    std::cout << "Enter min element for rand range" << std::endl;
    std::cin >> minRand;
    std::cout << "Enter max element for rand range" << std::endl;
    std::cin >> maxRand;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N - i; ++j) {
            matrix[i][j] = RandInt(minRand, maxRand);
        }
    }
}

void SolveTask1(int **&matrix, int N) {
    bool isNegative = false;
    long int product = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (GetMatrixElement(matrix, i, j, N) < 0) {
                isNegative = true;
                break;
            }
        }
        if (!isNegative) {
            for (int j = 0; j < N; ++j) {
                product *= GetMatrixElement(matrix, i, j, N);
            }
            std::cout << "Product of the " << i + 1 << "th row is equal ";
            std::cout << product << std::endl;
            product = 1;
        }
        isNegative = false;
    }
}

void SolveTask2(int **&matrix, int N) {
    int sum = 0;
    int min = 0;
    for (int i = 1; i < N; ++i) {
        sum = 0;
        for (int j = 0; j < N - i; ++j) {
            sum += GetMatrixElement(matrix, i + j, j, N);
        }
        if (i == 1 || min > sum) {
            min = sum;
        }
    }

    for (int j = 1; j < N; ++j) {
        sum = 0;
        for (int i = 0; i < N - j; ++i) {
            sum += GetMatrixElement(matrix, i, i + j, N);
        }
        if (min > sum) {
            min = sum;
        }
    }
    std::cout << "Minimal sum of all the diagonals is " << min << std::endl;
}

void FillMatrixFromKeyboard(int **&matrix, int N) {
    for (int i = 0; i < N; ++i) {
        std::cout << "Enter " << N - i << " elements for ";
        std::cout << i + 1 << "th row" << std::endl;
        for (int j = 0; j < N - i; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

void PrintMatrix(int **&matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << GetMatrixElement(matrix, i, j, N) << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    int n, commandInt;
    int **matrix;

    do {
        std::cout << "Enter amount of rows and columns of a matrix";
        std::cout << std::endl;
        std::cin >> n;
    } while (n < 1 || n > 10);

    std::cout
        << "Enter 0 to fill matrix randomly. Enter 1 to fill matrix manually"
        << std::endl;
    std::cin >> commandInt;

    AllocateMemory(matrix, n);

    switch ((Command)commandInt) {

    case RandomlyFillMatrix:
        FillMatrixFromRandom(matrix, n);
        break;

    case ManuallyFillMatrix:
        FillMatrixFromKeyboard(matrix, n);
        break;
    }

    PrintMatrix(matrix, n);
    SolveTask1(matrix, n);
    SolveTask2(matrix, n);
    FreeMemory(matrix, n);
    return 0;
}
