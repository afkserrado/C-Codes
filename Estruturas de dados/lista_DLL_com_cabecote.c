#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ##################################################### //
// LISTA DUPLAMENTE LIGADA LINEAR COM CABEÇOTE (LDLLC)

// Define a estrutura de um nó da lista
typedef struct node {
    int chave;
    struct node *ante; 
    struct node *prox;
} node;

// Define a estrutura de uma lista duplamente encadeada
typedef struct ldllc {
    node *cabeca;
    node *cauda;
} ldllc;

// Cria e inicializa um novo nó, configurando seus ponteiros para NULL
node *init_node (int chave) {
    node *novo = (node*)malloc(sizeof(node)); // Aloca memória para o nó
    
    // Falha de alocação
    if (novo == NULL) {
        printf("Erro ao alocar memória para o nó.\n");
        return NULL;
    }

    // Inicialização
    novo->chave = chave;
    novo->ante = NULL;
    novo->prox = NULL;
    return novo;
}

// Cria e inicializa uma nova lista, configurando seus ponteiros para NULL (lista vazia)
ldllc *init_lista () {
    ldllc *lista = (ldllc*)malloc(sizeof(ldllc));
    
    // Falha de alocação    
    if (lista == NULL) {
        printf("Erro ao alocar memória para a estrutura da lista.\n");
        return NULL;
    }

    // Inicialização
    lista->cabeca = init_node(INT_MAX); // Cabeçote
    lista->cabeca->prox = NULL;
    lista->cauda = NULL;
    return lista;
}

// Insere um novo nó no início da lista
void inserir_node (ldllc *lista, node *novo) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }

    if (novo == NULL) {
        printf("Memória não alocada para o nó.\n");
        return;
    }    
    
    // Lista vazia (apenas o cabeçote)
    if (lista->cabeca->prox == NULL) {
        lista->cabeca->prox = novo;  // O cabeçote agora aponta para o novo nó
        novo->ante = lista->cabeca;  // O novo nó aponta para o cabeçote
        lista->cauda = novo;         // O novo nó é a cauda da lista
    } 
    // Lista não vazia
    else {
        // Insere o novo nó no início da lista (após o cabeçote)
        novo->prox = lista->cabeca->prox;   // O novo nó aponta para o primeiro nó real
        lista->cabeca->prox->ante = novo;   // O primeiro nó real agora aponta para o novo nó
        lista->cabeca->prox = novo;         // O cabeçote agora aponta para o novo nó
        novo->ante = lista->cabeca;         // O novo nó aponta para o cabeçote
    }
}

// Insere um novo nó na posição ordenada
void inserir_node_ordenado (ldllc *lista, node *novo) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }

    if (novo == NULL) {
        printf("Memória não alocada para o nó.\n");
        return;
    }   

    // Lista vazia (apenas o cabeçote)
    if (lista->cabeca->prox == NULL) {
        lista->cabeca->prox = novo;  // O cabeçote agora aponta para o novo nó
        novo->ante = lista->cabeca;  // O novo nó aponta para o cabeçote
        lista->cauda = novo;         // O novo nó é a cauda da lista
    } 

    // Lista não vazia
    else { 
        
        // Variáveis temporárias
        node *x = lista->cabeca->prox;
        int chave = novo->chave;

        while (x != NULL && chave > x->chave) {
            x = x->prox;
        }

        // Caso 1: o novo é o primeiro item da lista
        if (x == lista->cabeca->prox) {
            novo->prox = lista->cabeca->prox;
            novo->ante = lista->cabeca;
            lista->cabeca->prox->ante = novo;
            lista->cabeca->prox = novo;
        }
        // Caso 2: o novo é o último item da lista
        else if (x == NULL) {
            novo->ante = lista->cauda;
            lista->cauda->prox = novo;
            lista->cauda = novo;
        }
        // Caso 3: o novo ocupa qualquer posição intermediária da lista
        else {
            novo->ante = x->ante;
            novo->prox = x;
            x->ante->prox = novo;
            x->ante = novo;      
        }
    }
}

