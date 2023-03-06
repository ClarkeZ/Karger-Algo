/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#include "karger.h"

/* ********** Matrice d'adjacence ********** */
/*
Fusionne deux colonnes d'une matrice, ajout de la colonne j dans la colonne i
@param i : indice de la colonne a fusionner   
@param j : indice de la colonne a fusionner dans i
@param mat : la matrice a modifier
*/
void contraction_matrice(Arete a, Matrix *mat, Hashage *h){
    mat->nb_aretes -= mat->m[a.u*mat->n + a.v];
    for(uint k = 0 ; k < mat->n ; k++){
        mat->m[k*mat->n + a.u] += mat->m[k*mat->n + a.v];
        // mat->m[a.u*mat->n + k] += mat->m[a.v*mat->n + k];
        mat->m[a.u*mat->n + k]=mat->m[k*mat->n + a.u];
        mat->m[k*mat->n + a.v] = -1;
        mat->m[a.v*mat->n + k] = -1;
    }
    // Pour la diagonale 
    mat->m[a.u*mat->n + a.u] = 0;
    mat->m[a.v*mat->n + a.v] = 0;


    // On fusionne les listes
    Element *tmp = h->tab[a.v]->first; 
    for(int k = 0 ; k < h->tab[a.v]->nb ; k++) // On se deplace jusqu'a la fin de la liste
    {
        list_insert(h->tab[a.u], tmp->nom);
        tmp = tmp->next;
    }
    h->tab[a.v]->nb = 0; // On met a jour le nombre d'elements dans la liste v

}

/*
* Tirage d'une arete aleatoire dans la matrice
* @param m : la matrice
* @return une arete aleatoire
*/
Arete tirage_arete(Matrix * m)
{
    Arete a;
    double r = rand() % (m->n * m->n -1);
    a.u=r/m->n;
    a.v=(uint)r%m->n;

    return a;
}

int nb_listes_vides(Hashage *h){
    int cpt = 0;
    for(int i = 0 ; i < h->n ; i++){
        if(h->tab[i]->nb > 0)
            cpt++;
    }
    return cpt;
}
/*
* Algorithmes de Karger
* @param m : la matrice
* @param h : le hashage
* @return la coupe minimale
*/
int karger(Matrix *m, Hashage *h)
{
    Arete a;

    while (m->nb>2){ // Tant que le nombre de groupe >2
        do
        {
            a = tirage_arete(m); 
        } while (m->m[a.u*m->n + a.v] <1);

        contraction_matrice( a, m, h);
        h->tab[a.v]->nb =0;

        m->nb--;

    }
    return m->nb_aretes;
}

void reset (Hashage *h)
{
    for (int i=0; i<h->n; i++)
    {
        for(int j = 0 ; j < h->tab[i]->nb ; j++)
        {
            // list_delete(h->tab[i], h->tab[i]->first->nom);
            free_list(h->tab[i]);
            h->tab[i]=init_list();
        }
        h->tab[i]->nb = 0;
    }

}
void copy(Hashage *h, Hashage *h2)
{

    for (int i=0; i<h->n; i++)
    {
        Element *elem = h2->tab[i]->first;
        for(int j = 0 ; j < h2->tab[i]->nb ; j++)
        {
            list_insert(h->tab[i], elem->nom);
            elem=elem->next;
        }
    }
}

int karger_itere(Matrix *m, Hashage *h, int nb_iter)
{
    int min = m->nb_aretes;
    int tmp;
    //groupe(h);
    for(int i=0;i<nb_iter;i++)
    {
        Matrix * m2 = copy_matrix(m);

        Hashage * h2 = init_hashage(m->n);
        for(int i = 0 ; i < m->n ; i++)
        {
            hash_insert(h2, i, i);
        }


        //Hashage * h2 = copy_hashage(h);
        tmp = karger(m2, h2);
        if(tmp<min)
        {    
            min = tmp;
            reset(h);
            copy(h,h2);
        }
        free_matrix(m2);
        free_hashage(h2);
    }  

    return min;
}

void contraction_partielle_matrice(int t, Matrix *m, Hashage *h)
{
    Arete a;

    if (t<=m->nb)
    {
        while (m->nb>t)
        { 
            do
            {
                a = tirage_arete(m);
            } while (m->m[a.u*m->n + a.v] <1);

            contraction_matrice( a, m, h);
            m->nb--;
        }
    }
}

int func_sqrt(int n){
    int sqrt = n / 2;
    int tmp = 0;

    while(sqrt != tmp){
        tmp = sqrt;
        sqrt = (n / tmp + tmp) / 2;
    }

    return sqrt;
}

int karger_stein_matrice(Matrix *mat, Hashage *h)
{
    int m1=0, m2=0,t=0;

    if (mat->nb<=6)
    {  
        return karger(mat, h);
    }
    else
    {
        t = 1 + func_sqrt(mat->nb);

        //G1 ← ContractionPartielle(G, t)
        Matrix *mat1 = copy_matrix(mat);
        Hashage *h1 = copy_hashage(h);
        contraction_partielle_matrice(t, mat1, h1);
        //S1 ← KargerStein(G1) ; m1 ← cardinal de la coupe (S1, V \ S1)
        m1 = karger_stein_matrice(mat1, h1);

        //G2 ← ContractionPartielle(G, t)
        Matrix *mat2 = copy_matrix(mat);
        Hashage *h2 = copy_hashage(h);
        contraction_partielle_matrice(t, mat2, h2);
        //S2 ← KargerStein(G2) ; m2 ← cardinal de la coupe (S2, V \ S2)
        m2 = karger_stein_matrice(mat2, h2);

        //si m1 < m2 alors
        if (m1<m2)
        {
            //S ← S1
            reset(h);
            copy(h, h1);
            free_matrix(mat2);
            free_hashage(h2);
            free_matrix(mat1);
            free_hashage(h1);
            return m1;
        }
        else
        {
            //S ← S2
            reset(h);
            copy(h, h2);

            free_matrix(mat2);
            free_hashage(h2);
            free_matrix(mat1);
            free_hashage(h1);
            return m2;
        }
    }

}


