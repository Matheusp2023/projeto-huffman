#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <stdbool.h>


bool isLeaf(struct Node *node){
    return node->left == NULL && node->right == NULL;
}
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
int treeDeep(struct Node *huffTree){
    if(huffTree == NULL){
        return 0;
    }
    else{
        int left = 1 + treeDeep(huffTree->left);
        int right = 1 + treeDeep(huffTree->right);
        if(left > right) return left;
        else return right;
    }
}
int treeSize(struct Node *huffTree){
    if(huffTree == NULL){
        return 0;
    }
    else{
        int left = treeSize(huffTree->left);
        int right = treeSize(huffTree->right);
        return 1 + left + right;
    }
}