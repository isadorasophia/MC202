#include "estruturas.h"

#define NOT_FOUND -1

/* Prototipos de funcoes auxiliares para a biblioteca */
TreeNode *removeRoot (TreeNode *r);
int findNewRoot (TreeNode *r);

TreeNode* afunilamento (TreeNode *r, int newR);
TreeNode* RE (TreeNode *r);
TreeNode* RD (TreeNode *r);

#ifdef DEBUG
void preOrder (TreeNode *r) {
    if (r == NULL)
        return;
    
    printf("%d ", r->elem);
    preOrder(r->esq);
    preOrder(r->dir);
}
#endif

/* Retorna um no de arvore */
TreeNode* createTree (int n) {
    TreeNode *t;
    
    t = malloc(sizeof (TreeNode));
    t->elem = n;
    t->esq = NULL;
    t->dir = NULL;
    
    return t;
}

/* Insere, com afunilamento, um elemento "n" em uma arvore de busca */
TreeNode* insereTreeNode (TreeNode *r, int n) {
    TreeNode *p, *f = r, *new = createTree(n);
    
    /* Caso a arvore esteja vazia, retorna como raiz */
    if (!r)
        return new;
    
    /* Encontra o espaco mais adequado para alocao do novo no */
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
    
    /* Retorna o afunilamento da arvore em n */
    return afunilamento(r, n);
}

/* Remove, com afunilamento, um elemento "n" em uma arvore de busca */
TreeNode* removeTreeNode (TreeNode *r, int n) {
    TreeNode *p, *f = r;
    int found = 0, newR;
    
    /* Caso a arvore seja vazia */
    if (r == NULL)
        return r;
    
    /* Caso o elemento seja a raiz */
    if (r->elem == n) {
        newR = findNewRoot(r);
        r = removeRoot(r);

#ifdef DEBUG
        printf("Afunilando em %d: ", newR);
        preOrder(r);
#endif
        return afunilamento(r, newR);
    }
    
    /* Encontra o pai do no a ser removido */
    while (!found && f != NULL) {
        /* Caso tenha encontrado */
        if (n == f->elem) {
            found = 1;
        }
        /* Caso o elemento esteja a esquerda */
        else if (n < f->elem) {
            p = f;
            f = f->esq;
        }
        /* Ou a direita */
        else {
            p = f;
            f = f->dir;
        }
    }
    
    /* Caso o elemento exista na arvore, remove-o e encontra candidato
     * para o afunilamento */
    if (found) {
        /* Caso ele esteja a esquerda */
        if (n < p->elem) {
            p->esq = removeRoot(p->esq);
            newR = findNewRoot(p->esq);
        }
        /* Ou a direita */
        else {
            p->dir = removeRoot(p->dir);
            newR = findNewRoot(p->dir);
        }
    }
    
    /* Caso nao tenha encontrado o elemento ou candidatos filhos para
     * realizar o afunilamento */
    if (!found || newR == NOT_FOUND)
        newR = p->elem;
    
#ifdef DEBUG
    printf("Afunilando em %d: ", newR);
    preOrder(r);
#endif

    return afunilamento(r, newR);
}

/* Remove a raiz de uma arvore */
TreeNode *removeRoot (TreeNode *r) {
    TreeNode *p, *q;
    
    /* Caso nao haja filhos a esquerda, nova raiz sera a subarvore direita */
    if (r->esq == NULL)
        q = r->dir;
    
    /* Caso haja filho na esquerda, encontra predecessor para ser a nova raiz */
    else {
        p = r;
        q = r->esq;
        
        /* Encontra maior elemento "q" da subarvore, sendo "p" o seu pai */
        while (q->dir) {
            p = q;
            q = q->dir;
        }
        
        /* Caso a nova raiz nao seja o filho direto da raiz */
        if (p != r) {
            p->dir = q->esq;
            q->esq = r->esq;
        }
        
        q->dir = r->dir;
    }
    
    free(r);
    
    return q;
}