/* ********** Liste d'adjacence ********** */
void contraction_liste(Arete a, Hashage *g, Hashage *h)
{
    int m1=list_seek_elem(g->tab[a.v], a.u);
    int nb=0;

    g->nb_aretes-=m1;
    list_concat(g->tab[a.u], g->tab[a.v]);

    for(int i=0; i<g->n;i++)
    { 
        nb=list_seek_elem(g->tab[i], a.v);
       if (i!=a.u && i!=a.v && nb>0)
       {
            for (int j=0; j<nb; j++)
            {
               list_insert(g->tab[i], a.u);
            }

           list_delete(g->tab[i], a.v);  
       }
    }
    list_delete(g->tab[a.u], a.u); 
    list_delete(g->tab[a.u], a.v);  
    /*
    for(int i=0; i<g->n;i++)
    {
       list_delete(g->tab[i], a.v);  
    }
*/
    // On fusionne les listes du groupe
    Element *tmp = h->tab[a.v]->first; 
    for(int k = 0 ; k < h->tab[a.v]->nb ; k++) // On se deplace jusqu'a la fin de la liste
    {
        list_insert(h->tab[a.u], tmp->nom);
        tmp = tmp->next;
    }
    h->tab[a.v]->nb = 0; // On met a jour le nombre d'elements dans la liste v
}


Arete tirage_arete_liste(Hashage *h)
{
    Arete a;
    int i = rand()%h->n,j;

    while(h->tab[i]->nb == 0)
        i = rand()%h->n;

    j = rand()%h->n;
    while(list_seek_elem(h->tab[i],j) == 0)
        j = rand()%h->n;

    a.u = i;
    a.v = j;
    return a;
}

int karger_liste(Hashage *h, Hashage *h2)
{
    Arete a;

    while (h->nb>2)
    {
        // printf("nb : %d", h->nb);
        a = tirage_arete_liste(h);
        contraction_liste(a, h,h2);
        h->nb--;
    }
    return h->nb_aretes;
}

int karger_liste_itere(Hashage *h, int iter, Hashage *h2)
{
    int min = h->nb_aretes;
    int tmp;

    for(int i = 0 ; i < iter ; i++)
    {
        Hashage *h3 = copy_hashage(h);
        Hashage *h4 = init_hashage(h->n);
        for(int i = 0 ; i < h->n ; i++)
        {
            hash_insert(h4, i, i);
        }

        tmp = karger_liste(h3, h4);

        if(tmp < min)
        {
            min = tmp;
            reset(h2);
            copy(h2,h4);
        }

        free_hashage(h3);
        free_hashage(h4);
    }
    return min;
}

void contraction_partielle_liste(Hashage *h, Hashage *h2, uint t)
{
    Arete a;

    if (t<=h->nb)
    {
        while (h->nb>t)
        { 
            a = tirage_arete_liste(h);
            contraction_liste( a, h, h2);
            h->nb--;
        }
    }
}


int karger_stein_liste(Hashage *h, Hashage *h2)
{
    int m1 = 0, m2 = 0, t = 0;

    if (h->nb<=6)
    {
        return karger_liste(h, h2);
    } 
    else
    {
        t = 1 + func_sqrt(h->nb);
        //G1 ← ContractionPartielle(G, t)
        Hashage *h3 = copy_hashage(h);
        Hashage *h4 = copy_hashage(h2);
        contraction_partielle_liste(h3, h4, t);
        //S1 ← KargerStein(G1) ; m1 ← cardinal de la coupe (S1, V \ S1)
        m1 = karger_stein_liste(h3, h4);

        //G2 ← ContractionPartielle(G, t)
        Hashage *h5 = copy_hashage(h);
        Hashage *h6 = copy_hashage(h2);
        contraction_partielle_liste(h5, h6, t);
        //S2 ← KargerStein(G2) ; m2 ← cardinal de la coupe (S2, V \ S2)
        m2 = karger_stein_liste(h5, h6);

        if (m1<m2)
        {
            //S ← S1
            reset(h2);
            copy(h2, h4);
            free(h3);
            free(h4);
            free(h5);
            free(h6);
            return m1;
        }
        else
        {
            //S ← S2
            reset(h2);
            copy(h2, h6);
            free(h3);
            free(h4);
            free(h5);
            free(h6);
            return m2;
        }
    }
}

/* ********** solution de Kager ********** */
void groupe(Hashage *h)
{
    if(h!=NULL)
    {
        printf("Les groupes sont : \n");
        for(int i=0; i<h->n; i++)
        {
            if (h->tab[i]->nb > 0)
            {
                list_print(h->tab[i]);
            }

        }
    }

}
/* ********** Fonction calcul du temps ********** */
double wtime(){
    struct timeval ts;
    gettimeofday(&ts, NULL);
    return (double) ts.tv_sec + ts.tv_usec / 1e6;
}


