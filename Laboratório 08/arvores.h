#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *parent, *sibling, *child;
} Node;

Node *initializeTrees(int N);

link (int a, int b);
cut (int a, int b);
lca (int a, int b);