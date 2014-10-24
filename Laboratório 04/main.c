/* Isadora Sophia Garcia Rodopoulos
 * RA: 158018
 * MC202B - LAB04 */

#include <stdio.h>
#include <stdlib.h>
#include "quick.h"

int main () {
    int i, n, *A;
    double custoMedio;
    
    scanf("%d", &n);
    
    /* Aloca memoria necessaria para a sequencia */
    A = malloc(n * sizeof(A));
    
    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);
    
    /* Estima o custo medio da sequencia a partir do algoritmo do Quicksort
     * aleatorizado */
    custoMedio = quicksort(A, n);

    printf("%.10f\n", custoMedio);
    
    /* Liberacao de memoria */
    free(A);
    
    return 0;
}