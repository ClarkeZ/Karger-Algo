/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#include "benchmark.h"

Benchmark *init_benchmark(int size){
    Benchmark *bench = malloc(sizeof(Benchmark));
    if(bench == NULL){
        perror("init_benchmark : Erreur allocation mémoire struct Benchmark !\n");
        exit(EXIT_FAILURE);
    }

    bench->times = malloc(sizeof(double)*size);
    if(bench->times == NULL){
        perror("init_benchmark : Erreur allocation mémoire struct Benchmark->temps !\n");
        exit(EXIT_FAILURE);
    }
    
    bench->nodes = malloc(sizeof(double)*size);
    if(bench->nodes == NULL){
        perror("init_benchmark : Erreur allocation mémoire struct Benchmark->nodes !\n");
        exit(EXIT_FAILURE);
    }

    bench->size = size;
    bench->algo = NULL;

    return bench;
}

void free_benchmark(Benchmark *bench){
    free(bench->times);
    free(bench->nodes);
    // free(bench->algo);
    // free(bench->name);
    free(bench);
}

Matrix *choix_matrix(int nb_nodes, int choix){
    switch(choix){
        case 0: return cycle(nb_nodes);         break;
        case 1: return complet(nb_nodes);       break;
        case 2: return biparti(nb_nodes);       break;
        case 3: return alea(nb_nodes);          break;
        case 4: return etoile(nb_nodes);        break;
    }
    perror("choix_matrix : Erreur choix de matrice !\n");
    exit(EXIT_FAILURE);
}

Hashage *choix_list(int nb_nodes, int choix){
    switch(choix){
        case 0: return cycle_liste(nb_nodes);         break;
        case 1: return complet_liste(nb_nodes);       break;
        case 2: return biparti_liste(nb_nodes);       break;
        case 3: return alea_liste(nb_nodes);          break;
        case 4: return etoile_liste(nb_nodes);        break;
    }
    perror("choix_list : Erreur choix de liste !\n");
    exit(EXIT_FAILURE);
}

char *choix_nom(int choix, int type){
    // type = 0 -> structure matrice
    if(type == 0){
        switch(choix){
            case 0: return "- Graphe Cyclique - Structure Matrice";    break;
            case 1: return "- Graphe Complet - Structure Matrice";     break;
            case 2: return "- Graphe Biparti - Structure Matrice";     break;
            case 3: return "- Graphe Aleatoire - Structure Matrice";   break;
            case 4: return "- Graphe Etoile - Structure Matrice";      break;
        }
        perror("choix_nom : Erreur choix de nom/matrice !\n");
        exit(EXIT_FAILURE);
    }
    // type = 1 -> structure liste
    else if(type == 1){
        switch(choix){
            case 0: return "- Graphe Cyclique - Structure Liste";    break;
            case 1: return "- Graphe Complet - Structure Liste";     break;
            case 2: return "- Graphe Biparti - Structure Liste";     break;
            case 3: return "- Graphe Aleatoire - Structure Liste";   break;
            case 4: return "- Graphe Etoile - Structure Liste";      break;
        }
        perror("choix_nom : Erreur choix de nom/liste !\n");
        exit(EXIT_FAILURE);
    }
    perror("choix_nom : Erreur choix de nom !\n");
    exit(EXIT_FAILURE);
}

char *choix_algo(int algo){
    if(algo == 0)
        return " - Algo Karger";
    else if(algo == 1)
        return " - Algo Karger Itere";
    else if(algo == 2)
        return " - Algo Karger Stein";
    else{
        perror("choix_algo : Erreur choix d'algo !");
        exit(EXIT_FAILURE);
    }
}

void bench_contraction_matrice(Benchmark *bench, int choix){
    double start, end, time;
    for(int i = 0; i < bench->size; i++){
        int nb_nodes = (i+1) * COEF;
        time = 0;
        for(int j = 0; j < NB_ITER; j++){
            Matrix *mat = choix_matrix(nb_nodes, choix);
            // Arete arete = tirage_arete(mat);
            Arete arete; arete.u = 0; arete.v = 1;
            Hashage *h = init_hashage(nb_nodes);
            start = wtime();
            contraction_matrice(arete, mat, h);
            end = wtime();
            time += (end - start);
            free_matrix(mat);
            free_hashage(h);
        }
        bench->times[i] = time / NB_ITER;
        bench->nodes[i] = nb_nodes;
    }
    bench->name = choix_nom(choix, 0);
    bench->algo = " - Contraction Matrice";
}

