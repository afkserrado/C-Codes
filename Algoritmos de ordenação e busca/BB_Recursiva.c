// ## Busca Binária Recursiva ##

#include <stdio.h>
#include <stdlib.h>

int buscaBinaria (int arr[], int esq, int dir, int alvo) {
    int meio = (esq + dir) / 2;

    // Caso base: alvo não encontrado
    if (esq > dir) {
        return -1;
    }
    // Ao buscar na metade esquerda, "dir" vai diminuindo
    // Ao buscar na metade direita, "esq" vai aumentando
    // Isso se repete até que o subvetor não contenha mais nenhum elemento

    // Alvo encontrado
    if (arr[meio] == alvo) {
        return meio; 
    }

    // Busca na metade esquerda
    if (alvo < arr[meio]) {
        return buscaBinaria(arr, esq, meio - 1, alvo); 
    }

    // Busca na metade direita
    return buscaBinaria(arr,meio + 1, dir, alvo);
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};  // Vetor ordenado
    int n = sizeof(arr) / sizeof(arr[0]);  // Tamanho do vetor
    int alvo = 19;  // Elemento a ser buscado

    int resultado = buscaBinaria(arr, 0, n - 1, alvo);  // Chama a função de busca binária

    if (resultado != -1) {
        printf("Elemento encontrado na posição: %d\n", resultado);
    } else {
        printf("Elemento não encontrado.\n");
    }

    return 0;
}