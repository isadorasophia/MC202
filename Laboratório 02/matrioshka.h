#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    long int n; long int containDir; struct No *next;
} No;

int AnalisaSequencia(int n);
int IsMatrioshka (No *t, long int a);

No* IniciaPilha();
void FreePilha (No *t);

void Push (No *t, long int a);
void Pop (No *t);

long int Topo (No *t);
int PilhaVazia (No *t);