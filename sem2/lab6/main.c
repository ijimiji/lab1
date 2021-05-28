#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int IsMagicSquare(short** square, int N);
// {
//     return square[0][0];
// }
// {
//     return square;
// }
int **DealocateMatrix (int n, short** m) {
    int i;
    for (i = 0; i < n; i++) {
        free (m[i]);
    }
    free (m);
    return(NULL);
}

short **AlocateMatrix (int n) {
    short **m = NULL, i, j;

    if ( ( m = malloc (n * sizeof(int *))) != NULL) {

        for (i = 0; i < n; i++) {
            if ( ( m[i] = malloc (n * sizeof(int ))) == NULL) {
                while ( i) {
                    i--;
                    free ( m[i]);
                }
                free ( m);
                return NULL;
            }
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                m[i][j] = 0;
            }
        }
    }

    return m;
}

int isMagicSquare(short** square, int N) {
    // calculate the sum of
    // the prime diagonal
    int sum = 0, sum2 = 0;

    for (int i = 0; i < N; i++)
        sum = sum + square[i][i];
    // the secondary diagonal
    for (int i = 0; i < N; i++)
        sum2 = sum2 + square[i][N - 1 - i];

    if (sum != sum2)
        return false;

    // For sums of Rows
    for (int i = 0; i < N; i++) {

        int rowSum = 0;
        for (int j = 0; j < N; j++)
            rowSum += square[i][j];

        // check if every row sum is
        // equal to prime diagonal sum
        if (rowSum != sum)
            return false;
    }

    // For sums of Columns
    for (int i = 0; i < N; i++) {

        int colSum = 0;
        for (int j = 0; j < N; j++)
            colSum += square[j][i];

        // check if every column sum is
        // equal to prime diagonal sum
        if (sum != colSum)
            return false;
    }

    return true;
}

int main() {
    int n;
    printf("%s", "Enter n: ");
    scanf("%d", &n);

    short **mat = AlocateMatrix(n);
    short t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%hd", &t);
            mat[i][j] = t;
        }
    }
    // printf("%hd %hd %hd %hd\n", mat[0][0], mat[0][1], mat[1][0], mat[1][1]);
    // printf("%d\n", isMagicSquare(mat, n));
    printf("%d\n", IsMagicSquare(mat, n));
    free(mat);
    return 0;
}
