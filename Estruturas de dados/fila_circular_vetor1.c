#include <stdio.h>
#include <stdlib.h>

// ##################################################### //
// FILA CIRCULAR COM VETOR SEM CONTADOR (FCV)

// Estrutura da fila
typedef struct estFila {
    int *itens; // Ponteiro para o array de elementos da fila
    int tam; // Quantidade máxima de elementos da fila
    int ini; // Índice do início da fila
    int fim; // Índice do final da fila
} estFila;

// Inicializa a fila
void init_fila (estFila *fila, int tam) {
    fila->itens = (int *)malloc(tam * sizeof(int));
    
    // Falha de alocação
    if (fila->itens == NULL) {
        printf("Erro ao alocar memória para os itens da fila.\n");
        return;
    }
    
    // Inicializações
    fila->tam = tam;
    fila->ini = 0;
    fila->fim = 0;
}

// Enfileirar: inserir elementos na fila
void enqueue (estFila *fila, int novo) {
    
    // Falha de alocação
    if (fila == NULL) {
        printf("Fila não existe.\n");
        return;
    }
    
    // Fila cheia
    // Início = Fim + 1
    if (fila->ini == (fila->fim + 1) % fila->tam) {
        printf("Fila cheia.\n");
        return;
    }

    // Fila não cheia
    fila->itens[fila->fim] = novo;

    // Incrementa o fim, resentando após inserir no último índice, mantendo a circularidade
    fila->fim = (fila->fim + 1) % fila->tam; 

    /*
    Obs.: ao fazer Início = Fim + 1, uma posição do vetor sempre ficará vazia. Por exemplo, se o vetor tem tamanho 5, apenas 4 posições poderão ser preenchidas. Entretanto, isso garante que não haja ambiguidade entre fila vazia e fila cheia.

    Exemplo: seja um vetor de tamanho 5.
    ini = 0, fim = 0, (fim + 1) % 5 = 1 → [ , , , , ] → Fila vazia
    ini = 0, fim = 1, (fim + 1) % 5 = 2 → [10, , , , ] → 1 elemento
    ini = 0, fim = 2, (fim + 1) % 5 = 3 → [10, 20, , , ] → 2 elementos
    ini = 0, fim = 3, (fim + 1) % 5 = 4 → [10, 20, 30, , ] → 3 elementos
    ini = 0, fim = 4, (fim + 1) % 5 = 0 → [10, 20, 30, 40, ] → Fila cheia
    */
}

// Desinfileirar: retirar elementos da fila
void dequeue (estFila *fila) {
    
    // Falha de alocação
    if (fila == NULL) {
        printf("Fila não existe.\n");
        return;
    }
    
    // Fila vazia
    // Início = Fim
    if (fila->ini == fila->fim) {
        printf("Fila vazia.\n");
        return;
    }

    // Incrementa o início, resentando após inserir no último índice, mantendo a circularidade
    fila->ini = (fila->ini + 1) % fila->tam; 
}

void imprimirFila (estFila *fila) {
    
    // Falha de alocação
    if (fila == NULL) {
        printf("Fila não existe.\n");
        return;
    }
    
    // Pilha vazia
    if (fila->ini == fila->fim) {
        printf("Fila vazia.\n");
    }
    
    int i = fila->ini;
    while (i != fila->fim) {
        if (i != fila->ini) {printf(" ");}
        printf("%d", fila->itens[i]);
        i = (i + 1) % fila->tam; // Mantém a circularidade
    }    
    printf("\n");
}

int main() {

    // Aloca memória para a fila
    estFila *fila = (estFila*)malloc(sizeof(estFila));

    // Inicializa a fila
    init_fila(fila, 4);

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

    dequeue(fila);
    dequeue(fila);
    dequeue(fila);
    imprimirFila(fila); // Fila vazia
    
    // Libera a memória alocada
    free(fila->itens);
    free(fila);

    return 0;
}