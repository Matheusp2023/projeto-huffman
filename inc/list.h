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

/**
 * @brief Inicializa uma lista encadeada retornando um ponteiro para NULL
 * 
 * @return Retorna um ponteiro do tipo struct Node para NULL 
 */
struct Node* createList();
/**
 * @brief checa se a lista está vazia
 * 
 * @param list: Um ponteiro que aponta para a lista 
 * @return Verdadeiro ou Falso 
 */
bool isEmpty(struct Node** list);
/**
 * @brief Cria um nó de Huffman
 * 
 * @param byte: Um ponteiro para void que contém o caractere 
 * @param frequency: A frequência do caractere
 * @return retorna um nó do tipo struct node 
 */
struct Node *createNode(void *byte,int frequency);
/**
 * @brief Pega a frequência de um todos os caracteres
 * 
 * @param fileIn: O arquivo que iremos compactar 
 * @param frequency: A tabela de frequência dos caracteres que inicialmente é 0 para todos
 */
void getFrequency(FILE *fileIn,int frequency[]);
/**
 * @brief Cria um ponteiro Para Void para colocar no nó de huffman
 * 
 * @param byte: um unsigned char qualquer
 * @return retorna um ponteiro Para Void com o caractere que desejamos 
 */
void *createVoidPointer(unsigned char byte);
/**
 * @brief Pega o conteudo do ponteiro para void como um unsigned char
 * 
 * @param byte Um nó de huffman que tem o ponteiro para void
 * @return um unsigned char que estava no ponteiro para void
 */
unsigned char getByteFromVoidPointer(struct Node *byte);
/**
 * @brief Remove o primeiro item da lista ordenada
 * 
 * @param list: Um ponteiro que aponta para a lista
 * @param currentSize: Tamanho atual da lista
 * @return um unsigned char que representa o caractere do primeiro nó
 */
unsigned char removeFirst(struct Node **list, int *currentSize); 
/**
 * @brief Adiciona o nó de Huffman de maneira ordenada
 * 
 * @param  list: Um ponteiro que aponta para a lista
 * @param newNode: Um nó criado que vai ser adicionado na Lista
 * @param currentSize: Tamanho atual da lista
 */
void addInOrder(struct Node **list,struct Node *newNode,int *currentSize);
/**
 * @brief Cria os nós de huffman para cada caractere com suas respectivas frequências
 * 
 * @param list: Um ponteiro que aponta para a lista
 * @param frequency: Uma tabela com a frequência de cada caractere
 * @param CurrentSize: Tamanho Atual da Lista
 */
void insertionFrequency(struct Node** list, int frequency[],int *CurrentSize);

#endif