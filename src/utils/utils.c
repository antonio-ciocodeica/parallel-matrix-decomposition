#include <stdlib.h>
#include <string.h>
#include "utils.h"

int write_matrix(matrix_t *matrix, char *directory, char *filename) {
    if (matrix == NULL || directory == NULL || filename == NULL) {
        return 0;
    }

    char *path = malloc(strlen(directory) + strlen(filename) + 2);
    if (path == NULL) {
        return 0;
    }

    sprintf(path, "%s/%s", directory, filename);
    
    FILE *output_file = fopen(path, "w");
    if (output_file == NULL) {
        free(path);
        return 0;
    }

    fprintf(output_file, "%d\n", matrix->size);
    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            fprintf(output_file, "%lf ", matrix->elements[i][j]);
        }

        fprintf(output_file, "\n");
    }

    fclose(output_file);
    free(path);
    return 1;
}

matrix_t *allocate_matrix(int size) {
    if (size < 1) {
        return NULL;
    }

    matrix_t *matrix = calloc(1, sizeof(matrix_t));
    if (matrix == NULL) {
        return NULL;
    }

    matrix->size = size;
    matrix->elements = calloc(matrix->size, sizeof(double *));
    if (matrix->elements == NULL) {
        free_matrix(matrix);
        return NULL;
    }

    for (int i = 0; i < matrix->size; i++) {
        matrix->elements[i] = calloc(matrix->size, sizeof(double));
        if (matrix->elements[i] == NULL) {
            free_matrix(matrix);
            return NULL;
        }
    }

    return matrix;
}

matrix_t *read_matrix(char *path) {
    FILE *input_file = fopen(path, "r");
    if (input_file == NULL) {
        return NULL;
    }
    
    int size;
    int ret = fscanf(input_file, "%d", &size);
    if (ret != 1) {
        fclose(input_file);
        return NULL;
    }

    matrix_t *matrix = allocate_matrix(size);
    if (matrix == NULL) {
        fclose(input_file);
        return NULL;
    }

    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            ret = fscanf(input_file, "%lf", &matrix->elements[i][j]);
            if (ret != 1) {
                free_matrix(matrix);
                fclose(input_file);
                return NULL;
            }
        }
    }

    fclose(input_file);
    return matrix;
}

void free_matrix(matrix_t *matrix) {
    if (matrix == NULL) {
        return;
    }

    if (matrix->elements == NULL) {
        free(matrix);
        return;
    }

    for (int i = 0; i < matrix->size; i++) {
        free(matrix->elements[i]);
    }

    free(matrix->elements);
    free(matrix);
}