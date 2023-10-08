#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <stdbool.h>


bool isLeaf(struct Node *node){
    return node->left == NULL && node->right == NULL;
}

void huffmanTree(struct Node **list,int *currentSize){
    while(*currentSize > 1){
        int frequency = (*list)->frequency + (*list)->next->frequency;
        struct Node *newNode = createNode(createVoidPointer('*'),frequency);
        newNode->left = *list;
        removeFirst(list,currentSize);
        newNode->right = (*list);
        removeFirst(list,currentSize);
        addInOrder(list,newNode,currentSize);
    }
    return;
}

int treeSize(struct Node *huffTree){
    if(huffTree == NULL){
        return 0;
    }
    else{
        int left = treeSize(huffTree->left);
        int right = treeSize(huffTree->right);
        unsigned char x = getByteFromVoidPointer(huffTree->byte);
        if(((x == '*') || (x == '\\')) && isLeaf(huffTree)){
        return 2 + left + right;
    }
        return 1 + left + right;
    }
}
