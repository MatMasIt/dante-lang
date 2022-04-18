#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define bool uint8_t
#define TRUE 1
#define FALSE 0
#include "syntaxtree.c"

int main()
{
    treeNode *p = rootTreeNode();
    treeNode *a = treeNodeNew(p, 1, 0);
    treeNode *b = treeNodeNew(a, 2, 0);
    treeNode *c = treeNodeNew(b, 3, 0);
    printTreeNode(p, 0);
    destroyTreeNode(p);
    printTreeNode(p, 0);
    return 0;
}