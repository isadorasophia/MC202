/* Biblioteca responsavel por implementar funcoes de lista ligada */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    false = 0,
    true = 1
} Bool;

/* No com especificacoes voltadas a aplicacao do disco */
typedef struct No {
    char name[11];
    long int size;
    long int sizeNotLocated;
    Bool ocupado;
    struct No *next;
} No;

/* Insere o no "p" apos o no recebido */
void addNext (No *no, No *p);

/* Remove o no posterior a "p" */
void removeNext (No *no);

/* Retorna o no com o nome correspondente, NULL caso nao exista */
No *findNo (char nome[], No *t);

/* Libera a memoria da lista */
void freeList (No *no);