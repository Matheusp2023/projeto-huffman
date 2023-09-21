#include <stdio.h>
#include <list.h>
#include <tree.h>

void printPreOrder(struct Node *bt)
{
    if (bt != NULL) {
    printf("%c", getByteFromVoidPointer(bt->byte));
    printPreOrder(bt->left);
    printPreOrder(bt->right);
    }
}
void huffmanTree(struct Node **list,int *currentSize){
    while(*currentSize > 1){
        int frequency = (*list)->frequency + (*list)->next->frequency;
        struct Node *newNode = createNode(createVoidPointer('*'),frequency);
        newNode->left = *list;
        remove_first(list,currentSize);
        newNode->right = (*list);
        remove_first(list,currentSize);
        addInOrder(list,newNode,currentSize);
    }
    return;
}