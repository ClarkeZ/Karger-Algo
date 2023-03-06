/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#include "benchmark.h"

void type_bench(){
    printf("L'algorithme que vous souhaitez tester : \n");
    printf("1 - Contraction - Structure Matrice\n");
    printf("2 - Contraction - Structure Liste\n");
    printf("3 - Algorithme de Karger - Structure Matrice\n");
    printf("4 - Algorithme de Karger - Structure Liste\n");
    printf("5 - Création d'un graphe - Structure Matrice\n");
    printf("6 - Création d'un graphe - Structure Liste\n");

}

void type_matrice(){
    printf("1 - Matrice cyclique\n");
    printf("2 - Matrice complete\n");
    printf("3 - Matrice biparti\n");
    printf("4 - Matrice aleatoire\n");
    printf("5 - Matrice etoile\n");
}

void type_karger(){
    printf("1 - Karger\n");
    printf("2 - Karger itere\n");
    printf("3 - Karger-Stein\n");
}

void test(int size){
    int bench = 0;
    int matrice = 0;
    int algo = 0;

    while(bench < 1 || bench >= 6){
        type_bench();
        if(scanf("%d", &bench) == 1)
            if(bench > 0 && bench <= 6)
                break;
    }

    while(matrice < 1 || matrice >= 5){
        type_matrice();
        if(scanf("%d", &matrice) == 1)
            if(matrice > 0 && matrice <= 5)
                break;
    }


    if(bench == 3 || bench == 4){
        while(algo < 1 || algo > 3){
            type_karger();
            if(scanf("%d", &algo) == 1)
                if(algo > 0 && algo <= 3)
                    break;
        }
    }
    
    // Car dans le switch on commence a 0
    bench--;
    matrice--;
    algo--;

    choix_bench(size, bench, matrice, algo);
}

int main (int argc, char *argv[])
{
    srand(time(NULL));
    // int n = 10;
    // printf("********** Matrice d'adjacence **********\n");

    // Matrix *mat = complet(n);
    // Matrix *mat2 = copy_matrix(mat);
    
    // Hashage *h = init_hashage(n);
    // for(int i=0;i<n;i++)
    // {
    //     hash_insert(h, i, i);
    // }
    // //print_matrix(mat);

    // // printf("\nLa coupe minimal est de : %d\n\n",karger(mat, h));
    // // print_matrix(mat);

    // printf("\nKarger itéré:\nLa coupe minimal est de : %d\n\n", karger_itere(mat2, h,n*n));

    // groupe(h);
    
    // free_matrix(mat);
    // free_matrix(mat2);
    // free_hashage(h);

    // printf("\n********** Liste d'adjacence **********\n\n");
    // Hashage *h2 = complet_liste(n);
    // Hashage *h3 = init_hashage(n);
    // for(int i=0;i<n;i++)
    // {
    //     hash_insert(h3, i, i);
    // }
    // print_hashage(h2);

    //printf("Karger :\nLa coupe minimal est de : %d\n\n",karger_liste(h2,h3));
    // printf("\nKarger itéré:\nLa coupe minimal est de : %d\n\n",karger_liste_itere(h2,n*n*n*n,h3));
    
    // groupe(h3);
    // free_hashage(h2);
    
    





    // int n = 100;
    // printf("********** Matrice d'adjacence **********\n");
    //  Matrix *mat = complet(n);
    // Matrix *mat2 = copy_matrix(mat);
    // Matrix *mat3 = copy_matrix(mat);
    //  Hashage *h = init_hashage(n);
    // for(int i=0;i<n;i++)
    // {
    //     hash_insert(h, i, i);
    // }
    // Hashage *h2 = copy_hashage(h);
    // Hashage *h3 = copy_hashage(h);

    // int min =0, min2=0, min3=0;

    //  min=karger(mat, h);
    // min2=karger_itere(mat2, h2,n*n);
    // min3=karger_stein_matrice(mat3, h3);

    // if (min<min2 && min<min3)
    // {
        // printf("Karger : la coupe minale est %d\n",min);
        // groupe(h);
    // }
    // else if (min2<min && min2<min3)
    // {
    //     printf("Karger itéré : la coupe minale est %d\n",min2);
    //     groupe(h2);
    // }
    // else
    // {
    //     printf("Karger Stein : la coupe minale est %d\n",min3);
    //     groupe(h3);
    // }
    
    
    // free_matrix(mat);
    // free_matrix(mat2);
    // free_matrix(mat3);
    // free_hashage(h);
    // free_hashage(h2);
    // free_hashage(h3);

    // printf("\n********** Liste d'adjacence **********\n\n");
    // Hashage *hash= complet_liste(n);
    // Hashage *hash2= copy_hashage(hash);
    // Hashage *hash3= copy_hashage(hash);
    // Hashage *h4 = init_hashage(n);
    // for(int i=0;i<n;i++)
    // {
    //     hash_insert(h4, i, i);
    // }
    // Hashage *h5 = copy_hashage(h4);
    // Hashage *h6 = copy_hashage(h4);

    // min=karger_liste(hash, h4);
    // printf("Karger : la coupe minale est %d\n",min);
    // groupe(h4);
    // free_hashage(h4);
    // free_hashage(hash);
    // min2=karger_liste_itere(hash2, 5, h5);
    // printf("Karger itéré : la coupe minale est %d\n",min2);
    // groupe(h5);
    // free_hashage(h5);
    // free_hashage(hash2);
    // min3=karger_stein_liste(hash3, h6);
    // printf("Karger Stein : la coupe minale est %d\n",min3);
    // groupe(h6);
    // free_hashage(h6);
    // free_hashage(hash3);


    // if (min<min2 && min<min3)
    // {
    // }
    // else if (min2<min && min2<min3)
    // {
    // }
    // else
    // {
    // }
    
    int size = 10;

    if(argc == 2){
        if(strcmp(argv[1], "-n") == 0){
            size = atoi(argv[2]);
        }
    }




    test(size);


    // int size = 8;
    
    // int bench = 2;
    // int matrice = 0;
    // int algo = 2;
    // choix_bench(size, bench, matrice, algo);
    // Calcul le nombre de succés pour chaque taille de graphe
    // karger_proba_succes(size, 100, matrice);



    return EXIT_SUCCESS;
}