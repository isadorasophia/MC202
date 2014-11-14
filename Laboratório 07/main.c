#include <stdio.h>
#include <stdlib.h>
#include "cobertura.h"

int main () {
    int u, n, i;
    char elemChar;
    ListNode *S = createListNode(NULL), *R = createListNode(NULL), *aux;
    TreeNode *U = NULL;
    
    scanf("%d %d", &u, &n);
    
    /* Inicia o universo U */
    U = createTreeNode(1);
    
    for (i = 2; i <= u; i++)
        insereTree(U, i);
    
    getchar ();
    
    /* Realiza a leitura da colecao S de subconjuntos */
    for (i = 1, aux = S->next; i <= n; i++) {
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