/* Retorna um candidato para realizar o afunilamento */
int findNewRoot (TreeNode *r) {
    TreeNode *p;
    
    /* Caso nao haja filhos, nao cabe a esta funcao determinar a nova raiz */
    if (r == NULL || (r->esq == NULL && r->dir == NULL))
        return NOT_FOUND;
    
    /* Caso nao haja subarvore esquerda, encontra o menor elemento 
     * da subarvore direita */
    if (r->esq == NULL) {
        r = r->dir;
        while (r != NULL) {
            p = r;
            r = r->esq;
        }
    }   
    /* Caso haja subarvore esquerda, encontra o seu maior elemento */
    else {
        r = r->esq;
        while (r != NULL) {
            p = r;
            r = r->dir;
        }
    }
    
    return p->elem;
}

/* Retorna se o elemento "n" existe na arvore */
int buscaTree (TreeNode *r, int n) {
    while (r && r->elem != n)
        if (r->elem > n)
            r = r->esq;
        else
            r = r->dir;
        
    if (r)
        return 1;
    else
        return 0;
}

/* Realiza o afunilamento com o elemento "newR" na arvore */
TreeNode* afunilamento (TreeNode *r, int newR) {
    TreeNode *a = r, *p = NULL, *n = NULL;
    
    /* Caso a raiz seja o proprio elemento ou a arvore esteja vazia */
    if (a == NULL || a->elem == newR)
        return a;
    /* Caso o elemento esteja a esquerda do avo */
    else if (newR < a->elem)
        p = a->esq;
    /* Ou a direita */
    else
        p = a->dir;

    /* Caso o elemento esteja a esquerda do pai */
    if (newR < p->elem) {
        /* Caso o filho ainda nao seja o elemento desejado, continua a
         * percorrer a arvore para encontra-lo */
        if (newR != p->esq->elem) {
            p->esq = afunilamento(p->esq, newR);
        }
        n = p->esq;
    }
    /* Ou a direita, realizando o procedimento analogo */
    else if (newR > p->elem) {
        if (newR != p->dir->elem) {
            p->dir = afunilamento(p->dir, newR);
        }
        n = p->dir;
    }
    /* Caso o pai seja o proprio elemento, finaliza */
    else {
        /* Caso esteja a esquerda do avo */
        if (newR < a->elem)
            return RD(a);
        /* Ou a direita */
        else
            return RE(a);
    }
    
    /* Encontrado o elemento no filho, executa caso esteja a esquerda do pai */
    if (n->elem < p->elem) {
        /* Caso esteja a esquerda do avo */
        if (p->elem < a->elem) {
            a = RD(a);
            return RD(a);
        }
        /* Caso esteja a direita do avo */
        else if (p->elem > a->elem) {
            a->dir = RD(p);
            return RE(a);
        }
    }
    /* Ou a direita do pai */ 
    else if (n->elem > p->elem) {
        /* Caso esteja a esquerda do avo */
        if (p->elem < a->elem) {
            a->esq = RE(p);
            return RD(a);
        }
        /* Caso esteja a direita do avo */
        else if (p->elem > a->elem) {
            a = RE(a);
            return RE(a);
        }
    }

    return NULL;
}

/* Rotaciona em "r" para a esquerda */
TreeNode* RE (TreeNode *r) {
    TreeNode *t = r->dir;
    
    if (!t) return r;
    
    r->dir = t->esq;
    t->esq = r;
    
    return t;
}

/* Rotaciona em "r" para a direita */
TreeNode* RD (TreeNode *r) {
    TreeNode *t = r->esq;
    
    if (!t) return r;
    
    r->esq = t->dir;
    t->dir = r;
    
    return t;
}

/* Libera a memoria de uma arvore */
void freeTree (TreeNode *r) {
    if (!r)
        return;
    
    freeTree(r->esq);
    freeTree(r->dir);
    
    free(r);
}

/* Retorna o no de uma lista ligada */
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

/* Libera a memoria de uma lista */
void freeList (ListNode *p) {
    ListNode *t;
    
    while (p) {
        t = p;
        p = p->next;
        
        freeTree(t->s);
        free (t);
    }
}