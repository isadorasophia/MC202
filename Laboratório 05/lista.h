#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Biblioteca responsavel por implementar funcoes de lista ligada
typedef enum {
    false = 0,
    true = 1
} Bool;

// No com especificacoes voltadas a aplicacao do programa
typedef struct No {
    char nome[11];
    long int size;
    Bool ocupado = true;
    struct No *next;
} No;

// Insere o no "p" na lista
void addNo (No *no, No *p);

// Remove o proximo no
void removeNo (No *no);

// Retorna o no anterior ao que possui o nome correspondente, 
// NULL caso nao exista
No *findNo (char[] nome, No *t);

// Libera a memoria da lista
void freeList (No *no);