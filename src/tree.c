#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <stdbool.h>


bool isLeaf(struct Node *node){
    return node->left == NULL && node->right == NULL;
}
/*
    monta a árvore de huffman com a lista ordenada
*/
void huffmanTree(struct Node **list,int *currentSize){
    while(*currentSize > 1){
        int frequency = (*list)->frequency + (*list)->next->frequency;// soma das frequências dos primeiros nós
        struct Node *newNode = createNode(createVoidPointer('*'),frequency);
        newNode->left = *list;// esquerda do novo nó vai receber o primeiro elemento
        removeFirst(list,currentSize);
        newNode->right = (*list);//direita do novo nó vai receber o segundo elemento
        removeFirst(list,currentSize);
        addInOrder(list,newNode,currentSize);// adiciona o novo nó de maneira ordenada
    }
    return;
}
/*
    acha o tamanho da árvore 
*/
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
