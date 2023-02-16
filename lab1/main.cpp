#include <iostream>
#include <cstdlib>
#include <omp.h>


void fillMatrix(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}


int main(int argc, char **argv) {
    int n1 = 1000;
    int m1 = 500;
    int n2 = 500;
    int m2 = 1200;

    int **matrix1;
    int **matrix2;

    matrix1 = new int *[n1];
    for (int i = 0; i < n1; i++) {
        matrix1[i] = new int[m1];
    }
    matrix2 = new int *[n2];
    for (int i = 0; i < n2; i++) {
        matrix2[i] = new int[m2];
    }

    fillMatrix(matrix1, n1, m1);
    fillMatrix(matrix2, n2, m2);

    int **result = new int *[n1];
    for (int i = 0; i < n1; i++) {
        result[i] = new int[m2];
    }


    int i, j, k;
    double start = omp_get_wtime();
#pragma omp parallel for shared(matrix1, matrix2, result, n1, m2, m1) private(i, j, k) default(none)
    for (i = 0; i < n1; i++) {
        for (j = 0; j < m2; j++) {
            result[i][j] = 0;
            for (k = 0; k < m1; k++) {
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }
    double end = omp_get_wtime();
    std::cout << end - start;
    return 0;
}