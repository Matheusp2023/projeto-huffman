#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <encode.h>

#define MAX 100

int main() {
    FILE *archive;
    char file_path[MAX]; // Array que armazena o nome do arquivo
    int currentSize = 0;
    printf("Digite o caminho da pasta do arquivo: ");
    scanf("%s", file_path);
    // Lista encadeada para armazenar as frequencias em ordem crescente
    struct Node* list_frequency = createList();

    archive = fopen(file_path, "rb");
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
    
    unsigned char byte; // Variavel que armazenara cada bit temporariamente
    int frequency[256] = {0}; // Array que armazena a frequencia de cada byte

    // Le cada byte do arquivo 
    while (fread(&byte, sizeof(unsigned char), 1, archive) == 1)
    {
        frequency[byte]++;
    }

    // Inserir a frequencia de cada byte na lista encadeada ordenada
    insertionFrequency(&list_frequency, frequency,&currentSize);

    // Exibir a tabela de frequência
    printf("Tabela de Frequencia:\n");
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            printf("Byte 0x%02X: %d vezes\n", i, frequency[i]);
        }
    }
    printf("\nLista encadeada ordenada das frequencias:\n");
    printList(list_frequency);
    
    huffmanTree(&list_frequency,&currentSize);
    BitHuff bithuff,table[256];
    bithuff.bitH = 0;
    bithuff.size = 0;
    memset(table,0,sizeof(BitHuff) * 256);
    build_table(list_frequency,table,bithuff);
    //print(table,frequency);
    printf("%d\n",trashsize(frequency,table));
    printPreOrder(list_frequency);
    setFirstByte(archiveOut,trashsize(frequency,table),treeSize(list_frequency));
    setSecondByte(archiveOut,treeSize(list_frequency));
    setTree(archiveOut,list_frequency);
    fseek(archive, 0, SEEK_SET);
    printBytes(archive,archiveOut,table,trashsize(frequency,table));
    deleteList(list_frequency);
    fclose(archive);
    fclose(archiveOut);
    // Exibir a lista encadeada
    
    return 0;
}
