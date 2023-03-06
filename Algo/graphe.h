/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#ifndef GRAPHE_H_
#define GRAPHE_H_

#include "table_hashage.h"
#include "matrice_adjacence.h"

typedef struct arete {
    uint u;
    uint v;
} Arete;

/* ********** Fonctions Graphes Elementaires Matrice ********** */
Matrix *cycle(int n);

Matrix *complet(int n);

Matrix *biparti(int n);

Matrix *alea(int n);

Matrix *etoile(int n);

/* ********** Fonctions Graphes Elementaires Liste ********** */
Hashage *cycle_liste(int n);

Hashage *complet_liste(int n);

Hashage *biparti_liste(int n);

Hashage *alea_liste(int n);

Hashage *etoile_liste(int n);

#endif // GRAPHE_H