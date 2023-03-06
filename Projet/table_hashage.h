/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#include "liste_chaine.h"

typedef unsigned int uint;
typedef struct Hashage {
    List **tab; // tableau de listes
    int n; // nombre de noeuds dans le graphe
    uint nb;//nombre de sommets actuel
    uint nb_aretes; // nombre d'aretes dans le graphe si on utilise une liste d'adjacence
} Hashage;

Hashage *init_hashage(int n);

void hash_insert(Hashage *hash, uint i, int val);

void hash_delete(Hashage *hash, uint i, int val);

void print_hashage(Hashage *hash);

Hashage *copy_hashage(Hashage *h);

void free_hashage(Hashage *hash);