// Remover um nó qualquer da lista
void remover_node(ldllc *lista, int chave) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }
    
    // Lista vazia
    if (lista->cabeca->prox == NULL) { 
        return; // Não há nada para remover
    }
    
    node *x = lista->cabeca->prox;

    // Procurando a chave a ser excluída
    while (x != NULL && x->chave != chave) { 
        x = x->prox;
    }

    // Chave encontrada
    if (x != NULL) {
        
        // Caso 1: O nó a ser removido é o primeiro nó real da lista (após o cabeçote)
        if (x == lista->cabeca->prox) {
            
            // Lista unitária (apenas o nó real após o cabeçote)
            if (x->prox == NULL) {
                lista->cabeca->prox = NULL; // Cabeçote não aponta para nenhum nó real
                lista->cauda = NULL;        // Não há cauda mais
            }
            // Lista com múltiplos elementos
            else {
                lista->cabeca->prox = x->prox;   // Cabeçote agora aponta para o próximo nó
                lista->cabeca->prox->ante = lista->cabeca; // O novo primeiro nó aponta para o cabeçote
            }
        }

        // Caso 2: O nó a ser removido é a cauda da lista
        else if (x == lista->cauda) {
            lista->cauda = x->ante;         // A cauda é o nó anterior
            lista->cauda->prox = NULL;      // A cauda agora aponta para NULL
        }

        // Caso 3: O nó a ser removido é um nó intermediário
        else {
            x->ante->prox = x->prox;       // O nó anterior aponta para o próximo
            x->prox->ante = x->ante;       // O próximo nó aponta para o anterior
        }

        free(x); // Libera o nó removido
    }
}

// Imprime a lista
void imprimir_lista (ldllc *lista) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }
    
    // Lista vazia
    if (lista->cabeca->prox == NULL) { 
        printf("A lista está vazia.\n");
        return;
    }
    
    node *x = lista->cabeca->prox; // Inicializa x com a "cabeca" da lista
    printf("\n(NULL)"); // Início da lista
    while (x != NULL) {
        printf("<- (%d) ->", x->chave);
        x = x->prox;
    }
    printf(" (NULL)\n\n"); // Fim da lista
}

// Função para liberar a lista e seus nós
void liberar_lista(ldllc *lista) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }
    
    node *x = lista->cabeca->prox;
    while (x != NULL) {
        node *temp = x;
        x = x->prox;
        free(temp); // Libera a memória de cada nó
    }

    free(lista); // Libera a memória da lista
}

int main(){
    
    ldllc *lista1 = init_lista();
    ldllc *lista2 = init_lista();

    inserir_node(lista1, init_node(20));
    inserir_node(lista1, init_node(37));
    inserir_node(lista1, init_node(18));
    inserir_node(lista1, init_node(40));
    inserir_node(lista1, init_node(18));
    inserir_node(lista1, init_node(100));
    imprimir_lista(lista1);

    remover_node(lista1, -1);
    printf("Depois\n");
    imprimir_lista(lista1);
    remover_node(lista1, 40);
    printf("Depois\n");
    imprimir_lista(lista1);
    remover_node(lista1, 20);
    printf("Depois\n");
    imprimir_lista(lista1);
    remover_node(lista1, 100);
    printf("Depois\n");
    imprimir_lista(lista1);

    inserir_node_ordenado(lista2, init_node(20));
    inserir_node_ordenado(lista2, init_node(37));
    inserir_node_ordenado(lista2, init_node(18));
    inserir_node_ordenado(lista2, init_node(40));
    inserir_node_ordenado(lista2, init_node(18));
    inserir_node_ordenado(lista2, init_node(-1));

    imprimir_lista(lista2);
    remover_node(lista2, -1);
    printf("Depois\n");
    imprimir_lista(lista2);
    remover_node(lista2, 40);
    printf("Depois\n");
    imprimir_lista(lista2);
    remover_node(lista2, 20);
    printf("Depois\n");
    imprimir_lista(lista2);
    remover_node(lista2, 100);
    printf("Depois\n");
    imprimir_lista(lista2);

    // Libera a memória alocada para todos os nós e para a lista
    liberar_lista(lista1);
    liberar_lista(lista2);
    lista1 = NULL;
    lista2 = NULL;
}