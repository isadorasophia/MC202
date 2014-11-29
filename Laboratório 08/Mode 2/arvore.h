/* Library responsible for implementing functions related to florest of trees */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Basic structure of a tree */
typedef struct Tree {
    int parent;
    int height;
} Tree;

/* Return N trees linked to a single vertex */
void setFlorest (Tree *florest, int size);

/* Link tree A to tree B */
void link (int A, int B, Tree *florest, int size);

/* Cut the link between A and its parent */
void cut (int A, Tree *florest, int size);

/* Find the lowest common ancestor between A and B */
int lca (int A, int B, Tree *florest);