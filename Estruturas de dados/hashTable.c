// ## Hash Table com Endereçamento Fechado

#include <stdio.h>
#include <stdlib.h>

#define tam 20 // Tamanho da tabela

// Estrutura da Hash (endereçamento fechado)
typedef struct HashTable {
    long int *matriculas; // Array para armazenar os números de matrícula
} HashTable;

// Inicializa a tabela
HashTable *init_hash () {
    // Aloca memória para a tabela
    HashTable *tabela = (HashTable *)malloc(sizeof(HashTable));
    
    // Verifica a alocação de memória
    if (tabela == NULL) {
        printf("Não foi possível alocar memória para a tabela.\n");
        return NULL;
    }

    // Aloca memória para as matrículas da tabela   
    tabela->matriculas = (long int *)malloc(sizeof(long int) * tam);

    // Verifica a alocação de memória
    if (tabela->matriculas == NULL) {
        printf("Não foi possível alocar memória para as matrículas.\n");
        return NULL;
    }

    // Inicializa a tabela com valores inválidos
    for (int i = 0; i < tam; i++) {
        tabela->matriculas[i] = -1;
    }

    return tabela;
}

// Função hash: aplica módulo 20 para determinar os índices
unsigned int hash (long int matricula) {
    return matricula % tam;
}

// Função para inserir uma matrícula na hash table
int insere (HashTable *tabela, long int matricula) {
    unsigned int index = hash(matricula);

    // Rehash com Probing Linear para gerenciamento de colisões
    for (int i = 0; i < tam; i++) {
        int probeIndex = (index + i) % tam;

        // Index vazio
        if (tabela->matriculas[probeIndex] == -1) {
            tabela->matriculas[probeIndex] = matricula;
            return 0;
        }
    }

    return -1; // Tabela cheia
}
 
// Função para imprimir as matrículas
void imprime (HashTable *tabela) {
    for (int i = 0; i < tam; i++) {
        if (tabela->matriculas[i] != -1) {
            printf("Índice %d: %ld\n", i, tabela->matriculas[i]);
        }
    }
}

int main () {

    // Inicializa a hash table
    HashTable *tabela = init_hash();

    // Inserindo números de matrícula
    insere(tabela, 12345678901);
    insere(tabela, 23456789012);
    insere(tabela, 34567890123);
    insere(tabela, 45678901234);
    insere(tabela, 12345678902);
    insere(tabela, 12345678901);

    // Imprimindo a tabela
    imprime(tabela);

    return 0;
}