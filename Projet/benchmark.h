/*
 * Authors : Jessica Laurent & Clarke Zhou
 * 
 * v1.00 (2022-12)
 * 
 */
#ifndef BENCHMARK_H_
#define BENCHMARK_H_

#include "karger.h"

#include <unistd.h> 

#define COEF 1
#define NB_ITER 2

typedef struct Benchmark {
    int *nodes;
    double *times;
    int size;
    char *name;
    char *algo;
} Benchmark;

Benchmark *init_benchmark(int size);
void free_benchmark(Benchmark *benchmark);

Matrix *choix_matrix(int nb_nodes, int choix);
Hashage *choix_list(int nb_nodes, int choix);

char *choix_nom(int choix, int type);
char *choix_algo(int algo);


void bench_contraction_matrice(Benchmark *bench, int choix);
void bench_contraction_liste(Benchmark *bench, int choix);

void bench_karger(Benchmark *bench, int choix, int algo);
void bench_karger_liste(Benchmark *bench, int choix, int algo);

void bench_matrix(Benchmark *bench, int choix);
void bench_liste(Benchmark *bench, int choix);

int courbe(Benchmark *bench);

void choix_bench(int size, int bench, int matrice, int algo);

void karger_proba_succes(int nb_nodes, int nb_iter, int choix);

#endif // BENCHMARK_H