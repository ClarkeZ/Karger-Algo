/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#ifndef LISTE_CHAINE_H_
#define LISTE_CHAINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef struct Element Element;
struct Element 
{
    int nom;
    struct Element *next;
};

typedef struct List 
{
    Element *first;
    Element *last;
    int nb; // nombre d'elements dans la liste
} List;

/* ********** Fonctions List ********** */

List *init_list();

void list_print(List *list);

void list_insert(List *list, int val);

void list_delete(List *list, int val);

void list_concat(List *list1, List *list2);

int list_seek_elem(List *list, int val);

void free_list(List *list);

#endif /* LISTE_CHAINE_H_ */