// ## Insertion Sort ##

#include <stdio.h>
#include <stdlib.h>

#define tam 10

//Insertion Sort
void insertionSort (int A[]){
    int i, j, temp;
    for (j = 1; j < tam; j++){
        temp = A[j];
        i = j - 1;
        
        while (i >= 0 && A[i] > temp){
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = temp;
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

int main () {

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #endif

    // Declarações
    int A[tam] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    
    printf("## Insertion Sort ##\n");

    // Exibindo o vetor desordenado
    printf("Vetor inicial: ");
    imprimeVetor(A);

    // Ordenando o vetor
    insertionSort(A);

    // Exibindo o vetor ordenado
    printf("\nVetor ordenado: ");
    imprimeVetor(A);
    printf("\n\n");
}