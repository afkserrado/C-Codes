// ## Busca Binária ##

#include <stdio.h>
#include <stdlib.h>

#define tam 10

int buscaBinaria (int A[], int k){
    int ini = 0;
    int fim = tam - 1;
    int meio;

    while (ini <= fim) {
        meio = (ini + fim) / 2;
        if (k < A[meio]) {
            fim = meio - 1;
        } 
        else if (k > A[meio]) {
            ini = meio + 1;
        } 
        else {
            return meio; // Retorna o índice onde o valor foi encontrado
        }
    }

    return -1; // Retorna -1 se o valor não for encontrado
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
    int A[tam] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Vetor já ordenados
    
    printf("## Busca Binária ##\n");

    // Exibindo o vetor desordenado
    printf("Vetor inicial: ");
    imprimeVetor(A);
    printf("\n");

    // Realizando a busca binária
    int resultado = buscaBinaria(A, 8); // Procurando o valor 8 no vetor
    if (resultado != -1) {
        printf("Valor encontrado na posição %d.\n", resultado);
    } else {
        printf("Valor não encontrado\n");
    }
}