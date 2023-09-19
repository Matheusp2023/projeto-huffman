#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../inc/tree.h"

#define MAX 100

int main()
{
    FILE *archive;
    char file_path[MAX]; // Array que armazena o nome do arquivo
    printf("Digite o caminho da pasta do arquivo: ");
    scanf("%s", file_path);

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
    //criação de uma fila de prioridade
    struct Queue *queue = createQueue();
    // Inserção da frequência dos elementos
    insertionFrequency(queue, frequency);
    
    printTabelaFrequencia(frequency,queue);
    
    // Fecha o arquivo
    fclose(archive);

    // Exibir a lista encadeada
    printFila(queue);
    printf("\n");
    huffmanTree(queue);
    printf("\nArvore de Huffman:\n");
    print_pre_order(queue->head);
    //Liberar a memoria
    freeMemory(queue);
    return 0;
}
