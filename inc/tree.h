#include <list.h>

#ifndef TREE_H
#define TREE_H

/* Fazer a árvore de huffman */
void huffmanTree(struct Node **list,int *currentSize);

// Printar a árvore em pré ordem
void printPreOrder(struct Node *bt);

// Achar a profundida do nó mais profundo
int treeDeep(struct Node *huffTree);

// Checar se o nó é uma folha
bool isLeaf(struct Node *node);

// Obter o tamanho da árvore
int treeSize(struct Node *huffTree);

#endif