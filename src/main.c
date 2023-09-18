#include <stdio.h>
#include <stdlib.h>

#define MAX 100

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
    
    // Exibir a tabela de frequência
    printf("Tabela de Frequencia:\n");
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
        {
            printf("Byte 0x%02X: %d vezes\n", i, frequency[i]);
            queue->current_size++;
        }
    }
    
    // Fecha o arquivo
    fclose(archive);

    // Exibir a lista encadeada
    printf("\nLista encadeada ordenada das frequencias:\n");
    struct Node* current = queue->head;
    while (current != NULL)
    {
        printf("[%c, %d] -> ", getByteFromVoidPointer(current->byte), current->frequency);
        current = current->next;
    }
    //Liberar a memoria
    struct Node* previour;
    huffmanTree(queue);
    print_pre_order(queue->head);
    while (queue->head != NULL)
    {
        previour = queue->head;
        queue->head = queue->head->next;
        free(previour);
    }
    return 0;
}
