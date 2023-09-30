#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <encode.h>


int is_bit_i_set(unsigned char c, int i)
{
unsigned char mask = 1 << i;
return mask & c;
}
char **createDictionary(int nBits){
    char **dictionary;
    dictionary = malloc(sizeof(char*) * 256);
    for(int i = 0; i < 256; i++){
        dictionary[i] = calloc(nBits,sizeof(char));
    }
    return dictionary;
}
void generateDicionationary(char **dictionary,struct Node *huffmanTree,char *path,int nBits){
    char left[nBits + 15],right[nBits + 15];
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
    long long int totalBits = 0;
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
    if(((x == '*') || (x == '\\')) && isLeaf(bt)){
        unsigned char y = '\\';
        fwrite(&y,sizeof(unsigned char),1,file);
    }
    fwrite(&x,sizeof(unsigned char),1,file);
    setTree(file,bt->left);
    setTree(file,bt->right);
    }
}
void printBytes(FILE *fileIn,FILE *fileOut,char **dictionary,int treeDeep){
    fseek(fileIn, 0, SEEK_SET);
    unsigned char byte;
    unsigned char byte_completo = 0x00;
    char caractere[3000] = "";
    char rest[3000] = "";
    int set = 8;
    int i,j = 0;
    while (fread(&byte, sizeof(unsigned char), 1, fileIn) == 1)
    {        
        strcat(caractere,rest);
        memset(rest, '\0', sizeof(rest));
        if(set > 0){
            strcat(caractere,dictionary[byte]); 
            set = 8 - strlen(caractere);
        } 
        if(set <= 0){
            set = -set;
            int k = 0;   
            j = 0; 
            while(j < set){
                
                rest[j] = caractere[8 + j];
                j++;          
            }         
            for(i = 0;i <= 7;i++){
            if(caractere[i] == '1'){
                byte_completo = byte_completo | (1 << (7 - i));
            } 
            }
            memset(caractere, '\0', sizeof(caractere));
            fwrite(&byte_completo,sizeof(unsigned char),1,fileOut); 
            byte_completo = 0x00;
            set = 8;
        }              
    }
    if(strlen(caractere)){
        byte_completo = 0x00;
        for(i = 0;i <= 7;i++){
            if(caractere[i] == '1'){
                byte_completo = byte_completo | (1 << (7 - i));
            } 
        }
        fwrite(&byte_completo,sizeof(unsigned char),1,fileOut);
    }
    if(strlen(rest)){
        byte_completo = 0x00;
        for(i = 0;i <= 7;i++){
            if(rest[i] == '1'){
                byte_completo = byte_completo | (1 << (7 - i));
            } 
        }
        fwrite(&byte_completo,sizeof(unsigned char),1,fileOut);
    }
}