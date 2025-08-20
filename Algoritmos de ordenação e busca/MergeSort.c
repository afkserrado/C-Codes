// ## Merge Sort ##

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge (int *V, int ini, int meio, int fim) {
    
    // Tamanho dos subvetores da esquerda e da direita
    int tamEsq = meio - ini + 1;
    int tamDir = fim - meio;

    // Alocando memória para os subvetores
    int *esq = (int *)malloc((tamEsq + 1) * sizeof(int)); // +1 para o INT_MAX
    int *dir = (int *)malloc((tamDir + 1) * sizeof(int));

    int i, j;

    // Preenchendo o subvetor esquerdo
    for (i = 0; i < tamEsq; i++) {
        esq[i] = V[ini + i]; // Generalização para qualquer valor de "ini"
    }

    // Preenchendo o subvetor direito
    for (j = 0; j < tamDir; j++) {
        dir[j] = V[meio + 1 + j];
    }

    // Preenche a última posição dos subvetores
    esq[tamEsq] = INT_MAX;
    dir[tamDir] = INT_MAX;

    // Reinicializa
    i = j = 0;

    // Combina os subvetores
    for (int k = ini; k <= fim; k++) {
        if (esq[i] < dir[j]) {
            V[k] = esq[i];
            i++;
        }
        else {
            V[k] = dir[j];
            j++;
        }
    }

    // Desaloca a memória
    free(esq);
    free(dir);
}

void mergeSort (int *V, int ini, int fim) {
    // Caso base
    if (ini < fim) {
        int meio = (ini + fim) / 2;
        mergeSort(V, ini, meio); // Metade esquerda
        mergeSort(V, meio + 1, fim); // Metade direita
        merge(V, ini, meio, fim); // Ordena o vetor
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
    mergeSort(A, 0, tam - 1);
    imprimirVetor(A, tam);

    printf("\n\n");

    free(A);
    return 0;
}