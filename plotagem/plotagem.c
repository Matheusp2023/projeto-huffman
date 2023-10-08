#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura do nó da lista
struct Node_l {
    int data;
    struct Node_l* next;
};

// Definição da estrutura do nó da árvore
struct Node_t {
    int data;
    struct Node_t* left;
    struct Node_t* right;
};

struct Node_t* criarNoArvore(int valor);

void inserirNoInicioLista(struct Node_l** head, int valor);

struct Node_t* inserirArvore(struct Node_t* root, int valor);

void buscarElementoLista(struct Node_l* head, int valor, int *contador);

void buscarElementoArvore(struct Node_t* root, int valor, int *contator);

int generate_random(int lower, int upper);

int main() {

    srand(time(NULL));

    FILE* output_list = fopen("output_list.txt", "w");
    FILE* output_tree = fopen("output_tree.txt", "w");

    int lower = 1;
    int upper = 100000;
    
    for (int n = 0; n <= 100000; n += 100)
    {
        struct Node_l* head = NULL;
        struct Node_t* root = NULL;

        for (int i = 0; i < n; i++)
        {
            int num = generate_random(lower, upper);

            inserirNoInicioLista(&head, num);

            root = inserirArvore(root, num);
        }
        
        int target = generate_random(lower, upper);

        int lista_iteracao = 0;
        int arvore_iteracao = 0;

        buscarElementoLista(head, target, &lista_iteracao);
        buscarElementoArvore(root, target, &arvore_iteracao);

        fprintf(output_list, "%d\t%d\n", n, lista_iteracao);
        fprintf(output_tree, "%d\t%d\n", n, arvore_iteracao);
    }

    fclose(output_list);
    fclose(output_tree);
    
    return 0;
}

// Função para criar um novo nó da arvore de busca binaria
struct Node_t* criarNoArvore(int valor) {
    struct Node_t* novoNo = (struct Node_t*)malloc(sizeof(struct Node_t));
    if (novoNo == NULL) {
        perror("Erro: Falha na alocação de memória");
        exit(EXIT_FAILURE);
    }
    novoNo->data = valor;
    novoNo->left = NULL;
    novoNo->right = NULL;
    return novoNo;
}

// Função para inserir um elemento no início da lista
void inserirNoInicioLista(struct Node_l** head, int valor) {
    // Aloca memória para um novo nó
    struct Node_l* novoNo = (struct Node_l*)malloc(sizeof(struct Node_l));
    
    // Verifica se a alocação de memória foi bem-sucedida
    if (novoNo == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        return;
    }
    
    // Define o valor do novo nó
    novoNo->data = valor;
    
    // Define o próximo nó como o atual cabeçalho da lista
    novoNo->next = *head;
    
    // Atualiza o cabeçalho da lista para apontar para o novo nó
    *head = novoNo;
}

struct Node_t* inserirArvore(struct Node_t* root, int valor) {
    // Se a árvore estiver vazia, retorna um novo nó
    if (root == NULL) {
        return criarNoArvore(valor);
    }
    
    // Caso contrário, percorre a árvore de forma recursiva
    if (valor < root->data) {
        root->left = inserirArvore(root->left, valor);
    } else if (valor > root->data) {
        root->right = inserirArvore(root->right, valor);
    }
    
    // Retorna o ponteiro para a raiz da árvore (não modificada)
    return root;
}

// Função para buscar um elemento na lista
void buscarElementoLista(struct Node_l* head, int valor, int *contador) {
    struct Node_l* current = head;

    // Percorre a lista até encontrar o elemento ou chegar ao final da lista
    while (current != NULL) {

        (*contador)++;

        if (current->data == valor) {
            return; // Elemento encontrado, retorna o nó atual
        }
        current = current->next;
    }
}

// Função para buscar um elemento em uma árvore de busca binária
void buscarElementoArvore(struct Node_t* root, int valor, int *contator) {
    if (root == NULL) {
        return;
    }

    (*contator)++;

    if (root->data == valor)
    {
        return;
    }
    
    // Se o valor for menor que a raiz, busca na subárvore esquerda
    if (valor < root->data) {
        buscarElementoArvore(root->left, valor, contator);
    }
    
    // Se o valor for maior que a raiz, busca na subárvore direita
    buscarElementoArvore(root->right, valor, contator);
}

int generate_random(int lower, int upper) {

    int num = rand() % (upper - lower + 1); /* Gera um número aleatório no intervalo [lower, upper] */
    return num;
}