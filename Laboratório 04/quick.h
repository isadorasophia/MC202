/* Isadora Sophia Garcia Rodopoulos
 * RA: 158018
 * MC202B - LAB04 */

#include <stdio.h>
#include <stdlib.h>

/* Estima o custo medio do algoritmo do quicksort aleatorizado, a partir
 * do vetor A de tamanho r */
double quicksort(int *A, int r);

/* Particiona a sequencia em l0 - com todos os elementos menores - e l1 - com
 * todos os elementos maiores. Retorna o custo desta particao */
int particiona(int *A, int p, int r, 
               int *l0, int *l1, int *l0_size, int *l1_size);