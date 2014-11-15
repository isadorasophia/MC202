#include "estruturas.h"

#define NOT_FOUND 1

TreeNode* createTreeNode (int n) {
    TreeNode *t;
    
    t->elem = n;
    t->esq = NULL;
    t->dir = NULL;
    
    return t;
}

TreeNode* insereTreeNode (TreeNode *r, int n) {
    TreeNode *p, *f, *new = createTreeNode(n);
    
    if (!r)
        return new;
    
    f = r;
    
    /* Encontra espaco mais adequado para alocao do novo no */
    while (f) {
        p = f;
        
        if (new->elem < f->elem)
            f = f->esq;
        else
            f = f->dir;
    }
    
    if (new->elem < p->elem)
        p->esq = new;
    else
        p->dir = new;
    
    return afunilamento(r, n);    
}

TreeNode* removeTreeNode (TreeNode *r, int n) {
    TreeNode *p, *f = r;
    int found = 0, newR;
    
    /* Caso o elemento seja a raiz */
    if (r->elem == n) {
        free(r);
        return NULL;
    }
    
    /* Encontra o pai do no a ser removido */
    while (!found && f) {
        if (n == f->elem)
            found = 1;
        else if (n < f->elem) {
            p = f;
            f = f->esq;
        }
        else {
            p = f;
            f = f->dir;
        }
    }
    
    if (found) {
        if (n < p->elem) {
            p->esq = RemoveRaiz(p->esq);
            newR = findNewRoot(p->esq);
        }
        else {
            p->dir = RemoveRaiz(p->dir);
            newR = findNewRoot(p->dir);
        }
    }
    
    if (newR == NOT_FOUND || !found)
        newR = p->elem;

    afunilamento(r, newR);
}

TreeNode *RemoveRoot (TreeNode *r) {
    No *p, *q;
    
    /* Caso nao haja filhos na esquerda */
    if (r->esq == NULL) 
        q = r->dir;
    
    /* Caso haja filho na esquerda, encontra antecessor para ser a nova raiz */
    else {
        p = r;
        q = r->esq;
        
        /* Encontra maior elemento "q" da subarvore, sendo "p" o seu pai */
        while (q->dir) {
            p = q;
            q = q->dir;
        }
        
        /* Caso a nova raiz nao seja o filho a esquerda da raiz */
        if (p != r) {
            p->dir = q->esq;
            q->esq = r->esq;
        }
        
        q->dir = r->dir;
    }
    
    free(r);
    
    return q;
}

int findNewRoot (TreeNode *r) {
    /* Caso nao ha filhos, nao cabe a esta funcao determinar a nova raiz */
    if (r->esq == NULL && r->dir == NULL)
        return NOT_FOUND;
    
    /* Caso nao haja esquerda, encontra o menor elemento da subarvore direita */
    if (r->esq == NULL) {
        r = r->dir;
        while (r)
            r = r->dir;
    }   
    /* Caso haja apenas esquerda ou ambos, encontra o maior elemento da
     * esquerda */
    else if (r->dir == NULL) {
        r = r->esq;
        while (r)
            r = r->esq;
    }
    
    return r->elem;
       
}

/* Retorna se o elemento buscado existe na arvore */
int buscaTree (TreeNode *r, int n) {
    if (!n)
        return 0;
    
    if (n == r->elem)
        return 1;
    
    if (r->elem > n)
        buscaTree(r->esq, n);
    else
        buscaTree(r->dir, n);
}

TreeNode* afunilamentoTree (TreeNode *r, int newR) {
    TreeNode *n = r, *p = NULL, *a = NULL;
    
    if (n == newR)
        return r;
   
    /* TODO: recursao que recebe o newR a partir da chamada recursiva e realiza
     * a rotacao conforme o pai e o avo */
    a = p;
    p = n;
    if (newR > n->elem)
        n = n->dir;
    else if (newR < n->elem)
        n = n->esq;
    }
}

void freeTree (TreeNode *p) {
    if (!p)
        return;
    
    freeTree(p->esq);
    freeTree(p->dir);
    
    free(p);
}

ListNode* createListNode(TreeNode *s, int order) {
    ListNode *p;
    
    p = malloc(sizeof (ListNode));
    p->size = 0;
    p->order = order;
    p->s = s;
    p->next = NULL;
    
    return p;
}

/* Remove o no posterior ao no "p" da lista */
ListNode* removeListNode (ListNode *p) {
    ListNode *t;
    
    t = p->next;
    p->next = t->next;
    
    return t;
}

void freeList (ListNode *p) {
    ListNode *t;
    
    while (p) {
        t = p;
        p = p->next;
        
        freeTree(t->s);
        free (t);
    }
}