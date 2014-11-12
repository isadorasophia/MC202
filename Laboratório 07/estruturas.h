#include <stdio.h>
#include <stdlib.h>

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