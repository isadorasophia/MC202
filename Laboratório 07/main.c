/* Isadora Sophia Garcia Rodopoulos
 * RA: 158018
 * MC202B - LAB07 - Cobertura de Conjuntos */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cobertura.h"

int main () {
    int u, n, i;
    ListNode *S, *R, *aux;
    TreeNode *U = NULL;
    
    /* Inicializa a cabeca das listas */
    S = createListNode(NULL, 0);
    R = createListNode(NULL, 0);
    
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
    
    /* Caso o metodo guloso tenha sido bem sucedido, imprime os
     * conjuntos escolhidos */
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
    /* Caso o metodo guloso nao tenha sido bem sucedido */
    } else
        printf(":(\n");
        
    return 0;
}