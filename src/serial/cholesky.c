#include <math.h>
#include "cholesky.h"

int cholesky(matrix_t *A, matrix_t *L) {
     if (A == NULL || L == NULL || A->size != L->size) {
        return 0;
    }

    int n = A->size;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L->elements[i][j] = 0.0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0.0;

            for (int k = 0; k < j; k++) {
                sum += L->elements[i][k] * L->elements[j][k];
            }

            if (i == j) {
                double value = A->elements[i][i] - sum;
                if (value <= 0.0) {
                    return 0;
                }

                L->elements[i][j] = sqrt(value);
            } else {
                L->elements[i][j] = (A->elements[i][j] - sum) / L->elements[j][j];
            }
        }
    }

    return 1;
}
