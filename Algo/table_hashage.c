/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#include "table_hashage.h"

Hashage *init_hashage(int n){
    Hashage *hash = malloc(sizeof(Hashage));

    if(hash == NULL){
        perror("init_hashage : Erreur allocation mémoire struct Hashage !\n");
        exit(EXIT_FAILURE);
    }

    hash->n = n;
    hash->nb_aretes = 0;
    hash->nb = n;
    hash->tab = malloc(sizeof(List *) * n);

    if(hash->tab == NULL){
        perror("init_hashage : Erreur allocation mémoire Hashage !\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0 ; i < n ; i++){
        hash->tab[i] = init_list();
    }

    return hash;
}

void hash_insert(Hashage *hash, uint i, int val)
{
    list_insert(hash->tab[i], val);  
}

void hash_delete(Hashage *hash, uint i, int val)
{
    list_delete(hash->tab[i], val);
}

void print_hashage(Hashage *hash)
{
    for(int i = 0 ; i < hash->n ; i++){
        printf("%d : ", i);
        list_print(hash->tab[i]);
    }
}

Hashage *copy_hashage(Hashage *h)
{
    Hashage *h2 = init_hashage(h->n);
    Element *elem;
    
    for(int i = 0 ; i < h->n ; i++)
    {
        elem = h->tab[i]->first;
        for (int j = 0 ; j < h->tab[i]->nb ; j++) 
        {
            hash_insert(h2, i, elem->nom);
            elem = elem->next;
        }
    }
    h2->nb_aretes = h->nb_aretes;
    h2->nb = h->nb;

    return h2;
}

void free_hashage(Hashage *hash){
    // Cause des fuites memoires
    for(int i = 0 ; i < hash->n ; i++){
        if (hash->tab[i] != NULL)
            free_list(hash->tab[i]);
    }
    free(hash->tab);
    free(hash);
}
