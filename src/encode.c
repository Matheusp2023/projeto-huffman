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
void printDictionary(char **dictionary){
    for(int i = 0;i < 256;i++){
        if(strcmp(dictionary[i],"") == 0) continue;
        printf("path:%c -> %s\n",i,dictionary[i]);
    }
}