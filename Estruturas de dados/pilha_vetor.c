#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// ##################################################### //
// PILHA COM VETOR

// Cria a estrutura de uma pilha
typedef struct estPilha {
    int *itens; // Ponteiro para o array que armazena os elementos da pilha
    int tamanho; // Tamanho máximo da pilha
    int topo; // Índice do topo da pilha (inicialmente -1, porque começa vazia)
} estPilha;

// Cria e inicializa uma pilha chamada pilha
void init_pilha (estPilha *pilha, int tamanho) {
    pilha->itens = (int*)malloc(tamanho * sizeof(int)); // Aloca memória para o array da pilha
    
    // Falha de alocação
    if (pilha->itens == NULL) {
        printf("Erro ao alocar memória para os itens da pilha.\n");
        return;
    }

    pilha->tamanho = tamanho; // Define o tamanho máximo da pilha
    pilha->topo = -1; // Inicializa o topo como -1 (pilha vazia)
}

/*
'itens' é como se fosse um vetor de inteiros. 'malloc' separa um bloco contíguo de memória para armazenar os inteiros. Esse bloco terá tamanho * 4 bytes. 'itens', portanto, contém o endereço de memória do primeiro byte desse bloco.
Quando fazemos itens[1], estamos acessando o segundo inteiro desse bloco, que ocupa os bytes 5 a 8.
*/

/*
'pilha' é um ponteiro para 'pilha'. Ou seja, ela aponta para um bloco de memória que contém dados do tipo 'pilha'.

Sendo assim, 'pilha' tem um total de 16 bytes:
int *itens = 8 bytes (qualquer endereço de memória precisa de 8 bytes na arquitetura x64)
int tamanho = 4 bytes
int topo = 4 bytes

Mas '*itens' é um ponteiro que aponta para um bloco de memória onde de fato estão os itens da pilha. 'pilha' apenas armazena o endereço desse bloco, e não o bloco.

Se o 'tamanho' for 5, então o bloco apontado por 'itens' teria 4 * 5 = 20 bytes, pois são necessários 4 bytes para cada número armazenado na pilha.
*/

bool pilha_cheia (estPilha *pilha) {
    return pilha->topo == pilha->tamanho - 1; // Retorna true se a pilha estiver cheia
}

bool pilha_vazia (estPilha *pilha) {
    return pilha->topo == -1; // Retorna true se o topo for -1 (pilha vazia)
}

// Insere elementos na pilha
void push (estPilha *pilha, int item) {
    if (!pilha_cheia(pilha)) { // Se a pilha não estiver cheia
        pilha->topo = pilha->topo + 1; // Incrementa o topo, adicionando o item na pilha
        pilha->itens[pilha->topo] = item; // Insere o item no topo da pilha
    }
    else {
        printf("Pilha cheia.\n");
    }
}

// Insere elementos ordenadamente na pilha (crescente)
void push_ordenado (estPilha *pilha, int item) {
    if (!pilha_cheia(pilha)) { // Se a pilha não estiver cheia
    
        int i = pilha->topo; // Topo inicial
        pilha->topo += 1; // Incrementa o topo
        
        // Encontra a posição correta do item novo
        while (i >= 0 && pilha->itens[i] > item) {
            pilha->itens[i + 1] = pilha->itens[i];
            i--;
        }
        // Insere o novo item na posição correta
        pilha->itens[i + 1] = item;
    }
    else { // Pilha cheia
        printf("Pilha cheia.\n");
    }
 }

// Remove elementos da pilha
int pop (estPilha *pilha) {
    if (!pilha_vazia(pilha)) { // Se a pilha não estiver vazia
        pilha->topo = pilha->topo - 1; // Decrementa o topo, removendo o item da pilha
        return pilha->itens[pilha->topo + 1]; // Retorna o elemento removido
    }
    else {
        printf("Pilha vazia.\n");
        return INT_MAX; // Retorna um valor de erro se a pilha estiver vazia
    }
}

// Retorna o último item inserido na pilha
int top (estPilha *pilha) {
    if (!pilha_vazia(pilha)) {
        return pilha->itens[pilha->topo]; // Retorna o item do topo
    } 
    else {
        printf("Pilha vazia.\n");
        return INT_MAX; // Retorna um valor de erro se a pilha estiver vazia
    }
}

// Retorna a quantidade de itens na pilha
int size (estPilha *pilha) {
    return pilha->topo + 1; // topo é um índice de base 0
}

// Limpa todos os itens da pilha sem destrui-la
void clear (estPilha *pilha) {
    pilha->topo = -1; // Reseta o topo
}

void imprimir_pilha (estPilha *pilha) {
    //printf("<< \n");
    for (int i = pilha->topo; i >= 0; i--) {
        if (i == pilha->topo) {
            printf("topo ->  %d\n", pilha->itens[i]); // Marca o topo
        } 
        else
            printf("\t %d\n", pilha->itens[i]); // Imprime os demais elementos
    }
    //printf(">>\n");
}

int main() {
    estPilha *pilha = malloc(sizeof(estPilha));

    /*
    'malloc' separa um espaço dentro da memória para armazenar a pilha e retorna o endereço desse espaço para a variável 'pilha'.

    Ou seja, 'pilha' é declarada como uma variável do tipo ponteiro para pilha. Como ela armazena o endereço de um espaço de memória, precisamos saber quem é esse endereço. O 'malloc', então, separa um espaço na memória para armazenar uma todos os campos de uma 'pilha' e retorna esse endereço para 'pilha'.

    Sendo assim, 'pilha' aponta para um espaço na memória que possui 16 bytes: 8 do int *itens + 4 de int tamanho + 4 de int topo.

    'itens' também é um ponteiro, que aponta para outro espaço de memória, mas esse espaço é variável, pois depende do tamanho. Isto é, o espaço de memória destinado aos itens da pilha possui 4 bytes para cada item da pilha. Se a pilha tiver 10 itens, então 'itens' apontará para um espaço de memória com 40 bytes.
    */

    // Push
    init_pilha(pilha, 10);
    push(pilha, 10);
    push(pilha, 5);
    push(pilha, 15);
    imprimir_pilha(pilha);
    printf("\nTopo: %d\n", top(pilha));
    printf("Tamanho: %d\n", size(pilha));
    clear(pilha);
    printf("\n");

    // Push ordenado
    init_pilha(pilha, 10);
    push_ordenado(pilha, 15);
    push_ordenado(pilha, 10);
    push_ordenado(pilha, 5);
    imprimir_pilha(pilha);
    printf("\nTopo: %d\n", top(pilha));
    printf("Tamanho: %d\n", size(pilha));

    // Libera a memória alocada para a pilha e seus itens
    free(pilha->itens);  // Libera a memória alocada para o array de itens
    free(pilha);  // Libera a memória alocada para a estrutura da pilha
}
