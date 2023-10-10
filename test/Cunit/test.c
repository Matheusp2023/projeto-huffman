#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <encode.h>
#include <decode.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#define MAX 100

int init_suite(void) {
    return 0;
}

int clean_suite(void) { 
    return 0; 
}

void test_create_list(){
    struct Node* list_f = createList();
    CU_ASSERT_EQUAL(list_f, createList());
    free(list_f);
}

void test_isEmpty(){
    struct Node* list_f = createList();
    CU_ASSERT_EQUAL(isEmpty(&list_f), true);
}

void test_getFrequency(){
    FILE *archive;
    archive = fopen("test/input/test_1.txt", "rb");
    if(archive == NULL){
        printf("Erro ao abrir o arquivo\n");
    }
    int frequency[256] = {0}; 
    getFrequency(archive, frequency);
    int i = 0;
    while(i < 256){
        if(frequency[i] == 0){
          i++;
        }
        else{
            break;
        }
    }
    CU_ASSERT_NOT_EQUAL(i, 255);
}

void test_insertionFrequency() {
    struct Node* list = createList();
    int frequency[256] = {0};
    FILE *archive;
    archive = fopen("test/input/test_1.txt", "rb");
    getFrequency(archive, frequency);


    int currentSize = 0;
    insertionFrequency(&list, frequency, &currentSize);
    
    CU_ASSERT_EQUAL(frequency[32], 3);

    // Limpe a lista após os testes (implemente a função de limpeza, se necessário)
    while (list != NULL) {
        struct Node *temp = list;
        list = list->next;
        free(temp);
    }
}

void test_createNode(void) {
    void *byte = (void *)malloc(sizeof(unsigned char)); // Aloca memória para um byte
    unsigned char testValue = 'A'; // Valor de teste
    *((unsigned char *)byte) = testValue; // Atribui o valor de teste ao byte

    int frequency = 10; // Frequência de teste

    struct Node *newNode = createNode(byte, frequency);

    // Realizando as asserções para verificar se a função funcionou como esperado
    CU_ASSERT(newNode != NULL);
    CU_ASSERT(newNode->next == NULL);
    CU_ASSERT(newNode->left == NULL);
    CU_ASSERT(newNode->right == NULL);
    CU_ASSERT(newNode->byte != NULL);
    CU_ASSERT(*((unsigned char *)newNode->byte) == testValue);
    CU_ASSERT(newNode->frequency == frequency);

    // Liberando a memória alocada para o byte e o nó
    free(byte);
    free(newNode);
}

void test_createVoidPointer(void) {
    unsigned char testValue = 'A'; // Valor de teste

    void *result = createVoidPointer(testValue);

    // Realizando as asserções para verificar se a função funcionou como esperado
    CU_ASSERT(result != NULL);
    CU_ASSERT(*((unsigned char *)result) == testValue);

    // Liberando a memória alocada para o resultado
    free(result);
}

void test_addInOrder(void) {
    struct Node *list = NULL;
    int currentSize = 0;

    // Teste 1: Inserindo um elemento em uma lista vazia
    struct Node *newNode1 = createNode(createVoidPointer('A'), 10);
    addInOrder(&list, newNode1, &currentSize);
    CU_ASSERT(list != NULL);
    CU_ASSERT(list->frequency == 10);
    CU_ASSERT(currentSize == 1);

    // Teste 2: Inserindo um elemento no início da lista
    struct Node *newNode2 = createNode(createVoidPointer('B'), 5);
    addInOrder(&list, newNode2, &currentSize);
    CU_ASSERT(list->frequency == 5);
    CU_ASSERT(list->next->frequency == 10);
    CU_ASSERT(currentSize == 2);

    // Limpe a lista após os testes
    while (list != NULL) {
        struct Node *temp = list;
        list = list->next;
        free(temp);
    }
}

void test_getByteFromVoidPointer(void) {
    unsigned char testValue = 'A'; // Valor de teste

    // Criando um ponteiro void com o valor de teste
    void *bytePointer = createVoidPointer(testValue);

    // Atribuindo o byte usando a função getByteFromVoidPointer
    unsigned char result = getByteFromVoidPointer(bytePointer);

    // Realizando as asserções para verificar se a função funcionou como esperado
    CU_ASSERT(result == testValue);

    // Liberando a memória alocada para o bytePointer
    free(bytePointer);
}

