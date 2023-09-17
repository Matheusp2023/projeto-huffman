#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <list.h>

// Criar lista encadeada vazia
struct Node* createList() {
    return NULL;
}

// Verificar se list esta vazia
bool isEmpaty(struct Node** list) {
    return (*list == NULL);
}

void *createVoidPointer(unsigned char byte) {
    unsigned char *pointer = malloc(sizeof(unsigned char*));
    *pointer = byte;
    return (void*) pointer;
}

unsigned char getByteFromVoidPointer(struct Node *byte) {
    unsigned char *item = (unsigned char*) byte;
    return *item;
}

/* OBJETIVO: Inserir na lista encadeada lista a frequencia e o byte
             de forma ordenada na ordem crescente. */
void insertionFrequency(struct Node** list, int frequency[]) {
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            // Criar no
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->byte = createVoidPointer(i);
            newNode->frequency = frequency[i];
            newNode->next = NULL;

            // Se a lista estiver vazia ou o elemento for o de menor frequência aqui ocorre a inserção
            if (isEmpaty(list) || frequency[i] < (*list)->frequency)
            {
                newNode->next = *list;
                *list = newNode;
            }
            // Aqui é para caso a inserção não ocorra no inicio
            else
            {
                struct Node* current = *list;
                while (current->next != NULL && frequency[i] >= current->next->frequency)
                {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }
}

void printList(struct Node* list) {
    struct Node* current = list;
    while (current != NULL)
    {
        printf("[%c, %d] -> ", getByteFromVoidPointer(current->byte), current->frequency);
        current = current->next;
    }
}

void deleteList(struct Node* list) {
    struct Node* previour;
    while (list != NULL)
    {
        previour = list;
        list = list->next;
        free(previour);
    }
}