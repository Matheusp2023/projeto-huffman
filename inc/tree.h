#include <list.h>

#ifndef TREE_H
#define TREE_H

/**
 * @brief Constroi a árvore de huffman com a Lista ordenada
 * 
 * @param list: Um ponteiro que aponta para a lista 
 * @param currentSize: Tamanho atual da lista
 */
void huffmanTree(struct Node **list,int *currentSize);

/**
 * @brief Checa se é uma folha ou não 
 * 
 * @param node: Um Nó de Huffman
 * @return Se é uma folha retorna verdadeiro caso contrário retorna falso
 */
bool isLeaf(struct Node *node);

/**
 * @brief Pega o Tamanho da árvore de Huffman
 * 
 * @param huffTree: o Nó raiz da árvore de Huffman 
 * @return O tamanho da árvore de Huffman em inteiro
 */
int treeSize(struct Node *huffTree);

#endif