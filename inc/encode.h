#include <list.h>
#include <tree.h>
#include <string.h>
#include <stdlib.h>

#ifndef ENCODE_H
#define ENDODE_H

char **createDictionary(int nBits);

void generateDicionationary(char **dictionary,struct Node *huffmanTree,char *path,int nBits);

void printDictionary(char **dictionary);


#endif