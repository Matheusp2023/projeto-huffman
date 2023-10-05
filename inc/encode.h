#include <list.h>
#include <tree.h>
#include <string.h>
#include <stdlib.h>

#ifndef ENCODE_H
#define ENDODE_H

typedef struct bithuff{
    int bitH;
    int size;
}BitHuff;
// Pega o tamanho do arquivo
unsigned long long int sizeArchive(FILE *archive);
// Construir a tabelo dos bits de Huffman
void buildTable(Node* tree_node,BitHuff table[],BitHuff code);
// Achar o tamanho do lixo
int trashsize(int frequency[],BitHuff table[]);
// Setar o primeiro byte que contém o tamanho do lixo e o começo do tamanho da árvore
void setFirstByte(FILE *file,int trashSize,int treeSize);
// Setar o segundo byte que contém o restante do tamanho da árvore
void setSecondByte(FILE *file,int treesize);
// Setar a árvore de huffman
void setTree(FILE *file,struct Node *bt);
// Setar os bytes com os novos bits correspondentes de cada caractere
void setBytes(FILE *fileIn,FILE *fileOut,BitHuff table[],int trashSize);

#endif
