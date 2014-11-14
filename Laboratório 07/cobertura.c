#include "cobertura.h"

int castInt (char a) {
    return a - 48;
}

ListNode* leConjunto (int order) {
    char elemChar;
    ListNode *S;
    
    scanf("%c", elemChar);
    
    S = createListNode(createTreeNode(castInt(elemChar)), order);
    
    while (elemChar != 's') {
        S->s = insereTree(S->s, castInt(elemChar));
        
        scanf ("%c", elemChar);
        
        S->size++;
    }
    
    return S;
}

/* Retorna se o metodo guloso foi reealizado com sucesso */
int guloso(ListNode *R, TreeNode *U, ListNode *S) {
    ListNode *maxSub, *head = S;
    
    while (!U && S->next) {
        /* Seleciona e remove o conjunto de maior quantidade 
         * de elementos em U */
        maxSub = removeListNode(findMaxSub(S));
        
        for (S = head; S->next; S = S->next) {
            S->next->size -= removeIntersecao(&(S->s), maxSub->s);
            
            /* Caso tenha esvaziado o conjunto */
            if (!(S->size))
                free(removeListNode(S));
        }
        
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
    if (!U && R->next)
        return 1;
   
    /* Como nao foi possivel cobrir U... */
    freeTree(U);
    
    return 0;
}

/* Retorna quantos elementos foram eliminados de "p" */
int removeIntersecao (TreeNode **p, TreeNode *beGone) {
    /* Caso uma das arvores esteja vazia */
    if (!(*p) || !beGone)
        return 0;
    
    int removido = 0;
    
    /* Caso haja o elemento para ser removido */
    if (buscaTree(beGone->elem))
        removido++;
    
    (*p) = removeTreeNode(p, beGone->elem);
    
    removido += removeIntersecao (p, beGone->esq);
    removido += removeIntersecao (p, beGone->dir);
    
    return removido;
}

/* Retorna um no anterior ao de maior tamanho */
ListNode *findMaxSub (ListNode *S) {
    ListNode = *max;
    
    max = S;
    
    while (S->next) {
        S = S->next;
        
        if (S->next->size >= max)
            max = S;
    }
    
    return S;
}