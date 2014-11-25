#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"

#define MAX_LENGHT 4

int main () {
    char[MAX_LENGHT] op;
    int N, M;
    Node *florest;
    
    scanf("%d %d", &N, &M);
    
    /* Create N trees linked to a single vertex */
    florest = createTrees(N);
    
    while (N--) {
        scanf("%s", op);
    }
    
    return 0;
}