void test_removeFirst(void) {
    struct Node *list = NULL;
    int currentSize = 0;

    // Adicione alguns nós à lista para teste
    struct Node *node1 = createNode(createVoidPointer('A'), 10);
    struct Node *node2 = createNode(createVoidPointer('B'), 5);
    struct Node *node3 = createNode(createVoidPointer('C'), 15);

    list = node1;
    node1->next = node2;
    node2->next = node3;
    currentSize = 3;

    // Remova o primeiro nó da lista e verifique se o valor removido é 'A'
    unsigned char result = removeFirst(&list, &currentSize);
    CU_ASSERT(result == 'A');
    CU_ASSERT(currentSize == 2);

    // Verifique se a lista foi atualizada corretamente após a remoção
    CU_ASSERT(list == node2);

    // Libere a memória alocada para os nós
    free(node1->byte);
    free(node1);
    free(node2->byte);
    free(node2);
    free(node3->byte);
    free(node3);
}

void test_isLeaf(void) {
    // Crie alguns nós para teste
    struct Node *leafNode = createNode(createVoidPointer('A'), 10);
    struct Node *nonLeafNode = createNode(createVoidPointer('B'), 5);

    // Verifique se o nó folha é realmente uma folha
    CU_ASSERT(isLeaf(leafNode) == true);

    // Libere a memória alocada para os nós
    free(leafNode->byte);
    free(leafNode);
}

void freeHuffmanTree(struct Node *root) {
    if (root == NULL) {
        return;
    }

    // Recursivamente libera a memória da subárvore esquerda
    freeHuffmanTree(root->left);

    // Recursivamente libera a memória da subárvore direita
    freeHuffmanTree(root->right);

    // Libera a memória do byte (ponteiro void)
    free(root->byte);

    // Libera o nó atual
    free(root);
}

void test_huffmanTree(void) {
    struct Node *list = NULL;
    int currentSize = 0;

    // Crie alguns nós para teste
    struct Node *node1 = createNode(createVoidPointer('A'), 10);
    struct Node *node2 = createNode(createVoidPointer('B'), 5);
    struct Node *node3 = createNode(createVoidPointer('C'), 15);

    // Adicione os nós à lista de teste
    addInOrder(&list, node1, &currentSize);
    addInOrder(&list, node2, &currentSize);
    addInOrder(&list, node3, &currentSize);

    // Chame a função huffmanTree para construir a árvore de Huffman
    huffmanTree(&list, &currentSize);

    // Realize as asserções para verificar se a função funcionou como esperado
    CU_ASSERT(list != NULL); // Deve haver um único nó na lista, que é a árvore de Huffman
    CU_ASSERT(currentSize == 1); // O tamanho da lista deve ser 1 após a construção da árvore

    // Libere a memória alocada para os nós
    free(node1->byte);
    free(node1);
    free(node2->byte);
    free(node2);
    free(node3->byte);
    free(node3);

}

void cleanHuffmanTree(struct Node **list) {
    while (*list != NULL) {
        struct Node *temp = *list;
        *list = (*list)->next;
        free(temp);
    }
}

void test_treeSize(void) {
    struct Node *list = NULL;
    int currentSize = 0;
    int frequency[256] = {0};

    // Crie uma árvore de Huffman de teste
    frequency[0] = 42;
    frequency[3] = 22;
    frequency[9] = 12;
    frequency[4] = 13;


    insertionFrequency(&list, frequency, &currentSize);

    huffmanTree(&list, &currentSize);

    //Checar se a árvore de huffman foi construída
    CU_ASSERT_PTR_NULL(list->next);

    // Chame a função treeSize para calcular o tamanho da árvore
    int size = treeSize(list);

    // Realize as asserções para verificar se a função funcionou como esperado
    CU_ASSERT(size == 7); // O tamanho egitsperado da árvore é 6

    
    // Libere a memória alocada para os nós
    cleanHuffmanTree(&list);
    
    // Certifique-se de que a árvore foi liberada corretamente
    CU_ASSERT_PTR_NULL(list);
}
int main(){
    CU_pSuite pSuite = NULL;
    if(CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    pSuite = CU_add_suite("Basic_Test", init_suite, clean_suite);
    if(pSuite == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if(CU_add_test(pSuite, "Testing List Creation ...", test_create_list) == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if(CU_add_test(pSuite, "Testing isEmpty() Function ...", test_isEmpty) == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if(CU_add_test(pSuite,"Testing getFrequency() Function ...", test_getFrequency) == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Testing insertionFrequency() Function ...", test_insertionFrequency)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Testing createNode structure ...", test_createNode)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Testing createVoidPointer() Function", test_createVoidPointer)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Teste addInOrder() Function...", test_addInOrder)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Teste getByteFromVoidPointer() Function...", test_getByteFromVoidPointer)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Teste removeFirst() Function...", test_removeFirst)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Teste isLeaf() Function...", test_isLeaf)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Teste huffmanTree() Function...", test_huffmanTree)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Teste treeSize() Function...", test_treeSize)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}