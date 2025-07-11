#include <stdio.h>
#include <stdlib.h>

// ##################################################### //
// LISTA DUPLAMENTE LIGADA LINEAR (LDLL)

// Define a estrutura de um nó da lista
typedef struct node {
    int chave;
    struct node *ante; 
    struct node *prox;
} node;

/*
Uma instância do tipo node possui 24 bytes:

- 4 bytes para o int chave
- 4 bytes de padding (adicionados pelo compilador)
- 8 bytes para o ponteiro ante
- 8 bytes para o ponteiro prox

O que é o "padding"?
O padding é uma técnica utilizada pelo compilador que adiciona bytes extras à estrutura de dados. Isso é feito para garantir que os endereços de memória dos ponteiros (que ocupam 8 bytes) estejam alinhados a múltiplos de 8 bytes. O alinhamento de memória é uma prática importante, especialmente em arquiteturas de 64 bits, onde a CPU lê os dados de 8 em 8 bytes (64 bits), garantindo que o acesso à memória seja otimizado.

Por que o padding é necessário?
Em uma arquitetura x64, a CPU trabalha de forma mais eficiente quando os dados estão alinhados de acordo com seu tamanho, especialmente para tipos como ponteiros (8 bytes). Se a estrutura node fosse armazenada sem o preenchimento (padding), o ponteiro ante poderia não estar alinhado a 8 bytes, o que faria com que a CPU precisasse realizar acessos adicionais à memória, prejudicando a performance.

Ao adicionar 4 bytes de padding entre o int chave e o ponteiro ante, o compilador assegura que o ponteiro comece em um endereço múltiplo de 8 bytes, permitindo que a CPU faça o acesso em blocos de 8 bytes e melhor aproveite os recursos de memória da arquitetura de 64 bits.

Obs. 1: lembrando que a palavra de um processador x64 é 64 bits. Por isso ele lê de 8 em 8 bytes.
Obs. 2: os bytes de padding não são utilizados para armazenar dados, apenas para alinhamento.
*/

// Define a estrutura de uma lista duplamente encadeada
typedef struct ldll {
    node *cabeca;
    node *cauda;
} ldll;

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

/*
Obs. 1: a variável novo é um ponteiro para uma estrutura node, que contém dados de tipos diferentes (neste caso, um int e dois ponteiros). A alocação de memória com malloc garante espaço suficiente para armazenar todos os campos dessa estrutura.

Obs. 2: a função init_node retorna um ponteiro para node, que aponta para a memória alocada para o nó recém-criado.
*/

// Cria e inicializa uma nova lista, configurando seus ponteiros para NULL (lista vazia)
ldll *init_lista () {
    ldll *lista = (ldll*)malloc(sizeof(ldll));
    
    // Falha de alocação    
    if (lista == NULL) {
        printf("Erro ao alocar memória para a estrutura da lista.\n");
        return NULL;
    }

    // Inicialização
    lista->cabeca = NULL;
    lista->cauda = NULL;
    return lista;
}

// Insere um novo nó no início da lista
void inserir_node (ldll *lista, node *novo) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }

    if (novo == NULL) {
        printf("Memória não alocada para o nó.\n");
        return;
    }    
    
    // Lista vazia
    if (lista->cabeca == NULL) { 
        lista->cabeca = novo; // Insere o novo nó na cabeça da lista
        lista->cauda = novo; // Insere o novo nó na cauda da lista
    }
    /*
    Obs. 1: "novo->ante" e "novo->prox" já apontam para NULL, porque isso foi definido no momento da inicialização do novo com init_node.
    
    Obs. 2: ao fazer "lista->cauda = novo" garantimos que "lista->cauda" sempre seja o último elemento da lista, pois a inserção está ocorrendo sempre na cabeça.
    */ 

    // Lista não vazia 
    else {  
        // Insere o novo nó no início da lista
        novo->prox = lista->cabeca; // "prox" do novo nó aponta para o atual "cabeca"
        lista->cabeca->ante = novo; // "ante" do atual "cabeca" aponta para o novo nó
        lista->cabeca = novo; //  "cabeca" recebe o novo nó
    }
}

