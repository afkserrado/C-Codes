#include <stdio.h>
#include <stdlib.h>

// ##################################################### //
// FILA CIRCULAR COM VETOR COM CONTADOR (FCV)

// Estrutura da fila
typedef struct estFila {
    int *itens; // Ponteiro para o array de elementos da fila
    int tam; // Quantidade máxima de elementos da fila
    int qtd; // Quantidade de elementos da fila
    int cabeca; // Índice do primeiro elemento da fila
    int cauda; // Índice do último elemento da fila
} estFila;

// Inicializa a fila
void init_fila (estFila *fila, int tam) {
    fila->itens = (int*)malloc(tam * sizeof(int));
    fila->tam = tam;
    fila->qtd = 0;
    fila->cabeca = 0;
    fila->cauda = 0;
}

// Enfileirar: inserir elementos na fila
void enqueue (estFila *fila, int novo) {
    // Verifica se a fila está cheia
    if (fila->qtd == fila->tam) {
        printf("Fila cheia.\n");
        return;
    }

    fila->itens[fila->cauda] = novo; // Acrescenta no final da fila
    fila->cauda = (fila->cauda + 1) % fila->tam; // Incrementa a cauda, mantendo a circularidade
    fila->qtd += 1; // Incrementa quantidade
}

// Desinfileirar: retirar elementos da fila
void dequeue (estFila *fila) {
    // Verifica se a fila está vazia
    if (fila->qtd == 0) {
        printf("Fila vazia.\n");
        return;
    }
    
    fila->cabeca = (fila->cabeca + 1) % fila->tam; // Incrementa a cabeça, mantendo a circularidade
    fila->qtd -= 1; // Decrementa quantidade
}

void imprimirFila (estFila *fila) {
    int i = fila->cabeca;
    for (int cont = 0; cont < fila->qtd; cont++) {
        if (cont != 0) {printf(" ");}
        printf("%d", fila->itens[i]);
        i = (i + 1) % fila->tam; // Mantém a circularidade
    }    
    printf("\n");
}

int main() {

    // Aloca memória para a fila
    estFila *fila = (estFila*)malloc(sizeof(estFila));

    // Inicializa a fila
    init_fila(fila, 3);

    dequeue(fila); // Fila vazia

    enqueue(fila, 10);
    enqueue(fila, 20);
    enqueue(fila, 30);
    imprimirFila(fila); // 10, 20, 30
    
    dequeue(fila);
    imprimirFila(fila); // 20, 30

    enqueue(fila, 40); 
    imprimirFila(fila); // Vetor: [40, 20, 30] | Saída: 20, 30, 40

    enqueue(fila, 50); // Fila cheia
    
    // Libera a memória alocada
    free(fila->itens);
    free(fila);

    return 0;
}