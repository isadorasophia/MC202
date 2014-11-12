#include "estruturas.h"

TreeNode* createTreeNode (int n) {
    TreeNode *t;
    
    t->elem = n;
    t->esq = NULL;
    t->dir = NULL;
    
    return t;
}

TreeNode* insereTree (TreeNode *r, int n) {
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

TreeNode* removeTree (TreeNode *r, int n) {

}

TreeNode* buscaTree (TreeNode *r, int n) {
    
}

TreeNode* afunilamentoTree (TreeNode *r, int n) {
    
}

ListNode* createListNode(TreeNode *s, int order) {
    
}