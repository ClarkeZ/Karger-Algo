/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define MAX 8
#define MIN 0
#define PROBA 0.7

typedef unsigned int uint;

typedef struct Matrix {
    int *m;//matrice d'ajaicence
    uint n; //nombre de sommets au debut
    uint nb;//nombre de sommets actuel
    uint nb_aretes;
} Matrix;

/* ********** Fonctions matrices ********** */
Matrix *init_matrix(uint n);

Matrix *copy_matrix(Matrix *mat);

void print_matrix(Matrix *mat);

void free_matrix(Matrix *mat);