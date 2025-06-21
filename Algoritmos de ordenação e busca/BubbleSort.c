// ## Bubble Sort ##

#include <stdio.h>
#include <stdlib.h>

#define tam 10

// Bubble Sort
void bubbleSort (int A[]){
    int i, j, temp;
    for (i = 0; i < tam - 1; i++) {
        for (j = 0; j < tam - i - 1; j++) {
            if(A[j] > A[j + 1]) {
                temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

// Imprimindo o vetor
void imprimeVetor (int A[]){
    int i, primeiro = 0;
    printf("[");
    for (i = 0; i < tam; i++){
        if (primeiro == 0){
            printf("%d", A[i]);
            primeiro = 1;
        }
        else
            printf(" %d", A[i]);
    }
    printf("]");
}

//Função principal
int main () {

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #endif

    // Declarações
    int A[tam] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    
    printf("## Bubble Sort ##\n");

    // Exibindo o vetor desordenado
    printf("Vetor inicial: ");
    imprimeVetor(A);

    // Ordenando o vetor
    bubbleSort(A);

    // Exibindo o vetor ordenado
    printf("\nVetor ordenado: ");
    imprimeVetor(A);
    printf("\n\n");
}