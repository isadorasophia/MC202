#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvores.h"

#define MAX_LENGHT 4

int main () {
    char[MAX_LENGHT] operation;
    int N, M, a, b;
    Node *florest;
    
    scanf("%d %d", &N, &M);
    
    /* Create N trees linked to a single vertex */
    florest = initializeTrees(N);
    
    while (N--) {
        scanf("%s", operation);
        
        if (strcmp(operation, "lca") == 0) {
            scanf("%d %d", &a, &b);
            
            printf("%d\n", lca(a, b));
        }
        else if (strcmp(operation, "link") == 0) {
            scanf("%d %d", &a, &b)
            
            florest = link (a, b);
        }
        else if (strcmp(operation, "cut") == 0) {
            scanf("%d", &a)
            
            florest = cut (a);
        }
    }
    
    return 0;
}