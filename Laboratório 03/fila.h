#include <stdio.h>
#include <stdlib.h>

// Armazena a informacao de cada celula da entrada
typedef struct {
    int altura; int i; int j; char rotulo;
} Celula;

// Dado o algoritmo do lda, havera um vetor (do tipo FilaOrdenada) responsavel
// por apontar listas (do tipo No) de acordo com o seu nivel de prioridade 
typedef struct No {
    Celula n; struct No *next;
} No;

typedef struct FilaOrdenada {
    No *s; No *t;
} FilaOrdenada;

// Implementa as funcoes basicas de FIFO
void RemFila (No **s, No **t);
void InsFila (Celula n, No **s, No **t);
int FilaVazia (No *s);

// Funcoes especificas para a funcionalidade da fila ordenada
int FilaOrdenadaVazia(FilaOrdenada filaOrdenada[], int n);
void IniciaFilaOrdenada(FilaOrdenada filaOrdenada[], int n);