#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// ##################################################### //
// PILHA COM LISTA SIMPLESMENTE LIGADA LINEAR (PLSLL)

// Define a estrutura de um nó da lista
typedef struct node {
    int chave;
    struct node *prox;
} node;

// Cria a estrutura de uma pilha baseada em lista
typedef struct estPilha {
    node *topo; 
} estPilha;

// Cria e inicializa um novo nó, configurando seus ponteiros para NULL
node *init_node (int chave) {
    node *novo = (node*)malloc(sizeof(node)); // Aloca memória para o nó
    
    // Falha de alocação
    if (novo == NULL) {
        printf("Erro ao alocar memória para o nó.\n");
        return NULL;
    }

    novo->chave = chave;
    novo->prox = NULL;
    return novo;
}

// Cria e inicializa uma pilha
estPilha *init_pilha () {
    estPilha *pilha = (estPilha*)malloc(sizeof(estPilha)); // Aloca memória para a estrutura da pilha
    
    // Falha de alocação    
    if (pilha == NULL) {
        printf("Erro ao alocar memória para a estrutura da pilha.\n");
        return NULL;
    }

    pilha->topo = NULL;
    return pilha;
}

// Insere elementos no topo da pilha (início da lista)
void push (estPilha *pilha, node *novo) {
    
    // Falha de alocação
    if (pilha == NULL) {
        printf("Memória não alocada para a pilha.\n");
        return;
    }

    if (novo == NULL) {
        printf("Memória não alocada para o nó.\n");
        return;
    }  

    novo->prox = pilha->topo;
    pilha->topo = novo;  
}

// Remove elementos do topo da pilha (início da lista)
int pop (estPilha *pilha) {
    
    // Falha de alocação
    if (pilha == NULL) {
        printf("Memória não alocada para a pilha.\n");
        return INT_MAX;
    }

    // Pilha vazia
    if (pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return INT_MAX;
    }

    node *temp = pilha->topo;
    pilha->topo = temp->prox;
    int valor = temp->chave; // Armazena a chave para retorno
    
    free(temp);
    return valor;
}

// Retorna o último item inserido na pilha
int top (estPilha *pilha) {
    
    // Falha de alocação
    if (pilha == NULL) {
        printf("Memória não alocada para a pilha.\n");
        return INT_MAX;
    }
    
    // Pilha não vazia
    if (pilha->topo != NULL) {
        return pilha->topo->chave; // Retorna o item do topo
    } 

    // Pilha vazia
    else {
        printf("Pilha vazia.\n");
        return INT_MAX; // Retorna um valor de erro se a pilha estiver vazia
    }
}

// Limpa todos os itens da pilha sem destrui-la
void clear (estPilha *pilha) {
    
    // Falha de alocação
    if (pilha == NULL) {
        printf("Memória não alocada para a pilha.\n");
        return;
    }

    // Pilha vazia
    if (pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }
    
    node *x = pilha->topo; // Inicializa no topo da pilha
    while (x != NULL) {
        node *temp = x;
        x = x->prox; // Avança
        free(temp); // Libera memória do nó
    }
    pilha->topo = NULL;
}

// Imprime a pilha
void imprimir_pilha (estPilha *pilha) {
    
    // Falha de alocação
    if (pilha == NULL) {
        printf("Memória não alocada para a pilha.\n");
        return;
    }

    // Pilha vazia
    if (pilha->topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }
    
    node *x = pilha->topo; // Inicializa no topo da pilha
    
    // Imprime o topo
    if (x != NULL) { // Se a pilha não estiver vazia
        printf("topo ->  %d\n", x->chave); 
        x = x->prox; // Avança
    }
    
    // Imprime os demais elementos
    while (x != NULL) {
        printf("\t %d\n", x->chave); 
        x = x->prox; // Avança
    }
}

// Libera a memória alocada para os nós e a estrutura da pilha
void libera_pilha (estPilha *pilha) {
    
    // Falha de alocação
    if (pilha == NULL) {
        printf("Memória não alocada para a pilha.\n");
        return;
    }

    node *x = pilha->topo; // Inicializa no topo da pilha

    // Libera os elementos da pilha
    while (x != NULL) {
        node *temp = x;
        x = x->prox; // Avança
        free(temp); // Libera memória do nó
    }
    
    free(pilha); // Libera memória alocada para a estrutura da pilha
}

int main() {
    estPilha *pilha = init_pilha();

    // Push
    push(pilha, init_node(10));
    push(pilha, init_node(5));
    push(pilha, init_node(15));
    imprimir_pilha(pilha);
    printf("\nTopo: %d\n", top(pilha));
    clear(pilha);
    imprimir_pilha(pilha);
    printf("\n");

    // Libera a memória alocada para a pilha e seus itens
    libera_pilha(pilha);
}