void bench_contraction_liste(Benchmark *bench, int choix){
    double start, end, time;
    for(int i = 0; i < bench->size; i++){
        int nb_nodes = (i+1) * COEF;
        time = 0;
        for(int j = 0; j < NB_ITER; j++){
            Hashage *liste = choix_list(nb_nodes, choix);
            Arete arete = tirage_arete_liste(liste);
            Hashage *h = init_hashage(nb_nodes);
            start = wtime();
            contraction_liste(arete, liste, h);
            end = wtime();
            time += (end - start);
            free_hashage(liste);
            free_hashage(h);
        }
        bench->times[i] = time / NB_ITER;
        bench->nodes[i] = nb_nodes;
    }
    bench->name = choix_nom(choix, 1);
    bench->algo = " - Contraction Liste";
}


void bench_karger(Benchmark *bench, int choix, int algo){
    double start, end, time;
    for(int i = 0; i < bench->size; i++){
        int nb_nodes = (i+1) * COEF; // 10 nodes per step
        time = 0;
        for(int j = 0; j < NB_ITER ; j++){
            printf("ite : %d", j);
            Matrix *mat = choix_matrix(nb_nodes, choix); // A MODIFIER 
            Hashage *h = init_hashage(nb_nodes);
            for(int k = 0; k < nb_nodes; k++){
                hash_insert(h, k, k);
            }
            start = wtime();
            if(algo == 0){
                karger(mat, h);
            }
            else if(algo == 1){
                karger_itere(mat, h, 10);
            }
            else if(algo == 2){
                karger_stein_matrice(mat, h);
            }
            else{
                perror("bench_karger : Erreur choix de l'algorithme !\n");
                exit(EXIT_FAILURE);
            }
            end = wtime();
            time += (end - start);
            free_matrix(mat);
            free_hashage(h);
        }
        bench->times[i] = time / NB_ITER;
        bench->nodes[i] = nb_nodes;
    }
    bench->name = choix_nom(choix, 0);
    bench->algo = choix_algo(algo);
}

void bench_karger_liste(Benchmark *bench, int choix, int algo){
    double start, end, time;
    printf("hello");
    for(int i = 0; i < bench->size; i++){
        int nb_nodes = (i+1) * COEF; // 10 nodes per step
        time = 0;
        for(int j = 0; j < NB_ITER ; j++){
            Hashage *liste = choix_list(nb_nodes, choix);
            Hashage *h = init_hashage(nb_nodes);
            for(int k = 0; k < nb_nodes; k++){
                hash_insert(h, k, k);
            }
            start = wtime();
            if(algo == 0){
                karger_liste(liste, h);
            }
            else if(algo == 1){
                karger_liste_itere(liste, 5, h);
            }
            else if(algo == 2){
                karger_stein_liste(liste, h);
            }
            else{
                perror("bench_karger_liste : Erreur choix de l'algorithme !\n");
                exit(EXIT_FAILURE);
            }
            end = wtime();
            time += (end - start);
            free_hashage(liste);
            free_hashage(h);
        }
        bench->times[i] = time / NB_ITER;
        bench->nodes[i] = nb_nodes;
    }
    bench->name = choix_nom(choix, 1);
    bench->algo = choix_algo(algo);
}

void bench_matrix(Benchmark *bench, int choix){
    double start, end, time;
    for(int i = 0; i < bench->size; i++){
        int nb_nodes = (i+1) * COEF; 
        time = 0;
        for(int j = 0; j < NB_ITER ; j++){
            start = wtime();
            Matrix *mat = choix_matrix(nb_nodes, choix);
            end = wtime();
            time += (end - start);
            free_matrix(mat);
        }
        bench->times[i] = time / NB_ITER;
        bench->nodes[i] = nb_nodes;
    }
    bench->name = choix_nom(choix, 0);
}

