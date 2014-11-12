#include <stdio.h>
#include <stdlib.h>
#include "cobertura.h"

int main () {
    int u, n, i;
    char elemChar;
    ListNode *S = createListNode(NULL), *R = NULL;
    TreeNode *U = NULL;
    
    scanf("%d %d", &u, &n);
    
    /* Inicia o universo U */
    U = createTreeNode(1);
    
    for (i = 2; i <= u; i++)
        insereTree(U, i);
    
    getchar ();
    
    /* Realiza a leitura da colecao S de subconjuntos */
    for (i = 1; i <= n; i++) {
        S->next = leConjunto(i);
        
        S = S->next;
    }
    
    if (guloso(&R, U, S) && !R) {
        while (!R) {
            R = R->next
            printf("S%d ", R->order);
        
            if (R)
                printf("U ");
            else
                printf(":)\n");
        }
    } else
        printf(":(\n");
        
    return 0;
}