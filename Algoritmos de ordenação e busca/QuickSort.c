// ## Quick Sort ##

#include <stdio.h>
#include <stdlib.h>

void trocar (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar (int *V, int ini, int fim) {
    int pivo = V[fim]; // Escolhendo o último elemento como pivô
    int i = ini - 1; // Inicializa o índice dos elementos menores que o pivô

    for (int j = ini; j < fim; j++) {
        if (V[j] <= pivo) { // Coloca os menores à esquerda do pivô
            i++;
            trocar(&V[i], &V[j]);
        }
    }

    trocar(&V[i + 1], &V[fim]); // Coloca o pivô na posição correta
    return (i + 1); // Retorna a posição do pivô
}

void quickSort (int *V, int ini, int fim) {
    if (ini < fim) {
        int pivo = particionar(V, ini, fim);
        quickSort(V, ini, pivo - 1); // Metade à esquerda do pivô
        quickSort(V, pivo + 1, fim); // Metade à direita do pivô
    }
}

void preencherVetor (int *V, int tam) {
    for (int i = 0; i < tam; i++) {
        V[i] = rand() % 500;
    }
}

void imprimirVetor (int *V, int tam) {
    printf("[");
    for (int i = 0; i < tam; i++) {
        printf("%d", V[i]);
        if (i < tam - 1) {printf(", ");}
    }
    printf("]");
}
 
int main () {
    int tam;

    // Entrada de dados
    printf("Informe o tamanho do array: ");
    scanf("%d", &tam);
    
    // Alocação de memória
    int *A = (int *)malloc(tam * sizeof(int));

    printf("\n");

    // Preenche os campos do vetor
    preencherVetor(A, tam);
    imprimirVetor(A, tam);
    printf("\n");

    // Ordenação
    quickSort(A, 0, tam - 1);
    imprimirVetor(A, tam);

    printf("\n\n");

    free(A);
    return 0;
}