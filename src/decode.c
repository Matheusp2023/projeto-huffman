#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <decode.h>

int is_bit_i_set(unsigned char c, int i){
    unsigned char mask = 1 << i;
    return mask & c;
}
int trashSizeCompactFile(FILE *archive){
    unsigned char byte;
    fread(&byte,sizeof(unsigned char),1,archive);
    short int trash = byte >> 5;
    fseek(archive, 0, SEEK_SET);
    return trash;
}
int treeSizeCompactFile(FILE *archive){
    unsigned char byte;
    fread(&byte,sizeof(unsigned char),1,archive);
    byte = byte << 3;
    byte = byte >> 3;
    short int treeSize = byte;
    treeSize = treeSize << 8;
    fread(&byte,sizeof(unsigned char),1,archive);
    treeSize = treeSize | byte;
    return treeSize;
}
Node *getTree(FILE *archive,short int *treeSize){
    unsigned char byte;
    Node *huffTree = NULL;
    if(*treeSize > 0){
        fread(&byte,sizeof(unsigned char),1,archive);
        if(byte == '\\'){
            (*treeSize)--;
            fread(&byte,sizeof(unsigned char),1,archive);
            huffTree = createNode(createVoidPointer(byte),0);
            (*treeSize)--;
            return huffTree;
        }
        huffTree = createNode(createVoidPointer(byte),0);
        (*treeSize)--;
        if(byte == '*'){
            huffTree->left = getTree(archive,treeSize);
            huffTree->right = getTree(archive,treeSize);
        }
        return huffTree;      
    }
    return huffTree;
}
void setBytesBack(FILE *fileIn,FILE *fileOut,short int trashSize,unsigned long long int sizeFile,Node *huffTree){
    unsigned char byte;
    Node *aux = huffTree;
    int limit = 0;
    for(int i = 0;i < sizeFile;i++){
        if(i == (sizeFile - 1)) limit = trashSize;
        fread(&byte,sizeof(unsigned char),1,fileIn);    
        for(int j = 7;j >= limit;j--){
            if(is_bit_i_set(byte,j)){
                aux = aux->right;             
            }
            else{
                aux = aux->left;
            }
            if(isLeaf(aux)){
                unsigned char caractere = getByteFromVoidPointer(aux->byte);
                fwrite(&caractere,sizeof(unsigned char),1,fileOut);
                aux = huffTree;
            }
        }
    }
}
