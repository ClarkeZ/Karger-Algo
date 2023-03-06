/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#include "graphe.h"

#include <math.h>

/* ********** Matrice d'adjacence ********** */
void contraction_matrice(Arete a, Matrix *mat, Hashage *h);

Arete tirage_arete(Matrix * m);

int karger(Matrix *m, Hashage *h);

int karger_itere(Matrix *m, Hashage *h, int nb_iter);

void contraction_partielle_matrice(int t, Matrix *mat, Hashage *h);

int karger_stein_matrice(Matrix *m, Hashage *h);

/* ********** Liste d'adjacence ********** */
void contraction_liste(Arete a, Hashage *g, Hashage *h);

Arete tirage_arete_liste(Hashage *h);

int karger_liste(Hashage *h,Hashage *h2);

int karger_liste_itere(Hashage *h, int nb_iter, Hashage *h2);

void contraction_partielle_liste(Hashage *h, Hashage *h2, uint t);

int karger_stein_liste(Hashage *h, Hashage *h2);

/* ********** solution de Kager ********** */
void groupe(Hashage *h);

/* ********** Fonction calcul du temps ********** */
double wtime();

