#include "fila.h"

// Insere um elemento a fila
void InsFila (Celula n, No **s, No **t) {
    No *aux;
    
    aux = malloc(sizeof (No));
    aux->n = n;
    aux->next = NULL;
    
    if (*s == NULL) {
        *t = aux;
        *s = *t;
    }
    else {
        (*t)->next = aux;
        *t = aux;
    }
}

// Remove um elemento da fila
void RemFila (No **s, No **t) {
    No *aux;
    
    aux = *s;
    *s = aux->next;
    
    free(aux);
    
    if (*s == NULL) *t = NULL;
}

// Verifica se a lista em "s" esta vazia
int FilaVazia (No *s) {
    return (s == NULL);
}

// Verifica se a fila ordenada de "n" elementos esta vazia
int FilaOrdenadaVazia(FilaOrdenada filaOrdenada[], int n) {
    int i;
    
    for (i = 0; i < n; i++) {
        if (!FilaVazia(filaOrdenada[i].s))
            return 0;
    }
    
    return 1;
}

//Inicia as listas da lista ordenada
void IniciaFilaOrdenada(FilaOrdenada filaOrdenada[], int n) {
    int i;
    
    for (i = 0; i < n; i++) {
        filaOrdenada[i].s = NULL;
        filaOrdenada[i].t = NULL;
    }
}