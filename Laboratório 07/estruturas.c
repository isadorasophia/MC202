#include "estruturas.h"

#define NOT_FOUND -1
#define DEBUG 1

TreeNode *removeRoot (TreeNode *r);
int findNewRoot (TreeNode *r);

TreeNode* afunilamento (TreeNode *r, int newR);
TreeNode* RE (TreeNode *r);
TreeNode* RD (TreeNode *r);

void preOrder (TreeNode *r) {
    if (r == NULL)
        return;
    
    printf("%d ", r->elem);
    preOrder(r->esq);
    preOrder(r->dir);
}

TreeNode* createTreeNode (int n) {
    TreeNode *t;
    
    t = malloc(sizeof (TreeNode));
    t->elem = n;
    t->esq = NULL;
    t->dir = NULL;
    
    return t;
}

TreeNode* insereTreeNode (TreeNode *r, int n) {
    TreeNode *p, *f = r, *new = createTreeNode(n);
    
    if (!r)
        return new;
    
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
    
#ifdef DEBUG
//    printf("Next step: removing the element %d\n", n);
//    preOrder(r);
#endif
    
    /* Caso o elemento seja a raiz */
    if (r->elem == n) {
#ifdef DEBUG
//        printf("I am the root\n", n);
#endif
//        if (r->esq == NULL && r->dir == NULL)
//            printf("ue\n");
        newR = findNewRoot(r);
        r = removeRoot(r);
//        printf("The new root is %d\n", newR);
        return afunilamento(r, newR);
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
#ifdef DEBUG
//         printf("Element %d found\n", n);
#endif
        if (n < p->elem) {
            p->esq = removeRoot(p->esq);
#ifdef DEBUG
//             printf("Removed\n", n);
//             preOrder(r);
#endif
            newR = findNewRoot(p->esq);
#ifdef DEBUG
//             printf("New root found: %d\n", newR);
#endif
        }
        else {
            p->dir = removeRoot(p->dir);
            newR = findNewRoot(p->dir);
        }
    }
    
    if (!found || newR == NOT_FOUND) {
#ifdef DEBUG
//         if (!found)
//             printf("I wasnt found\n", n);
#endif
        newR = p->elem;
    }

#ifdef DEBUG
//     printf("Element %d removed\n", n);
#endif
    
//     printf("new root is still %d\n", newR);
    return afunilamento(r, newR);
}

TreeNode *removeRoot (TreeNode *r) {
    TreeNode *p, *q;
    
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
    TreeNode *p;
    
    /* Caso nao haja filhos, nao cabe a esta funcao determinar a nova raiz */
    if (r == NULL || (r->esq == NULL && r->dir == NULL))
        return NOT_FOUND;
    
#ifdef DEBUG
//         printf("Finding the new root now...\n");
#endif

    
    /* Caso nao haja esquerda, encontra o menor elemento da subarvore direita */
    if (r->esq == NULL) {
        r = r->dir;
        while (r != NULL) {
            p = r;
            r = r->esq;
        }
    }   
    /* Caso haja apenas esquerda ou ambos, encontra o maior elemento da
     * esquerda */
    else {
        r = r->esq;
        while (r != NULL) {
            p = r;
            r = r->dir;
        }
    }
    
    return p->elem;
       
}

/* Retorna se o elemento buscado existe na arvore */
int buscaTree (TreeNode *r, int n) {
    if (!r)
        return 0;
    
    if (n == r->elem)
        return 1;
    
    if (r->elem > n)
        return buscaTree(r->esq, n);
    else
        return buscaTree(r->dir, n);
}

TreeNode* afunilamento (TreeNode *r, int newR) {
    TreeNode *a = r, *p = NULL, *n = NULL;
    
    /* Caso a raiz seja o próprio elemento ou esteja vazia */
    if (a == NULL || a->elem == newR)
        return a;
    else if (newR > a->elem)
        p = a->dir;
    else if (newR < a->elem)
        p = a->esq;

    if (newR > p->elem)
        n = p->dir;
    else if (newR < p->elem)
        n = p->esq;
    /* Caso o proprio pai seja o elemento, finaliza */
    else
        /* Caso esteja a esquerda do pai */
        if (newR < a->elem)
            return RD(a);
        /* Caso esteja a direita do pai */
        else if (newR > a->elem)
            return RE(a);
    
    /* Caso o filho nao seja o elemento desejado, continua a procura-lo */
    if (newR != n->elem) {
        n = afunilamento(p, newR);
        p = n;
        
        if (newR > a->elem) {
            a->dir = p;
        }
        else if (newR < a->elem) {
            a->esq = p;
        }
        
        if (p->elem != newR) {
            if (newR > p->elem)
                return p->dir;
            else
                return p->esq;
        }
//         printf("apos o afunilamento, o n vale %d, ", n->elem);
    }
    
//     printf("valor de n found: %d = %d\n", n->elem, newR);
    
    /* Encontrado o elemento, executa caso esteja a esquerda do pai */
    if (n->elem < p->elem) {
        /* Caso esteja a esquerda do avo */
        if (p->elem < a->elem) {
//             printf("vo %d e ", a->elem);
            a = RD(a);
//             printf("E-E: %d ", a->elem);
            return RD(a);
        }
        /* Caso esteja a direita do avo */
        else if (p->elem > a->elem) {
            a->dir = RD(p);
//             printf("E-D: %d ", a->elem);
            return RE(a);
        }
    }
    /* Caso esteja a direita do pai */ 
    else if (n->elem > p->elem) {
        /* Caso esteja a esquerda do avo */
        if (p->elem < a->elem) {
            a->esq = RE(p);
//             printf("D-E: %d ", a->elem);
            return RD(a);
        }
        /* Caso esteja a direita do avo */
        else if (p->elem > a->elem) {
            a = RE(a);
//             printf("D-D: %d ", a->elem);
            return RE(a);
        }
    }
    else if (n->elem == p->elem) {
        /* Caso esteja a esquerda do pai */
        if (newR < a->elem)
            return RD(a);
        /* Caso esteja a direita do pai */
        else if (newR > a->elem)
            return RE(a);
    }
    
    return NULL;
}

TreeNode* RE (TreeNode *r) {
    TreeNode *t = r->dir;
    
    if (!t) return r;
    
    r->dir = t->esq;
    t->esq = r;
    
    return t;
}

TreeNode* RD (TreeNode *r) {
    TreeNode *t = r->esq;
    
    if (!t) return r;
    
    r->esq = t->dir;
    t->dir = r;
    
    return t;
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
//     printf("*********************removo o S%d\n", t->order);
    
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