void bench_liste(Benchmark *bench, int choix){
    double start, end, time;
    for(int i = 0; i < bench->size; i++){
        int nb_nodes = (i+1) * COEF; 
        time = 0;
        for(int j = 0; j < NB_ITER ; j++){
            start = wtime();
            Hashage *liste = choix_list(nb_nodes, choix);
            end = wtime();
            time += (end - start);
            free_hashage(liste);
        }
        bench->times[i] = time / NB_ITER;
        bench->nodes[i] = nb_nodes;
    }
    bench->name = choix_nom(choix, 1);
}

int courbe(Benchmark *bench)
{
    const char *nom_fichier = "graphe.txt";
    FILE *fichier = NULL;
    fichier = fopen(nom_fichier, "w");
    
    if(fichier == NULL)
    {
        perror("Erreur ouverture fichier !\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fichier, "%s\n", bench->name);
    if(bench->algo == NULL)
        fprintf(fichier, "%s\n", "no algo");
    else
        fprintf(fichier, "%s\n", bench->algo);
    // fprintf(fichier, "import matplotlib.pyplot as plt \nplt.plot(range(%d))\nplt.ylabel('Temps en ms')\nplt.xlabel('Nombre de sommets')\n", nbSommets);
    for(int i = 0 ; i < bench->size ; i++)
    {
        fprintf(fichier, "nbSommet = %d, temps = %f\n", bench->nodes[i], bench->times[i]);
    }
    fclose(fichier);

    return 0;
}

void choix_bench(int size, int bench, int matrice, int algo){
    Benchmark *b = init_benchmark(size);
    switch(bench){
        case 0 : bench_contraction_matrice(b, matrice); break;
        case 1 : bench_contraction_liste(b, matrice); break;
        case 2 : bench_karger(b, matrice, algo); break;
        case 3 : bench_karger_liste(b, matrice, algo); break;
        case 4 : bench_matrix(b, matrice); break;
        case 5 : bench_liste(b, matrice); break;
        default : 
            perror("Erreur choix benchmark");
            exit(EXIT_FAILURE);
        break;
    }

    // Ecriture dans un fichier graphe.txt des resultats
    if(courbe(b) == 0){
        // printf("Ecriture dans un fichier avec succes !\n");
        
        // Arguments pour execv : appel de python pour tracer la courbe
        char *const argList[] = {"/usr/bin/python3", "graph.py", NULL};
        // Execution de python
        if(execv(argList[0], argList) < 0){
            perror("Erreur execv");
            exit(EXIT_FAILURE);
        }
    }
    else{
        perror("Erreur ecriture dans un fichier");
        exit(EXIT_FAILURE);
    }

    free_benchmark(b);
}

void karger_proba_succes(int nb_nodes, int nb_iter, int choix){
    int nb_succes = 0;
    int k;
    // int nb_min = nb_nodes;
    // int nb_max = 0;
    int toto = 0;
    int nb;
    for(k = 0 ; k < 20 ; k++){
        for(int i = 0; i < nb_iter; i++){
            Matrix *mat = choix_matrix(nb_nodes, choix);
            // printf("arete : %d\n", mat->nb_aretes);
            Hashage *h = init_hashage(nb_nodes);
            for(int k = 0; k < nb_nodes; k++){
                hash_insert(h, k, k);
            }
            nb = karger(mat, h);
            // printf("nb : %d\n", nb);
            // if(nb < nb_min)
            //     nb_min = nb;
            // else if(nb > nb_max)
            //     nb_max = nb;
            // else 
            //     nb_succes++;

            if(nb == 1){
                nb_succes++;
            }

            // groupe(h);
            free_matrix(mat);
            free_hashage(h);
        }
        printf("Nombre de succes : %d/%d\n", nb_succes, nb_iter);
        toto += nb_succes;
        nb_succes = 0;
    }
    printf("Pourcentage de succes : %d\n", (toto / k));
}