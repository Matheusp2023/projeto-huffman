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

struct Node* createList();

bool isEmpty(struct Node** list);

struct Node *createNode(void *byte,int frequency);

void *createVoidPointer(unsigned char byte);

unsigned char getByteFromVoidPointer(struct Node *byte);

unsigned char remove_first(struct Node **list, int *currentSize); 

void addInOrder(struct Node **list,struct Node *newNode,int *currentSize);

void insertionFrequency(struct Node** list, int frequency[],int *CurrentSize);

void printList(struct Node* list);

void deleteList(struct Node* list);

#endif