/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#include "liste_chaine.h"
/* ********** Fonctions List ********** */

List *init_list(){
    List *list = malloc(sizeof(List));
    if(list == NULL){
        perror("init_list : Erreur allocation mémoire struct List !\n");
        exit(EXIT_FAILURE);
    }

    list->first = NULL;
    list->last = NULL;
    list->nb = 0;
    return list;
}

void list_print(List *list){
    if(list != NULL || list->nb != 0)
    {
        Element *tmp = list->first;
        for(int i = 0; i < list->nb; i++)
        {
            printf("%d ", tmp->nom);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

void list_insert(List *list, int val){
    Element *elem = malloc(sizeof(Element));

    if(elem == NULL){
        perror("list_insert : Erreur allocation mémoire struct Element !\n");
        exit(EXIT_FAILURE);
    }

    if (list->nb == 0)
    {
        elem->nom = val;
        elem->next = NULL;
        list->first = elem;
        list->last = elem;
        list->last->next = NULL;
    }
    else
    {
        elem->nom = val;
        elem->next = list->first;
        list->first = elem;     
    }
    list->nb++;
}

void delete(List *list, int val){
    if(list != NULL || list->nb != 0)
    {
        Element *tmp = list->first;
        Element *tmp2 = NULL;
        for(int i = 0; i < list->nb; i++)
        {
            if(tmp->nom == val)
            {
                if(tmp == list->first)
                {
                    list->first = tmp->next;
                    free(tmp);
                    list->nb--;
                    break;
                }
                else if(tmp == list->last)
                {
                    list->last = tmp2;
                    list->last->next = NULL;
                    free(tmp);
                    list->nb--;
                    break;
                }
                else
                {
                    tmp2->next = tmp->next;
                    free(tmp);
                    list->nb--;
                    break;
                }
            }
            tmp2 = tmp;
            tmp = tmp->next;
        }
    }
}

void list_delete(List *list, int val){
    while (list_seek_elem(list, val) >0)
    {
        delete(list, val);
    }
}
// void list_delete(List *list, int val){
//     if (list != NULL && list->nb > 0){
//         Element *actuel = list->first;
//         Element *precedent = NULL;

//         int nb = list->nb;

        // while (actuel != NULL && nb > 0){
        //     if (actuel->nom == val){
        //         if (precedent == NULL){
        //             list->first = actuel->next;
        //         }
        //         else{
        //             precedent->next = actuel->next;
        //         }
        //         free(actuel);
        //         list->nb--;
        //     }
        //     precedent = actuel;
        //     if (actuel->next != NULL){
        //         actuel = actuel->next;
        //     }
        //     else{
        //         actuel = NULL;
        //     }
            
        // }
//     }
// }

// void list_delete(List *list, int val)
// {
//     if (list != NULL && list->nb > 0)
//     {
//         Element * actuel, *precedent=NULL;
//         int nb=list->nb;

//         actuel = list->first;
//         for(int i=0; i<nb;i++)
//         {
//             if(actuel->nom == val)
//             {
//                 //debut de la liste
//                 if(actuel == list->first)
//                 {
//                     list->first = actuel->next;
//                     free(actuel);
//                     list->nb--;
//                     if(list->nb == 0)
//                         list->last = NULL;
//                     precedent = actuel;
//                     if(actuel->next != NULL)
//                         actuel = actuel->next;
//                 }
//                 //milieu de la liste
//                 else if(actuel != list->last)
//                 {
//                     precedent->next = actuel->next;
//                     free(actuel);
//                     list->nb--;
//                     actuel = precedent->next;
//                 }
//                 //fin de la liste
//                 else
//                 {
//                     precedent->next = NULL;
//                     list->last = precedent;
//                     free(actuel);
//                     list->nb--;
                    
//                     return;
//                 }
//             }
//             else
//             {
//                 precedent = actuel;
//                 if (actuel->next != NULL)
//                     actuel = actuel->next;
//             }
           
//         }
    
//     }
  
// }

void list_concat(List *list1, List *list2)
{
    if(list1 == NULL || list2 == NULL)
    {
        perror("list_concat : Erreur, une des listes est vide !\n");
        exit(EXIT_FAILURE);
    }

    if(list1->nb == 0)
    {
        list1->first = list2->first;
        list1->last = list2->last;
        list1->nb = list2->nb;
       
    }
    else 
    {
        list1->last->next = list2->first;
        list1->last = list2->last;
        list1->nb += list2->nb;
    }
    list2->nb = 0;
   
}

int list_seek_elem(List *list, int val){
    Element *elem = list->first;
    int r=0;
    for(int i=0;i<list->nb;i++)
    {
        if(elem->nom == val)
        {
            r++;
        }
        elem = elem->next;
    }
    return r;
}

void free_list(List *list)
{
    if (list != NULL && list->nb >0 )
    {
        Element *elem = list->first;
        Element *tmp;

        for(int i=0; i<list->nb; i++)
        {
            tmp = elem;
            elem = elem->next;
            free(tmp);
        }
        free(list);
    }
    else{
        if (list->first != NULL && list->nb >0)
            free(list->first);
        if (list->last != NULL && list->nb >0)
            free(list->last);
        if (list != NULL )
            free(list);
    }
}