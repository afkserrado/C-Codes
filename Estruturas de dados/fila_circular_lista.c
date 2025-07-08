#include <stdio.h>
#include <stdlib.h>

// Fila circular com lista simplesmente ligada circular

// Define a estrutura de um nó lista
typedef struct node {
    int chave;
    struct node *prox;
} node;

// Cria a estrutura de uma fila baseada em lista
typedef struct estFila {
    node *inicio;
    node *fim;
} estFila;

// Cria e inicializa um novo nó, configurando seus ponteiros para NULL
node *init_node (int chave) {
    node *novo = malloc(sizeof(node)); // Aloca memória para o nó

    // Falha de alocação de memória
    if (novo == NULL) {
        printf("Erro ao alocar memória para o nó.\n");
        return NULL;
    }

    novo->chave = chave;
    novo->prox = NULL;
    return novo;
}

// Cria e inicializa uma fila
estFila *init_fila () {
    estFila *fila = malloc(sizeof(estFila)); // Aloca memória para a fila

    // Falha de alocação de memória
    if (fila == NULL) {
        printf("Falha ao alocar memória para a estrutura da fila.\n");
        return NULL;
    }

    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

// Enfileirar: inserir elementos na fila
void enqueue (estFila *fila, node *novo) {

    // Falha de alocação para a fila ou fila inexistente
    if (fila == NULL) {
        printf("Não há memória alocada para a estrutura da fila.\n");
        return;
    }

    // Falha de alocação para o nó
    if (novo == NULL) {
        printf("Não há memória alocada para o novo nó.\n");
        return;
    }

    // Fila vazia
    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
        novo->prox = novo; // Fecha o círculo
        return;
    }

    // Fila não vazia
    fila->fim->prox = novo; // Fim atual aponta para o novo
    novo->prox = fila->inicio; // Novo aponta para o início atual da fila
    fila->fim = novo; // Fim recebe o novo
}

// Desinfileirar: retirar elementos da fila
void dequeue (estFila *fila) {

    // Falha de alocação para a fila ou fila inexistente
    if (fila == NULL) {
        printf("Não há memória alocada para a estrutura da fila.\n");
        return;
    }

    // Fila vazia
    if (fila->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    node *temp = fila->inicio; // Guarda o início da fila

    // Fila com elemento único
    if (fila->inicio == fila->fim) {
        fila->inicio = NULL;
        fila->fim = NULL;
    }

    // Fila com mais de um elemento
    else {
        fila->fim->prox = fila->inicio->prox;
        fila->inicio = fila->inicio->prox; // Atualiza o início da fila
    }

    free(temp);
}

// Exibe os elementos da fila
void imprimirFila (estFila *fila) {

    // Falha de alocação para a fila ou fila inexistente
    if (fila == NULL) {
        printf("Não há memória alocada para a estrutura da fila.\n");
        return;
    }

    // Fila vazia
    if (fila->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    node *x = fila->inicio; // Guarda o início dafila

    // Percorre a fila
    do {
        if (x != fila->inicio) {printf(" ");}
        printf("%d", x->chave);
        x = x->prox;
    } while (x != fila->inicio);
    printf("\n");
}

// Libera a memória da fila e dos nós da lista
void liberarFila (estFila *fila) {

    // Falha de alocação para a fila ou fila inexistente
    if (fila == NULL) {
        printf("Não há memória alocada para a estrutura da fila.\n");
        return;
    }

    // Fila existente, mas vazia
    if (fila->inicio == NULL) {
        free(fila);
        return;
    }

    node *x = fila->inicio; // Guarda o início da fila

    // Percorre a fila, liberando os nós da lista
    do {
        node *temp = x;
        x = x->prox;
        free(temp);
    } while (x != fila->inicio);

    // Libera a estrutura da fila
    free(fila);
}

int main() {

    // Inicializa a fila
    estFila *fila = init_fila();

    dequeue(fila); // Fila vazia

    enqueue(fila, init_node(10));
    enqueue(fila, init_node(20));
    enqueue(fila, init_node(30));
    imprimirFila(fila); // 10 20 30

    dequeue(fila);
    imprimirFila(fila); // 20 30

    enqueue(fila, init_node(40));
    imprimirFila(fila); // 20 30 40

    enqueue(fila, init_node(50)); // Insere 50
    imprimirFila(fila); // 20 30 40 50

    dequeue(fila);
    dequeue(fila);
    dequeue(fila);
    imprimirFila(fila); // 50

    dequeue(fila); // Remove o último (50)
    imprimirFila(fila); // Fila vazia

    liberarFila(fila); // Liberação de memória
    fila = NULL;

    return 0;
}
