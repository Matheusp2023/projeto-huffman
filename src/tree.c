#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../inc/tree.h"

/* OBJETIVO: Criação de uma fila(uma ponteiro que vai apontar para o primeiro 
        nó da lista ordenada e ter um tamanho que inicialmente é 0)*/ 
struct Queue *createQueue(){
    struct Queue *New_queue = malloc(sizeof(struct Queue));
    New_queue->head = NULL;
    New_queue->current_size = 0;
    return New_queue;
}
// OBJETIVO: Criação de um nó de Huffman
struct Node *createNode(void *byte,int frequency){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->byte = byte;
    newNode->frequency = frequency;
    return newNode;
}
// OBJETIVO: Cria um ponteiro para void
void *createVoidPointer(unsigned char byte){
    unsigned char *pointer = malloc(sizeof(unsigned char*));
    *pointer = byte;
    return (void*) pointer;
}
// OBJETIVO: Pega o conteudo de de um ponteiro para void
unsigned char getByteFromVoidPointer(struct Node *byte){
    unsigned char *item = (unsigned char*) byte;
    return *item;
}
// OBJETIVO: Exibir a tabela de frequência
void printTabelaFrequencia(int frequency[],struct Queue *queue){
    printf("Tabela de Frequencia:\n");
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            printf("Byte 0x%02X: %d vezes\n", i, frequency[i]);
            queue->current_size++;
        }
    }
}
// OBJETIVO: Exibir a fila ordenada
void printFila(Queue *queue){
    printf("\nfila ordenada das frequencias:\n");
    struct Node* current = queue->head;
    while (current != NULL)
    {
        printf("[%c, %d] -> ", getByteFromVoidPointer(current->byte), current->frequency);
        current = current->next;
    }
}
// OBJETIVO: Liberar memória da fila ordenada
void freeMemory(struct Queue *queue){
    struct Node* previour;
    while (queue->head != NULL)
    {
        previour = queue->head;
        queue->head = queue->head->next;
        free(previour);
    }
}
// OBJETIVO: Função para adicionar um nó na fila de maneira ordenada com base na frequencia
void enqueue(struct Queue *queue,struct Node *newNode){
    if (queue->head == NULL || newNode->frequency <= queue->head->frequency){
        newNode->next = queue->head;
        queue->head = newNode;
    }
    // Aqui é para caso a inserção não ocorra no inicio
    else{
        struct Node* current = queue->head;
        while (current->next != NULL && newNode->frequency > current->next->frequency){
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
/* OBJETIVO: Inserir na lista encadeada lista a frequencia e o byte
             de forma ordenada na ordem crescente.*/
void insertionFrequency(struct Queue *queue, int frequency[])
{
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            struct Node* newNode = createNode(createVoidPointer(i), frequency[i]);
            enqueue(queue, newNode);
        }
    }
}
// * OBJETIVO: Imprimir a árvore de huffmann em pré_ordem
void print_pre_order(struct Node *bt)
{
    if (bt != NULL) {
    printf("%c", getByteFromVoidPointer(bt->byte));
    print_pre_order(bt->left);
    print_pre_order(bt->right);
    }
}
// * OBJETIVO: Construir a árvore de huffman 
void huffmanTree(struct Queue *queue){
    while(queue->current_size != 1){
        int frequency = queue->head->frequency + queue->head->next->frequency;
        struct Node *newNode = createNode(createVoidPointer('*'),frequency);
        newNode->left = queue->head;
        queue->head = queue->head->next;
        newNode->right = queue->head;
        queue->head = queue->head->next;
        queue->current_size--;
        enqueue(queue,newNode);
    }
}