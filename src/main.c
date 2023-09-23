#include <stdio.h>
#include <list.h>
#include <tree.h>

#define MAX 100

int main() {
    FILE *archive;
    char file_path[MAX]; // Array que armazena o nome do arquivo
    int currentSize = 0;
    printf("Digite o caminho da pasta do arquivo: ");
    scanf("%s", file_path);

    // Lista encadeada para armazenar as frequencias em ordem crescente
    struct Node* list_frequency = createList();

    // Abre o arquivo para leitura
    archive = fopen(file_path, "rb");

    // Caso de erro na leitura do arquivo
    if (archive == NULL)
    {
        perror("Erro ao abrir o arquivo");
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
    
    // Fecha o arquivo
    fclose(archive);


    // Exibir a lista encadeada
    printf("\nLista encadeada ordenada das frequencias:\n");
    printList(list_frequency);
    
    huffmanTree(&list_frequency,&currentSize);
    printPreOrder(list_frequency);
    // Liberar a memoria
    deleteList(list_frequency);
    
    return 0;
}