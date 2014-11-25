#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *parent, *sibling, *child;
} Node;

link (int a, int b);
cut (int a, int b);
lca (int a, int b);