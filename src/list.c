#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <list.h>

// Criar lista encadeada vazia
struct Node* createList() {
    return NULL;
}
struct Node *createNode(void *byte,int frequency){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->byte = byte;
    newNode->frequency = frequency;
    return newNode;
}
// Verificar se list esta vazia
bool isEmpty(struct Node** list) {
    return (*list == NULL);
}

void *createVoidPointer(unsigned char byte) {
    unsigned char *pointer = malloc(sizeof(unsigned char*));
    *pointer = byte;
    return (void*) pointer;
}
void addInOrder(struct Node **list,struct Node *newNode,int *currentSize){
    if (*list == NULL || newNode->frequency <= (*list)->frequency){
        newNode->next = *list;
        *list = newNode;
    }
    // Aqui é para caso a inserção não ocorra no inicio
    else{
        struct Node* current = *list;
        while (current->next != NULL && newNode->frequency > current->next->frequency){
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    (*currentSize)++;
    return;
}
unsigned char getByteFromVoidPointer(struct Node *byte) {
    unsigned char *item = (unsigned char*) byte;
    return *item;
}

/* OBJETIVO: Inserir na lista encadeada lista a frequencia e o byte
             de forma ordenada na ordem crescente. */
void insertionFrequency(struct Node** list, int frequency[],int *CurrentSize) {
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            struct Node* newNode = createNode(createVoidPointer(i), frequency[i]);
            addInOrder(list,newNode,CurrentSize);
        }
    }
}
unsigned char remove_first(struct Node **list, int *currentSize){
    unsigned char item = getByteFromVoidPointer((*list)->byte); 
    (*list) = (*list)->next;
    (*currentSize)--;
    return item;
}

// Exibir a lista encadeada
void printList(struct Node* list) {
    struct Node* current = list;
    while (current != NULL)
    {
        printf("[%c, %d] -> ", getByteFromVoidPointer(current->byte), current->frequency);
        current = current->next;
    }
}

// Liberar a memoria destruindo a lista encadeada
void deleteList(struct Node* list) {
    struct Node* previour;
    while (list != NULL)
    {
        previour = list;
        list = list->next;
        free(previour);
    }
}