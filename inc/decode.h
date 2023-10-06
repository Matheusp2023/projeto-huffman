#include <list.h>
#include <tree.h>
#include <string.h>
#include <stdlib.h>

#ifndef DECODE_H
#define DEDODE_H
// Pega o tamanho do lixo no arquivo compactado
int trashSizeCompactFile(FILE *archive);
// Pega o tamanho da árvore no arquivo compactado
int treeSizeCompactFile(FILE *archive);
// pega a árvore do arquivo compactado
Node *getTree(FILE *archive,short int *treeSize);
// checa se o bit está setado nessa posição
int is_bit_i_set(unsigned char c, int i);
// seta os bytes no arquivo para descomprimir
void setBytesBack(FILE *fileIn,FILE *fileOut,short int trashSize,unsigned long long int sizeFile,Node *huffTree);

#endif