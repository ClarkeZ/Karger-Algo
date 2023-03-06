/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#include "graphe.h"

/* ********** Fonctions Graphes Elementaires Matrice ********** */
Matrix *cycle(int n){
    Matrix *mat = init_matrix(n);

    for(int i = 0 ; i < n ; i++){
        mat->m[i*n + (i+1)%n] = 1;
        mat->m[(i+1)%n*n + i] = 1;
        mat->nb_aretes++;
    }
    return mat;
}

Matrix *complet(int n){
    Matrix *mat = init_matrix(n);

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(i != j){
                mat->m[i*n + j] = 1;
                mat->nb_aretes++;
            }
        }
    }
    mat->nb_aretes /= 2;
    return mat;
}

Matrix *biparti(int n){
    if(n%2 != 0){
        perror("Erreur : n doit etre pair pour un graphe biparti\n");
        exit(EXIT_FAILURE);
    }
    Matrix *mat = init_matrix(n);

    for(int i = 0 ; i < n ; i++){
        for(int j = i ; j < n ; j++){
            if(i != j){
                if(i%2 == 0 && j%2 == 1){
                    mat->m[i*n + j] = 1;
                    mat->m[j*n + i] = 1;
                    mat->nb_aretes++;
                }
                else if(i%2 == 1 && j%2 == 0){
                    mat->m[i*n + j] = 1;
                    mat->m[j*n + i] = 1;
                    mat->nb_aretes++;
                }
            }
        }
    }
    return mat;
}


Matrix *alea(int n){
    double r = 0;

    Matrix *mat = init_matrix(n);

    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(i != j){
                r = rand() % (MAX - MIN);
                if(r > PROBA){
                    mat->m[i*n + j] = 1;
                    mat->m[j*n + i] = 1;
                    mat->nb_aretes++;
                }
            }
        }
    }
    return mat;
}

Matrix *etoile(int n)
{
    Matrix *mat = init_matrix(n);

    for(int i = 1 ; i < n ; i++){
        mat->m[i*n] = 1;
        mat->m[0*n + i] = 1;
        mat->nb_aretes++;
    }
    return mat;
}
/* ********** Fonctions Graphes Elementaires Liste ********** */


Hashage *cycle_liste(int n)
{
    Hashage *g = init_hashage(n);
    for(int i = 0 ; i < n ; i++)
    {
        hash_insert(g, i, (i+1)%n);
        hash_insert(g, (i+1)%n, i);
        g->nb_aretes++;
    }
    return g;
} 

Hashage *complet_liste(int n)
{
    Hashage *g = init_hashage(n);
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = i+1 ; j < n ; j++)
        {
            if(i != j)
            {
                hash_insert(g, i, j);
                hash_insert(g, j, i);
                g->nb_aretes++;
            }
        }
    }
    return g;
}

Hashage *biparti_liste(int n)
{
    if(n % 2 != 0)
    {
        perror("Erreur : n doit etre pair pour un graphe biparti\n");
        exit(EXIT_FAILURE);
    }
    
    Hashage *g = init_hashage(n);
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = i+1 ; j < n ; j++)
        {
            if(i%2 == 0 && j%2 == 1)
            {
                hash_insert(g, i, j);
                hash_insert(g, j, i);
                g->nb_aretes++;
            }
            else if(i%2 == 1 && j%2 == 0)
            {
                hash_insert(g, i, j);
                hash_insert(g, j, i);
                g->nb_aretes++;
            }
        }
    }
    return g;
}

Hashage *alea_liste (int n)
{
    double r = 0;
    Hashage *g = init_hashage(n);
    
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(i != j){
                r = rand() % (MAX - MIN);
                if(r > PROBA){
                    hash_insert(g, i, j);
                    hash_insert(g, j, i);
                    g->nb_aretes++;
                }
            }
        }
    }
    return g;
}

Hashage *etoile_liste(int n)
{
    Hashage *g = init_hashage(n);
    for(int i = 1 ; i < n ; i++)
    {
        hash_insert(g, i, 0);
        hash_insert(g, 0, i);
        g->nb_aretes++;
    }
    return g;
}