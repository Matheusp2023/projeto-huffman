#include <stdbool.h>

#ifndef LIST_H
#define LIST_H

struct Node {
    void *byte;
    int frequency;
    struct Node* next;
    struct Node *left;
    struct Node *right;
};

typedef struct Node Node;

// Criar uma lista que aponta para NULL
struct Node* createList();
// Checar se a lista está vazia
bool isEmpty(struct Node** list);
// Criar um nó de huffman
struct Node *createNode(void *byte,int frequency);
void getFrequency(FILE *fileIn,int frequency[]);
// Alocar memória para um ponteiro para void
void *createVoidPointer(unsigned char byte);
// Pegar o conteudo de um ponteiro pra void
unsigned char getByteFromVoidPointer(struct Node *byte);
// Remover o primeiro elemento da lista
unsigned char removeFirst(struct Node **list, int *currentSize); 
// Adicionar um elemento em ordem com basena frequencia
void addInOrder(struct Node **list,struct Node *newNode,int *currentSize);
// Inserir a frequencia dos itens
void insertionFrequency(struct Node** list, int frequency[],int *CurrentSize);
// Printar a lista encadeada
void printList(struct Node* list);
// Libera a memória da lista
void deleteList(struct Node* list);

#endif