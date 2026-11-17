#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>

#define CHOLESKY_L_FILE "cholesky-L"
#define CROUT_L_FILE "crout-L"
#define CROUT_U_FILE "crout-U"

typedef struct {
    int size;
    double **elements;
} matrix_t;

int write_matrix(matrix_t *matrix, char *directory, char *filename);
matrix_t *allocate_matrix(int size);
matrix_t *read_matrix(char *path);
void free_matrix(matrix_t *matrix);

#endif
