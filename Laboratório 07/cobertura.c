#include "cobertura.h"

int castInt (char a) {
    return a - 48;
}

TreeNode* leConjunto (int order) {
    char elemChar;
    ListNode *S;
    
    scanf("%c", elemChar);
    
    S = createListNode(createTreeNode(castInt(elemChar)), order);
    
    while (elemChar != 's') {
        insereTree(S->s, castInt(elemChar));
        
        scanf ("%c", elemChar);
    }
    
    return S;
}