// Insere um novo nó na posição ordenada
void inserir_node_ordenado (ldll *lista, node *novo) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }

    if (novo == NULL) {
        printf("Memória não alocada para o nó.\n");
        return;
    }   

    // Lista vazia
    if (lista->cabeca == NULL) { 
        lista->cabeca = novo;
        lista->cauda = novo;
    }

    // Lista não vazia
    else { 
        
        // Variáveis temporárias
        node *x = lista->cabeca;
        int chave = novo->chave;

        while (x != NULL && chave > x->chave) {
            x = x->prox;
        }
        /*
        Quando o while é interrompido, 'x' guarda a posição do elemento imediatamente após à posição na qual a chave deve ser inserida. Por exemplo, se a lista contém 5, 7 e 9, 'x' possuíra o endereço de 9.
        */

        // Caso 1: o novo é o primeiro item da lista
        if (x == lista->cabeca) {
            novo->prox = lista->cabeca;
            lista->cabeca->ante = novo;
            lista->cabeca = novo;
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
void remover_node (ldll *lista, int chave) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }
    
    // Lista vazia
    if (lista->cabeca == NULL) { 
        return;
    }
    
    node *x = lista->cabeca;

    // Procurando a chave a ser excluída
    while (x != NULL && x->chave != chave) { 
        x = x->prox;
    }

    // Chave encontrada
    if (x != NULL) {
        
        // A chave buscada é a cabeça da lista
        if (x == lista->cabeca) {
            
            // Lista unitária
            if (x->prox == NULL) {
                lista->cabeca = NULL;
                lista->cauda = NULL;
            }

            // Lista com múltiplos elementos
            else {
                lista->cabeca = x->prox;
                lista->cabeca->ante = NULL;
            }
        }

        // A chave buscada é a cauda da lista
        else if (x == lista->cauda) {
            lista->cauda = x->ante;
            lista->cauda->prox = NULL;
        }

        // A chave buscada é um elemento intermediário
        else {
            x->ante->prox = x->prox; // O "ante" do atual aponta para o "prox" do atual
            x->prox->ante = x->ante; // O "prox" do atual aponta para o "ante" do atual
        }

        free(x);
    }
}

// Função para ordenar a lista duplamente ligada
void bubbleSort(ldll *lista) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }

    // Lista vazia ou com apenas um nó
    if (lista->cabeca == NULL || lista->cabeca->prox == NULL) {
        return;  // Não há necessidade de ordenar
    }

    int trocou;
    node *i, *j;
    
    // Percorrer a lista para ordenar
    do {
        trocou = 0;
        i = lista->cabeca;

        // Comparar os nós adjacentes
        while (i != NULL && i->prox != NULL) {
            j = i->prox;
            if (i->chave > j->chave) {
                // Trocar os valores das chaves
                int temp = i->chave;
                i->chave = j->chave;
                j->chave = temp;
                
                // Marcar que houve uma troca
                trocou = 1;
            }
            i = i->prox;
        }
    } while (trocou == 1);  // Repetir enquanto houver troca
}

// Função para ordenar a lista duplamente ligada com Insertion Sort
void insertionSort(ldll *lista) {
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }

    // Lista vazia ou com apenas um nó
    if (lista->cabeca == NULL || lista->cabeca->prox == NULL) {
        return;  // Não há necessidade de ordenar
    }

    node *atual = lista->cabeca->prox;  // Começa do segundo nó
    while (atual != NULL) {
        node *chave = atual;
        node *anterior = chave->ante;
        
        // Move a chave para a posição correta
        while (anterior != NULL && chave->chave < anterior->chave) {
            // Trocar as chaves dos nós
            int temp = chave->chave;
            chave->chave = anterior->chave;
            anterior->chave = temp;

            // Mover para o nó anterior
            chave = anterior;
            anterior = chave->ante;
        }

        // Passa para o próximo nó
        atual = atual->prox;
    }
}

