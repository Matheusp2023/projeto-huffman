#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <encode.h>

char **createDictionary(int nBits){
    char **dictionary;
    dictionary = malloc(sizeof(char*) * 256);
    for(int i = 0; i < 256; i++){
        dictionary[i] = calloc(nBits,sizeof(char));
    }
    return dictionary;
}
void generateDicionationary(char **dictionary,struct Node *huffmanTree,char *path,int nBits){
    char left[nBits + 1],right[nBits + 1];
    if(isLeaf(huffmanTree)){
        strcpy(dictionary[getByteFromVoidPointer(huffmanTree->byte)],path);
    }
    else{
        strcpy(left,path);
        strcpy(right,path);
        strcat(left,"0");
        strcat(right,"1");
        generateDicionationary(dictionary,huffmanTree->left,left,nBits);
        generateDicionationary(dictionary,huffmanTree->right,right,nBits);
    }
}
int trashsize(char **dictionary,int frequency[]){
    int totalBits = 0;
    for(int i = 0;i < 256;i++){
        if(strcmp(dictionary[i],"") == 0) continue;
        totalBits += frequency[i] * strlen(dictionary[i]);
    }
    int trash = (8 - (totalBits % 8));
    return trash;
}
void printDictionary(char **dictionary){
    for(int i = 0;i < 256;i++){
        if(strcmp(dictionary[i],"") == 0) continue;
        printf("path:%c -> %s\n",i,dictionary[i]);
    }
}
void setFirstByte(FILE *file,int trashSize,int treeSize){
    unsigned char byte_completo = 0x00;
    byte_completo = byte_completo | (trashSize << 5);
    byte_completo = byte_completo | (treeSize >> 8);
    fwrite(&byte_completo,sizeof(unsigned char),1,file);
}
void setSecondByte(FILE *file,int treesize){
    unsigned char byte_completo = 0x00;
    byte_completo = byte_completo | treesize;
    fwrite(&byte_completo,sizeof(unsigned char),1,file);
}
void setTree(FILE *file,struct Node *bt)
{
    if (bt != NULL) {
    unsigned char x = getByteFromVoidPointer(bt->byte);
    fwrite(&x,sizeof(unsigned char),1,file);
    setTree(file,bt->left);
    setTree(file,bt->right);
    }
}
void printBytes(FILE *fileIn,FILE *fileOut,char **dictionary,int treeDeep){
    fseek(fileIn, 0, SEEK_SET);
    unsigned char byte;
    unsigned char byte_completo = 0x00;
    char caractere[treeDeep];
    int move = 8;
    int rest = 0;
    memset(caractere,0,sizeof(caractere));
    while (fread(&byte, sizeof(unsigned char), 1, fileIn) == 1)
    {         
        strcat(caractere,dictionary[byte]);    
        move -= strlen(caractere);
        if(move > 0) byte_completo = byte_completo | (1 << move);
        else if(move == 0){
            for (int bit = 7; bit >= 0; bit--) {    // Lê cada bit do byte
            int valor_bit = (byte >> bit) & 1;
            printf("%d", valor_bit);
        }
        }
        else{
            rest = -move;
            byte_completo = byte_completo | (1 >> rest);
            
        }
        }
        memset(caractere,0,sizeof(caractere));
}
    
