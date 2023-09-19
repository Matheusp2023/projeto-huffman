#include <stdbool.h>

#ifndef TREE_H
#define TREE_H

struct Node {
    void *byte;
    int frequency;
    struct Node* next;
    struct Node* right;
    struct Node* left; 
};
struct Queue{
    int current_size;
    struct Node *head;
};

typedef struct Node Node;

typedef struct Queue Queue;

struct Queue *createQueue();

struct Node *createNode(void *byte,int frequency);

void *createVoidPointer(unsigned char byte);

unsigned char getByteFromVoidPointer(struct Node *byte);

void enqueue(struct Queue *queue,struct Node *newNode);

void insertionFrequency(struct Queue *queue, int frequency[]);

void printPreOrder(struct Node *bt);

void printTabelaFrequencia(int frequency[],struct Queue *queue);

void printFila(Queue *queue);

void huffmanTree(struct Queue *queue);

void freeMemory(struct Queue *queue);

#endif