// Busca sequencial
void buscaSequencial (ldll *lista, int chave) {

    // Lista vazia
    if (lista->cabeca == NULL) { 
        printf("Lista vazia.\n");
        return;
    }

    // Busca a chave
    node *atual = lista->cabeca;
    while (atual != NULL) {
        // Chave encontrada
        if (atual->chave == chave) {
            printf("Chave: %d\n", atual->chave);
            return;
        }

        atual = atual->prox;
    }

    // Chave não encontrada
    printf("Chave não encontrada.\n");
}

// Busca sequencial ordenada
void buscaSequencialOrdenada (ldll *lista, int chave) {

    // Lista vazia
    if (lista->cabeca == NULL) { 
        printf("Lista vazia.\n");
        return;
    }

    // Busca a chave
    node *atual = lista->cabeca;
    while (atual != NULL && chave >= atual->chave) {
        // Chave encontrada
        if (atual->chave == chave) {
            printf("Chave: %d\n", atual->chave);
            return;
        }
        atual = atual->prox;
    }

    printf("Chave não encontrada.\n");
}

// Imprime a lista
void imprimir_lista (ldll *lista) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }
    
    // Lista vazia
    if (lista->cabeca == NULL) { 
        printf("A lista está vazia.\n");
        return;
    }
    
    node *x = lista->cabeca; // Inicializa x com a "cabeca" da lista
    printf("\n(NULL)"); // Início da lista
    while (x != NULL) {
        printf("<- (%d) ->", x->chave);
        x = x->prox;
    }
    printf(" (NULL)\n\n"); // Fim da lista
}

// Função para liberar a lista e seus nós
void liberar_lista(ldll *lista) {
    
    // Falha de alocação
    if (lista == NULL) {
        printf("Memória não alocada para a lista.\n");
        return;
    }
    
    node *x = lista->cabeca;
    while (x != NULL) {
        node *temp = x;
        x = x->prox;
        free(temp); // Libera a memória de cada nó
    }

    free(lista); // Libera a memória da lista
}

int main(){
    ldll *lista = init_lista();

    /*
    inserir_node(lista, init_node(20));
    inserir_node(lista, init_node(37));
    inserir_node(lista, init_node(18));
    inserir_node(lista, init_node(40));
    inserir_node(lista, init_node(18));
    inserir_node(lista, init_node(100));
    imprimir_lista(lista);

    printf("Lista ordenada\n");
    insertionSort(lista);
    imprimir_lista(lista);

    remover_node(lista, -1);
    printf("Depois\n");
    imprimir_lista(lista);
    remover_node(lista, 40);
    printf("Depois\n");
    imprimir_lista(lista);
    remover_node(lista, 20);
    printf("Depois\n");
    imprimir_lista(lista);
    remover_node(lista, 100);
    printf("Depois\n");
    imprimir_lista(lista);
    */

    inserir_node_ordenado(lista, init_node(20));
    inserir_node_ordenado(lista, init_node(37));
    inserir_node_ordenado(lista, init_node(18));
    inserir_node_ordenado(lista, init_node(40));
    inserir_node_ordenado(lista, init_node(18));
    inserir_node_ordenado(lista, init_node(-1));

    imprimir_lista(lista);
    remover_node(lista, -1);
    printf("Depois\n");
    imprimir_lista(lista);
    remover_node(lista, 40);
    printf("Depois\n");
    imprimir_lista(lista);
    remover_node(lista, 20);
    printf("Depois\n");
    imprimir_lista(lista);
    remover_node(lista, 100);
    printf("Depois\n");
    imprimir_lista(lista);

    // Libera a memória alocada para todos os nós e para a lista
    liberar_lista(lista);
    lista = NULL;
}