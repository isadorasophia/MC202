#include "arvore.h"

#define NO_PARENT 0
#define FAILED -1

/* Prototypes of functions that help to implement the library */
void setHeight(int A, Tree *florest, int size);

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
int lca (int A, int B, Tree *florest) {   
    /* Check who is the lower one, and goes up until they reach the same
     * height */
    while (florest[A].height > florest[B].height)
        A = florest[A].parent;
    while (florest[A].height < florest[B].height)
        B = florest[B].parent;
    
    /* Now that they have the same height - just run until find the
     * common ancestor */
    while (A != B) {
        A = florest[A].parent;
        B = florest[B].parent;
    }
    
    return A;
}