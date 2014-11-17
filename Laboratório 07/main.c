#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cobertura.h"

int main () {
    int u, n, i;
    ListNode *S = createListNode(NULL, 0), *R = createListNode(NULL, 0), *aux;
    TreeNode *U = NULL;
    
    scanf("%d %d", &u, &n);
    
    /* Inicia o universo U */    
    for (i = 1; i <= u; i++)
        U = insereTreeNode(U, i);
    
    /* Realiza a leitura da colecao S de subconjuntos */
    for (i = 1, aux = S; i <= n; i++) {
        /* Realiza a leitura do char "s" */
        getchar ();
        
        aux->next = leConjunto(i);
        aux = aux->next;
    }
    
    if (guloso(R, U, S)) {
        while (R->next) {
            aux = R;
            R = R->next;
            free(aux);
            
            printf("S%d ", R->order);
        
            if (R->next)
                printf("U ");
            else
                printf(":)\n");
        }
    } else
        printf(":(\n");
        
    return 0;
}