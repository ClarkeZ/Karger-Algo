/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#include "matrice_adjacence.h"

Matrix *init_matrix(uint n){
    Matrix *mat = malloc(sizeof(Matrix));

    if(mat == NULL){
        perror("init_matrix : Erreur allocation mémoire struct Matrix !\n");
        exit(EXIT_FAILURE);
    }

    mat->n = n;
    mat->nb = n;
    mat->nb_aretes = 0;
    mat->m = calloc(n*n, sizeof(int));

    if(mat->m == NULL){
        perror("init_matrix : Erreur allocation mémoire Matrix !\n");
        exit(EXIT_FAILURE);
    }
    return mat;
}

/*
Copie une matrice dans une nouvelle matrice
@param mat : la matrice a copier

@return une copie de la matrice mat
*/
Matrix *copy_matrix(Matrix *mat){
    Matrix *copy = init_matrix(mat->n);
    copy->nb_aretes = mat->nb_aretes;
    copy->nb = mat->nb;
    memcpy(copy->m, mat->m, sizeof(int) * mat->n * mat->n);

    return copy;
}

/*
Affiche une matrice
@param M : la matrice a afficher
*/
void print_matrix(Matrix *mat){
    uint i, j;
    for (i = 0; i < mat->n; ++i) {
        for (j = 0; j < mat->n; ++j) {
            printf("%d ", mat->m[i * mat->n + j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
Libere la memoire allouee a une structure Matrix
@param mat : la matrice a liberer
*/

void free_matrix(Matrix *mat){
    free(mat->m);
    free(mat);
}