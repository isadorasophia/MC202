#include "cobertura.h"

#define MAX_NUMBER_LENGTH 11

int removeIntersecao (TreeNode **p, TreeNode *beGone);
ListNode *findMaxSub (ListNode *S);

ListNode* leConjunto (int order) {
    char number[MAX_NUMBER_LENGTH], end;
    ListNode *S;
    
    getchar();
    
    scanf("%s%c", number, &end);
    
    S = createListNode(createTreeNode(atoi(number)), order);
    S->size++;
    
    while (end != '\n') {        
        scanf ("%s%c", number, &end);
       
        S->s = insereTreeNode(S->s, atoi(number));
        S->size++;
    }
    
    return S;
}

/* Retorna se o metodo guloso foi reealizado com sucesso */
int guloso(ListNode *R, TreeNode *U, ListNode *S) {
    ListNode *maxSub, *aux;
    
    while (U != NULL && S->next != NULL) {
        /* Seleciona e remove o conjunto de maior quantidade 
         * de elementos em U */
        maxSub = removeListNode(findMaxSub(S));
        
#ifdef DEBUG
        printf("Next step: removing the interception of S with S%d\n", maxSub->order);

        if (maxSub->order == 38)
            printf("tamanho do 38 eh %d e o do 44 eh ", maxSub->size);
#endif
        aux = S;
        
        while (aux->next != NULL) {
#ifdef DEBUG
//             printf("Removing interception with S%d\n", aux->next->order);
#endif
            
            aux->next->size -= removeIntersecao(&(aux->next->s), maxSub->s);
            
            /* Caso tenha esvaziado o conjunto */
            if (!(aux->next->size)) {
//                printf("removo o S%d\n", aux->next->order);
                free(removeListNode(aux));
//                 if (aux->next != NULL)
//                     aux = aux->next;
            }
            else
                aux = aux->next;
        }
        
#ifdef DEBUG
//         printf("Next step: removing the interception with U\n");
#endif
        
        removeIntersecao(&U, maxSub->s);
        
        R->next = createListNode(NULL, maxSub->order);
        R = R->next;
        
        /* Remove subconjunto utilizado */
        freeTree(maxSub->s);
        free(maxSub);
    }
    
    /* Como nao usara mais os subconjuntos S... */
    freeList(S);
    
    /* Caso o universo tenha sido esvaziado e a lista R seja valida */
    if (U == NULL)
        return 1;
   
    /* Como nao foi possivel cobrir U... */
    freeTree(U);
    
    return 0;
}

/* Retorna quantos elementos foram eliminados de "p" */
int removeIntersecao (TreeNode **p, TreeNode *beGone) {
    int removido = 0;
    
    /* Caso uma das arvores esteja vazia */
    if ((*p) == NULL || beGone == NULL)
        return 0;
    
    /* Caso haja o elemento para ser removido */
    if (buscaTree((*p), beGone->elem))
        removido++;
    
    (*p) = removeTreeNode((*p), beGone->elem);
//     printf("apos a remocao do %d:", beGone->elem);
//     preOrder((*p));
//     printf("\n");
    
    removido += removeIntersecao (p, beGone->esq);
    removido += removeIntersecao (p, beGone->dir);
    
    return removido;
}

/* Retorna um no anterior ao de maior tamanho */
ListNode *findMaxSub (ListNode *S) {
    ListNode *max;
    
    max = S;
    S = S->next;
    
    while (S->next) {        
        if (S->next->size >= max->next->size)
            max = S;
       
        S = S->next;
    }
    
#ifdef DEBUG
//     printf("Found the maxSub S%d\n", max->next->order);
#endif
    
    return max;
}