#include "arvores.h"

#define NOT_FOUND -1

Node *createNode(int n);

/* Return N trees linked to a single vertex */
Node *initializeTrees(int N) {
    int i;
    Node *node, *root;
    
    /* Initialize the first node */
    node = createNode(1);
    
    root = node;
    
    /* Then initialize all of its siblings */
    for (i = 2; i <= N; i++) {
        node->sibling = createNode(i);
        
        node = node->sibling;
    }
    
    return root;
}

/* Create a node which all its pointers are set to NULL, 
 * and the key setted to "n" */
Node *createNode(int n) {
    Node *aux;
    
    aux = malloc(sizeof(Node));
    aux->key = n;
    aux->parent = NULL;
    aux->sibling = NULL;
    
    return aux;
}

link (int A, int B, Node *florest) {
    Node *nodeA, *nodeB;
    Node *rootB, *s = NULL, *p;
    
    nodeB = find(B, florest, &s);
    
    /* Find the root of B */
    rootB = B;
    p = rootB->parent;

    while (p) {
        rootB = p;
        p = rootB->parent;
    }

    /* Now procedes to find A */
    s = NULL;
    
    nodeA = find(A, rootB->sibling, &s);
    
    /* Make the tree still, being able to move node A */
    /* If there is a sibling before A */
    if (s)
        s->sibling = nodeA->sibling;
    /* If A doesn't have any sibling */
    else if (nodeA->parent)
        nodeA->parent->child = nodeA->sibling;
    /* It A doens't have any sibling or a parent */
    else
        florest = nodeA->sibling;
    
    nodeA->sibling = NULL;
    
    /* Finally, makes A a child of B */
    p = nodeB->child;
    s = NULL;
    while (p) {
        s = p;
        p = p->sibling;
    }
    /* If B doesn't have any child, A is a direct child */
    if (!s)
        nodeB->child = nodeA;
    /* If B already have child, make A a sibling */
    else
        s->sibling = nodeA;
    
    nodeA->parent = nodeB;
    
    return florest;
}

Node *find (int x, Node *tree, **s) {
    if (!tree)
        return NULL;
    if (tree->key == x)
        return tree;
    
    Node *found;
    
    found = find(x, tree->child, s);
    
    if (found)
        return found;
    
    if (tree->sibling && tree->sibling->key == x)
        *s = tree;
    
    found = find(x, tree->sibling, s);
    
    return found;
}

Node *cut (int a, *florest) {
    Node *s, *nodeA, *parentS;
    
    nodeA = find(A, florest, &s);
    
    if (s) {
        s->sibling = nodeA->sibling;
    }
    else if (nodeA->parent) {
        nodeA->parent->child = nodeA->sibling;
    }
    /* It was already on top of the vertex */
    else
        return florest;

    nodeA->sibling = NULL;
    
    parentS = nodeA->parent;
    
    while (parentS) {
        nodeA->parent = parentS;
        parentS = parentS->sibling;
    }
    
    parentS->sibling = nodeA;
    nodeA->parent = parentS->parent;
    
    return florest;
}


int lca (int A, int B, Node* florest) {
    Node *nodeA, *nodeB, *s = NULL;
    int ancestor;
    
    nodeA = find(A, florest, &s);
    
    nodeB = find(B, florest, &s);

    ancestor = findAncestor(nodeA, nodeB);
    
    return ancestor;
}

/* Find the ancestor assuming that B is upper than A */
int findAncestor (Node *parentA, Node *parentB) {
    if (!parentA || !parentB)
        return NOT_FOUND;
    if (parentA == parentB)
        return parentA->key;
    
    int ancestor;
    
    ancestor = findAncestor (parentA->parent, parentB);
    
    if (ancestor == NOT_FOUND)
        ancestor = findAncestor(parentA, parentB->parent);
            
    return ancestor;
}