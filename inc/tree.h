#include <list.h>

#ifndef TREE_H
#define TREE_H

/* fazer a árvore de huffman */
void huffmanTree(struct Node **list,int *currentSize);

// printar a árvore em pré ordem
void printPreOrder(struct Node *bt);

// Achar a profundida do nó mais profundo
int treeDeep(struct Node *huffTree);

bool isLeaf(struct Node *node);

#endif