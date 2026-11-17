#include <stdio.h>
#include <stdlib.h>
#include "cholesky.h"
#include "crout.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Expected call: %s <input_matrix_file> <output_directory>", argv[0]);
        return 1;
    }

    matrix_t *input_matrix = read_matrix(argv[1]);
    if (input_matrix == NULL) {
        fprintf(stderr, "Could not read matrix from %s!\n", argv[1]);
        return 1;
    }

    matrix_t *L = allocate_matrix(input_matrix->size);
    if (L == NULL) {
        fprintf(stderr, "Could not allocate matrix L!\n");
        return 1;
    }

    if (!cholesky(input_matrix, L)) {
        fprintf(stderr, "Cholesky decomposition failed!\n");
        return 1;
    }

    if (!write_matrix(L, argv[2], CHOLESKY_L_FILE)) {
        fprintf(stderr, "Could not write Cholesky L matrix to %s!\n", argv[2]);
        return 1;
    }

    matrix_t *crout_L = allocate_matrix(input_matrix->size);
    if (crout_L == NULL) {
        fprintf(stderr, "Could not allocate matrix crout_L!\n");
        return 1;
    }

    matrix_t *crout_U = allocate_matrix(input_matrix->size);
    if (crout_U == NULL) {
        fprintf(stderr, "Could not allocate matrix crout_U!\n");
        return 1;
    }

    if (!crout(input_matrix, crout_L, crout_U)) {
        fprintf(stderr, "Crout decomposition failed!\n");
        return 1;
    }

    if (!write_matrix(crout_L, argv[2], CROUT_L_FILE)) {
        fprintf(stderr, "Could not write Crout L matrix to %s!\n", argv[2]);
        return 1;
    }

    if (!write_matrix(crout_U, argv[2], CROUT_U_FILE)) {
        fprintf(stderr, "Could not write Crout U matrix to %s!\n", argv[2]);
        return 1;
    }

    return 0;
}
