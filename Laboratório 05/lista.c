#include "lista.h"

/* Insere o no "p" ao fim da lista */
void addNo (No *no, No *p) {
    while (no->next != NULL)
        no = no->next;
    
    no->next = p;
}

/* Remove o proximo no */
void removeNext (No *p) {
    No *q;
    
    q = p->next;
    p->next = p->next->next;
    free (q);
}

/* Retorna o no com o nome correspondente, NULL caso nao exista */
No *findNo (char nome[], No *t) {
    No *p = t->next;
    
    while (p != NULL && strcmp(p->name, nome) != 0)
        p = p->next;

    return p;
}

/* Libera a memoria da lista */
void freeList (No *t) {
    No *p;
    
    while (t != NULL) {
        p = t->next;
        free(t);
        t = p;
    }
}