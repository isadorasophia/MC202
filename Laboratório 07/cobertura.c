#include "cobertura.h"

#define MAX_NUMBER_LENGTH 11

/* Prototipos de funcoes auxiliares para a biblioteca */
int removeIntersecao (TreeNode **p, TreeNode *beGone);
ListNode *findMaxSub (ListNode *S);

/* Retorna um subconjunto recebido na entrada */
ListNode* leConjunto (int order) {
    char number[MAX_NUMBER_LENGTH], end;
    ListNode *S;
    
    getchar();
    
    /* Realiza a leitura do numero */
    scanf("%s%c", number, &end);
    
    /* Aloca-o na arvore, acrescentando o seu tamanho */
    S = createListNode(createTree(atoi(number)), order);
    S->size++;
    
    /* Realiza o mesmo procedimento para todos os elementos do subconjunto */
    while (end != '\n') {
        scanf ("%s%c", number, &end);
       
        S->s = insereTreeNode(S->s, atoi(number));
        S->size++;
    }
    
    return S;
}

/* Retorna se o metodo guloso foi realizado com sucesso */
int guloso(ListNode *R, TreeNode *U, ListNode *S) {
    ListNode *maxSub, *aux;
    
    while (U != NULL && S->next != NULL) {
        /* Seleciona e remove o conjunto de maior quantidade 
         * de elementos em U */
        maxSub = removeListNode(findMaxSub(S));

        aux = S;
        
        /* Realiza a leitura de todos os subconjuntos em S */
        while (aux->next != NULL) {
#ifdef DEBUG
            printf("Removing intersection of S%d in S%d\n",
                    aux->next->order, maxSub->order);
#endif
            
            /* Remove a interseccao dos elementos dos subconjuntos de S 
             * com maxSub */
            aux->next->size -= removeIntersecao(&(aux->next->s), maxSub->s);
            
            /* Caso o conjunto tenha sido esvaziado */
            if (!(aux->next->size))
                free(removeListNode(aux));
            else
                aux = aux->next;
        }
        
        /* Remove a interseccao de U com S */
        removeIntersecao(&U, maxSub->s);
        
        /* Acrescenta subconjunto escolhido pela abordagem gulosa */
        R->next = createListNode(NULL, maxSub->order);
        R = R->next;
        
        /* Remove o subconjunto utilizado */
        freeTree(maxSub->s);
        free(maxSub);
    }
    
    /* Libera a memoria dos subconjuntos de S */
    freeList(S);
    
    /* Caso o universo tenha sido esvaziado e a lista R seja valida */
    if (U == NULL)
        return 1;
   
    /* Libera a memoria do universo */
    freeTree(U);
    
    /* ...o metodo nao foi realizado com sucesso */
    return 0;
}

/* Elimina a intersecao dos elementos de "beGone" em "p" e retorna a
 * quantidade eliminada */
int removeIntersecao (TreeNode **p, TreeNode *beGone) {
    int removido = 0;
    
    /* Caso uma das arvores esteja vazia */
    if ((*p) == NULL || beGone == NULL)
        return 0;
    
    /* Caso haja o elemento para ser removido */
    if (buscaTree((*p), beGone->elem))
        removido++;
    
    (*p) = removeTreeNode((*p), beGone->elem);
    
    removido += removeIntersecao (p, beGone->esq);
    removido += removeIntersecao (p, beGone->dir);
    
    return removido;
}

/* Retorna o no anterior ao no de maior tamanho da lista */
ListNode *findMaxSub (ListNode *S) {
    ListNode *max;
    
    max = S;
    S = S->next;
    
    while (S->next) {        
        if (S->next->size >= max->next->size)
            max = S;
       
        S = S->next;
    }

    return max;
}