#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <encode.h>
#include <decode.h>

#define MAX 100

int main() {
    int i;
    printf("SEJA BEM VINDO A CODIFICAÇÃO DE HUFFMAN\n");
    printf("SELECIONE UMA DAS OPÇÕES A SEGUIR:\n");
    printf("1 - COMPACTAR ARQUIVO\n");
    printf("2 - DESCOMPACTAR ARQUIVO\n");
    printf("OPÇÃO: ");
    scanf("%d",&i);
    if(i == 1){
        FILE *archive;
        char file_path[MAX]; // Array que armazena o nome do arquivo
        int currentSize = 0;
        printf("Digite o caminho da pasta do arquivo: ");
        scanf("%s", file_path);
        // Lista encadeada para armazenar as frequencias em ordem crescente
        struct Node* list_frequency = createList();
        archive = fopen(file_path, "rb");
        unsigned long long int size1 = sizeArchive(archive);
        strcat(file_path,".huff");
        // Abre o arquivo para leitura
        FILE *archiveOut = fopen(file_path,"wb");
        if (archiveOut == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return 1;
        }
        // Caso de erro na leitura do arquivo
        if (archive == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return 1;
        } 
        int frequency[256] = {0};
        getFrequency(archive,frequency);
        insertionFrequency(&list_frequency, frequency,&currentSize);
        huffmanTree(&list_frequency,&currentSize);
        BitHuff bithuff,table[256];
        bithuff.bitH = 0;
        bithuff.size = 0;
        memset(table,0,sizeof(BitHuff) * 256);
        buildTable(list_frequency,table,bithuff);
        setFirstByte(archiveOut,trashsize(frequency,table),treeSize(list_frequency));
        setSecondByte(archiveOut,treeSize(list_frequency));
        setTree(archiveOut,list_frequency);
        fseek(archive, 0, SEEK_SET);
        setBytes(archive,archiveOut,table,trashsize(frequency,table));
        unsigned long long int size2 = sizeArchive(archiveOut);
        deleteList(list_frequency);
        fclose(archive);
        fclose(archiveOut);
        printf("TAMANHO DO ARQUIVO ORIGINAL EM BYTES: %llu\n",size1);
        printf("TAMANHO DO ARQUIVO COMPACTADO EM BYTES: %llu\n",size2);
        if(size1 > size2){
            printf("A COMPRESSÃO SE DEMONSTROU EFICIENTE\n");
        }
        else{
            printf("A COMPRESSÃO SE DEMONSTROU INEFICIENTE\n");
        }
    }
    else if(i == 2){
        FILE *archive;
        FILE *archiveOut;
        char file_path[MAX];
        printf("Digite o caminho da pasta do arquivo: ");
        scanf("%s", file_path);
        archive = fopen(file_path, "rb");
        char *remove = strrchr(file_path,'.');
        if(remove != NULL) *remove = '\0';
        archiveOut = fopen(file_path, "wb");
        short int trash = trashSizeCompactFile(archive);
        short int treeSize = treeSizeCompactFile(archive);
        unsigned long long int archiveSize = sizeArchive(archive);
        archiveSize -= 2;
        archiveSize -= treeSize;
        Node *huffTree = getTree(archive,&treeSize);
        setBytesBack(archive,archiveOut,trash,archiveSize,huffTree);
        fclose(archive);
        fclose(archiveOut);
    }
    
    return 0;
}
