#include <list.h>
#include <tree.h>
#include <string.h>
#include <stdlib.h>

#ifndef ENCODE_H
#define ENDODE_H
// Alocar memória para um dicionário
char **createDictionary(int nBits);
// Criar os novos bits que vão representar os caracteres
void generateDicionationary(char **dictionary,struct Node *huffmanTree,char *path,int nBits);
// printar o dicionário
void printDictionary(char **dictionary);
// Achar o tamanho do lixo
int trashsize(char **dictionary,int frequency[]);

void setFirstByte(FILE *file,int trashSize,int treeSize);

void setSecondByte(FILE *file,int treesize);

void setTree(FILE *file,struct Node *bt);

void printBytes(FILE *fileIn,FILE *fileOut,char **dictionary,int treeDeep);

#endif