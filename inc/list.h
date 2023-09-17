#include <stdbool.h>

#ifndef LIST_H
#define LIST_H

struct Node {
    void *byte;
    int frequency;
    struct Node* next;
};

typedef struct Node Node;

struct Node* createList();

bool isEmpaty(struct Node** list);

void *createVoidPointer(unsigned char byte);

unsigned char getByteFromVoidPointer(struct Node *byte);

void insertionFrequency(struct Node** list, int frequency[]);

void printList(struct Node* list);

void deleteList(struct Node* list);

#endif