#define ROOT 0
typedef struct treeNode
{
    uint8_t elcode;
    struct treeNode *left;
    struct treeNode *right;
    struct treeNode *parent;
    struct treeNode **children;
    int childrenN;
    void *reference;
} treeNode;

treeNode *rootTreeNode()
{
    treeNode *t = malloc(sizeof(treeNode));
    t->children = malloc(sizeof(t));
    t->childrenN = 0;
    t->elcode = ROOT;
    t->left = NULL;
    t->right = NULL;
    t->reference = NULL;
}
treeNode *treeNodeNew(treeNode *parent, uint8_t elcode, void *reference)
{
    treeNode *t = malloc(sizeof(treeNode));
    t->elcode = elcode;
    t->reference = reference;
    parent->childrenN++;
    parent->children = realloc(parent->children, sizeof(t) * parent->childrenN);
    parent->children[parent->childrenN - 1] = t;
    if (parent->childrenN > 1)
    {
        t->left = parent->children[parent->childrenN - 2];
        parent->children[parent->childrenN - 2]->right = t;
    }
    else
    {

        t->left = NULL;
    }
    t->right = NULL;
    t->children = NULL;
    t->childrenN = 0;
    t->parent = parent;
}

treeNode *getTreeNodeAt(treeNode *treeNode, int index)
{
    if (treeNode->childrenN < index + 1 || index < 0)
    {
        return NULL;
    }
    return treeNode->children[index];
}

int destroyTreeNode(treeNode *treeNode)
{
    if (treeNode != NULL)
    {
        for (int i = 0; i < treeNode->childrenN; i++)
        {
            printf("\n%p",(void *) treeNode->children[i]);
            destroyTreeNode(treeNode->children[i]);
            printf("\n%p",(void *) treeNode->children[i]);
        }

        if (treeNode->reference != NULL)
        {
            free(treeNode->reference);
        }
        free(treeNode);
        treeNode = NULL;
    }
    return 0;
}

int printTreeNode(treeNode *treeNode, int recLevel)
{
    printf("\n");
    for (int s = 0; s < recLevel; s++)
    {
        printf("|");
    }
    if (treeNode == NULL)
    {
        printf("-Tree Node is deallocated\n");
        return 0;
    }
    printf("- Elcode: %d", treeNode->elcode);
    printf("\n");
    for (int s = 0; s < recLevel; s++)
    {
        printf("|");
    }
    printf("- Children: %d", treeNode->childrenN);
    printf("\n");
    for (int s = 0; s < recLevel; s++)
    {
        printf("|");
    }
    printf("- Referencing : %p", treeNode->reference);
    for (int i = 0; i < treeNode->childrenN; i++)
    {
        printf("\n");
        for (int s = 0; s < recLevel; s++)
        {
            printf("|");
        }
        if (treeNode->children != NULL)
            printTreeNode(treeNode->children[i], recLevel + 1);
    }
    return 0;
}