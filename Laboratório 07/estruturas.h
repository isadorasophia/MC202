/* Biblioteca responsavel por implementar operacoes de arvore binaria e de
 * lista */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estruturas necessarias para a implementacao da biblioteca */
typedef struct TreeNode {
    int elem;
    struct TreeNode *esq, *dir;
} TreeNode;

typedef struct ListNode {
    int size;
    int order;
    TreeNode *s;
    struct ListNode *next;
} ListNode;

#ifdef DEBUG
void preOrder (TreeNode *r);
#endif

/* Retorna um no de arvore */
TreeNode* createTree (int n);

/* Insere, com afunilamento, um elemento "n" em uma arvore de busca */
TreeNode* insereTreeNode (TreeNode *r, int n);

/* Remove, com afunilamento, um elemento "n" em uma arvore de busca */
TreeNode* removeTreeNode (TreeNode *r, int n);

/* Retorna se o elemento "n" existe na arvore */
int buscaTree (TreeNode *r, int n);

/* Libera a memoria de uma arvore */
void freeTree (TreeNode *p);

/* Retorna o no de uma lista ligada */
ListNode* createListNode(TreeNode *s, int order);

/* Remove o no posterior ao no "p" da lista */
ListNode* removeListNode (ListNode *p);

/* Libera a memoria de uma lista */
void freeList (ListNode *p);