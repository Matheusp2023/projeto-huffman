#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <decode.h>

int is_bit_i_set(unsigned char c, int i){
    unsigned char mask = 1 << i;
    return mask & c;
}
/*
    pega o tamanho do lixo que está nos 3 bits mais significativos 
    do arquivo compactado
*/
int trashSizeCompactFile(FILE *archive){

    //lendo primeiro byte do arquivo
    unsigned char byte;
    fread(&byte,sizeof(unsigned char),1,archive);

    //empurra 5 bits menos significativos para fora
    short int trash = byte >> 5;
    fseek(archive, 0, SEEK_SET);
    return trash;
}

/*
    pega o tamanho da árvore que está nos 5 bits menos significativos do primeiro
    byte e nos 8 bits do segundo byte
*/
int treeSizeCompactFile(FILE *archive){
    unsigned char byte;
    fread(&byte,sizeof(unsigned char),1,archive);

    //considerando apenas 5 ultimos bits
    byte = byte << 3;
    byte = byte >> 3;
    short int treeSize = byte;
    treeSize = treeSize << 8;
    fread(&byte,sizeof(unsigned char),1,archive);
    treeSize = treeSize | byte;
    return treeSize;
}

/*
    Percorrendo Arvore de Huffman e monta ela sabendo que está em pré ordem
*/
Node *getTree(FILE *archive,short int *treeSize){
    unsigned char byte;
    Node *huffTree = NULL;

    //tratando caractere especial (sempre folha)
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

        //se for um nó intermediario
        if(byte == '*'){
            //busca primeiro na esquerda até acha uma folha
            huffTree->left = getTree(archive,treeSize);
            huffTree->right = getTree(archive,treeSize);
        }
        return huffTree;      
    }
    return huffTree;
}

/*
    Preencher arquivo descompactado
*/
void setBytesBack(FILE *fileIn,FILE *fileOut,short int trashSize,unsigned long long int sizeFile,Node *huffTree){

    //byte que está sendo manipulado
    unsigned char byte;

    //arvore de huffman
    Node *aux = huffTree;

    //definir até onde ler do byte
    int limit = 0;

    //não considera o header do arquivo
    for(int i = 0;i < sizeFile;i++){

        //tratamento de lixo no ultimo byte
        if(i == (sizeFile - 1)) limit = trashSize;
        fread(&byte,sizeof(unsigned char),1,fileIn);    
        for(int j = 7;j >= limit;j--){

            //se estiver setado vai para direita
            //se não estiver setado vai para esquerda
            if(is_bit_i_set(byte,j)){
                aux = aux->right;             
            }
            else{
                aux = aux->left;
            }

            // quando acha folha imprime no arquivo
            if(isLeaf(aux)){
                unsigned char caractere = getByteFromVoidPointer(aux->byte);
                fwrite(&caractere,sizeof(unsigned char),1,fileOut);
                aux = huffTree;
            }
        }
    }
}
