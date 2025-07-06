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
        printf("Falha ao alocar memória para a estrutura da pilha.\n");
        return NULL;
    }

    fila->fim = NULL;
    return fila;
}

// Enfileirar: inserir elementos na fila
void enqueue (estFila *fila, node *novo) {
    
    // Fila vazia
    if (fila->fim == NULL) {
        fila->fim = novo;
        novo->prox = novo; // Fecha o círculo
        return;
    }

    // Fila não vazia
    novo->prox = fila->fim->prox; // Novo aponta para o início atual da fila
    fila->fim->prox = novo; // Fim atual aponta para o novo
    fila->fim = novo; // Fim recebe o novo
}

// Desinfileirar: retirar elementos da fila
void dequeue (estFila *fila) {
    
    // Fila vazia
    if (fila->fim == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    node *inicio = fila->fim->prox; // Guarda o início da fila

    // Fila com elemento único
    if (fila->fim == inicio) {
        fila->fim = NULL;
    }
    // Fila com mais de um elemento
    else {
        fila->fim->prox = inicio->prox; // Atualiza o início da fila
    }
          
    free(inicio);
}

// Exibe os elementos da fila
void imprimirFila (estFila *fila) {
    
    // Fila vazia
    if (fila->fim == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    node *inicio = fila->fim->prox; // Guarda o início da fila
    node *x = inicio; // Percorre a fila, começando do início

    do {
        if (x != inicio) {printf(" ");}
        printf("%d", x->chave);
        x = x->prox;
    } while (x != inicio);
    printf("\n");
}

void liberarFila (estFila *fila) {
    
    // Fila vazia
    if (fila->fim == NULL) {
        return;
    }

    node *inicio = fila->fim->prox; // Guarda o início da fila
    node *x = inicio; // Percorre a fila, começando do início

    // Libera os nós da lista
    do {
        node *temp = x;
        x = x->prox;
        free(temp);
    } while (x != inicio);

    // Libera a estrutura da fila
    free(fila);
    fila = NULL;
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
}