#include "quick.h"

/* Estima o custo medio do algoritmo do quicksort aleatorizado, a partir
 * do vetor A de tamanho r */
double quicksort(int *A, int r) {
    /* Caso o tamanho seja menor que 2, nao ha necessidade de ordena-lo */
    if (r < 2)
        return 0;
    
    int i, l0_size = 0, l1_size = 0;
    int *l0, *l1;
    double custoMedio = 0;
    
    /* Aloca memoria para os vetores l0 e l1 */
    l0 = malloc (r * sizeof(l0));
    l1 = malloc (r * sizeof(l1));
    
    /* Para cada um dos valores pivot de A, estima seu custo total e o
     * acrescenta ao custo medio */
    for (i = 0; i < r; i++) {
        /* Custo individual de A */
        custoMedio += (double)particiona (A, i, r, 
                                    l0, l1, &l0_size, &l1_size)/r;
        
        /* Custos totais das chamadas recursivas de A */
        custoMedio += quicksort(l0, l0_size)/r;
        custoMedio += quicksort(l1, l1_size)/r;
    }
    
    /* Liberacao de memoria */
    free(l0);
    free(l1);
    
    /* Retorna o custo total do vetor A */
    return custoMedio;
}

/* Particiona a sequencia em l0 - com todos os elementos menores - e l1 - com
 * todos os elementos maiores. Retorna o custo desta particao */
int particiona(int *A, int p, int r, 
               int *l0, int *l1, int *l0_size, int *l1_size) {
    int i = 0, custoIndividual = 0;
 
    /* Inicia valores de l0 e l1 */
    (*l0_size) = 0;
    (*l1_size) = 0;
    
    /* Particiona o vetor em elementos maiores ou menores que o pivot A[p] */
    for (i = 0; i < r; i++) {
        // Caso o elemento seja menor
        if (A[i] < A[p]) {
            l0[(*l0_size)++] = A[i];
            // Caso o elemento esteja a direita, aumenta o custo
            if (i > p)
                custoIndividual++;
        }
        
        // Caso o elemento seja maior
        else if (A[i] > A[p]) {
            l1[(*l1_size)++] = A[i];
            // Caso o elemento esteja a esquerda, aumenta o custo
            if (i < p) {
                custoIndividual++;
            }
        }
    }

    return custoIndividual;
}