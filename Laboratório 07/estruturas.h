#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TreeNode {
    int elem;
    struct TreeNode *esq, *dir;
} TreeNode;

typedef struct ListNode {
    int size;
    int order;
    TreeNode *s;
    struct ListNode *next;
} ListNode;

void preOrder (TreeNode *r);

TreeNode* createTreeNode (int n);
TreeNode* insereTreeNode (TreeNode *r, int n);
TreeNode* removeTreeNode (TreeNode *r, int n);
int buscaTree (TreeNode *r, int n);
void freeTree (TreeNode *p);

ListNode* createListNode(TreeNode *s, int order);
ListNode* removeListNode (ListNode *p);
void freeList (ListNode *p);