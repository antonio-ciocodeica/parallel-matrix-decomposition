#include "crout.h"

int crout(matrix_t *A, matrix_t *L, matrix_t *U) {
    if (A == NULL || L == NULL || U == NULL || A->size != L->size || A->size != U->size) {
        return 0;
    }

    int n = A->size;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L->elements[i][j] = 0.0;
            U->elements[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = j; i < n; i++) {
            double sum = 0.0;
            for (int k = 0; k < j; k++) {
                sum += L->elements[i][k] * U->elements[k][j];
            }
            L->elements[i][j] = A->elements[i][j] - sum;
        }

        if (L->elements[j][j] == 0.0) {
            return 0;
        }

        for (int i = j + 1; i < n; i++) {
            double sum = 0.0;
            for (int k = 0; k < j; k++) {
                sum += L->elements[j][k] * U->elements[k][i];
            }
            U->elements[j][i] = (A->elements[j][i] - sum) / L->elements[j][j];
        }
    }

    return 1;
}
