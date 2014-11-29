#include "arvore.h"

#define NO_PARENT 0
#define FAILED -1

/* Prototypes of functions that help to implement the library */
void setHeight(int A, Tree *florest, int size);
int findCommonAncestor (int A, int B, Tree *florest, int max);

/* Return N trees linked to a single vertex */
void setFlorest (Tree florest[], int size) {
    int i;
    
    for (i = 0; i < size; i++) {
        florest[i].parent = NO_PARENT;
        florest[i].height = 0;
    }
}

/* Set the correct height of the children of A */
void setHeight(int A, Tree *florest, int size) {
    int i;
    
    for (i = 0; i < size; i++) {
        if (florest[i].parent == A) {
            florest[i].height = florest[A].height + 1;
            setHeight(i, florest, size);
        }
    }
}

/* Link tree A to tree B */
void link (int A, int B, Tree *florest, int size) {
    florest[A].parent = B;
    florest[A].height = florest[B].height + 1;
    
    setHeight(A, florest, size);
}

/* Cut the link between A and its parent */
void cut (int A, Tree *florest, int size) {
    florest[A].parent = NO_PARENT;
    florest[A].height = 0;
    
    setHeight(A, florest, size);
}

/* Find the lowest common ancestor between A and B */
int lca (int A, int B, Tree *florest, int max) {   
    /* Study the current condition in order to return the lowest ancestor in
     * the most optimized way - if A is lower than B */
    if (florest[B].height < florest[A].height)
        return findCommonAncestor(A, B, florest, max);
    /* ...otherwise */
    else
        return findCommonAncestor(B, A, florest, max);
}

/* Find the common ancestor between A and B */
int findCommonAncestor (int A, int B, Tree *florest, int max) {
    /* Escaped the limits, or it won't find anyway */
    if (A <= 0 || B <= 0 || florest[B].height > florest[A].height) 
        return FAILED;
    /* Found */
    if (A == B)
        return A;
    
    /* Default is failed */
    int firstEntry = FAILED, secondEntry = FAILED;
   
    /* Way up to B! */
    firstEntry = findCommonAncestor (florest[A].parent, B, florest, max);

    printf("im testing");
    /* Way up to A! */
    secondEntry = findCommonAncestor (A, florest[B].parent, florest, max);

    /* If both entries are valid */
    if (secondEntry != FAILED && firstEntry != FAILED) {
        /* If the second entry is lower than the first one */
        if (florest[secondEntry].height > florest[firstEntry].height)
            return secondEntry;
        /* ...otherwise */
        else
            return firstEntry;
    }
    /* If only the second entry was valid */
    else if (secondEntry != FAILED)
        return secondEntry;
    /* Or if only the first one */
    else
        return firstEntry;
}