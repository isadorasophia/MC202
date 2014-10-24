#include <stdio.h>
#include <stdlib.h>

struct No {
    int n; 
    int freq; 
    struct No *next;
};

typedef struct No No;

No *createList (int N);
void addNo (No *no, int n, int N);
void removeLista (No *no);

void MTF (No *fichario, int *req, int R, int N);
void TR (No *fichario, int *req, int R, int N);
void FC (No *fichario, int *req, int R, int N);

No *findReq(int n, int *custo, No *p);

void insertAfter (int n, int freq, No *p);
void deleteNext (No *p);
void swapValues (No *no);
void ordenaFreq (No *head, No *found);