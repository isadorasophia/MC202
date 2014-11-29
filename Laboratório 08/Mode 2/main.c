/* Isadora Sophia Garcia Rodopoulos
 * RA: 158018
 * MC202B - LAB08 - Menor Ancestral Comum */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

#define MAX_LENGHT 5

int main () {
    char operation[MAX_LENGHT];
    int N, M, a, b;
    Tree *florest;
    
    scanf("%d %d", &N, &M);
    
    /* Create N trees linked to a single vertex and set them right */
    florest = malloc ((N + 1) * sizeof(Tree));
    setFlorest (florest, N + 1);
    
    /* Read and execute the requested operation */
    while (M--) {
        scanf("%s", operation);
        
        if (strcmp(operation, "lca") == 0) {
            scanf("%d %d", &a, &b);
            
            printf("%d\n", lca(a, b, florest));
        }
        else if (strcmp(operation, "link") == 0) {
            scanf("%d %d", &a, &b);
            
            link (a, b, florest, N + 1);
        }
        else if (strcmp(operation, "cut") == 0) {
            scanf("%d", &a);
            
            cut (a, florest, N + 1);
        }
    }
    
    /* Deallocate memory */
    free (florest);
    
    return 0;
}