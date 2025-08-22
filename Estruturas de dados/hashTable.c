// ## Hash Table com Endereçamento Fechado

// Expansão dinâmica da tabela hash
/*
1. Att qtd_mat, qtd_disp e recalcular proporcao a cada inserção;
2. Att qtd_mat, qtd_disp e recalcular proporcao a cada remoção;
3. Na inserção, verificar se a proporcao é maior ou igual a 0,90;
    3.1 Se não for, insere normalmente;
    3.2 Se for, chama a função tabela_cheia
        3.2.1 Dobrar o tamanho da tabela com realloc
        3.2.2 Recalcular o hash de todas as matrículas
        ...
*/

#include <stdio.h>
#include <stdlib.h>

// Constantes e variáveis globais
int tam = 20; // Tamanho inicial da tabela

// Tipos enumerados
typedef enum status {
    SUCESSO = 0,
    EXISTE = -1,
    NAO_EXISTE = -2,
    TABELA_CHEIA = -3
} status;

// Estrutura da Hash (endereçamento fechado)
typedef struct HashTable {
    long int *matriculas; // Array para armazenar os números de matrícula
    int qtd_mat; // Quantidade de matrículas cadastradas
    int qtd_disp; // Quantidade de espaços disponíveis
    int proporcao; // qtd_disp / qtd_mat
} HashTable;

// Cabeçalho
HashTable *init_hash ();
unsigned int hash (long int matricula);
unsigned int rehash (unsigned int index, int i);
int insere (HashTable *tabela, long int matricula);
int busca (HashTable *tabela, long int matricula);
int removeMat (HashTable *tabela, long int matricula);

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

unsigned int rehash (unsigned int index, int i) {
    return (index + i) % tam;
}

// Função para inserir uma matrícula na hash table
int insere (HashTable *tabela, long int matricula) {  
    unsigned int index = hash(matricula);

    // Verifica se a tabela está cheia

    // Rehash com Probing Linear para gerenciamento de colisões
    for (int i = 0; i < tam; i++) {
        unsigned int probeIndex = rehash(index, i);

        // Index vazio
        if (tabela->matriculas[probeIndex] == -1) {
            tabela->matriculas[probeIndex] = matricula;
            return SUCESSO;
        }

        if (tabela->matriculas[probeIndex] == matricula) {
            return EXISTE; // Matrícula já cadastrada
        }
    }

    //return TABELA_CHEIA; // Tabela cheia
}
 
// Função para buscar uma matrícula na hash table
int busca (HashTable *tabela, long int matricula) {
    unsigned int index = hash(matricula);

    // Rehash com Probing Linear para buscar a matrícula pelo index
    for (int i = 0; i < tam; i++) {
        unsigned int probeIndex = rehash(index, i);

        // Matrícula encontrada
        if (tabela->matriculas[probeIndex] == matricula) {
            return probeIndex; 
        }

        // Matrícula não cadastrada
        if (tabela->matriculas[probeIndex] == -1) {
            break; // Posição vazia
        }
    }

    return NAO_EXISTE; // Matrícula não encontrada
}

int removeMat (HashTable *tabela, long int matricula) {
    int probeIndex = busca(tabela, matricula);

    // Matrícula não encontrada
    if (probeIndex == NAO_EXISTE) {
        return NAO_EXISTE;
    }

    // Matrícula encontrada
    tabela->matriculas[probeIndex] = -1; // Remove a matrícula
    return EXISTE;
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
    printf("Inserção: \n");
    insere(tabela, 12345678901);
    insere(tabela, 23456789012);
    insere(tabela, 34567890123);
    insere(tabela, 45678901234);
    insere(tabela, 12345678902);
    insere(tabela, 12345678901);

    // Imprimindo a tabela
    imprime(tabela);
    printf("\n");

    // Buscando matrícula
    printf("Busca: \n");
    long int matricula = 23456789012;
    int index = busca(tabela, matricula);
    if (index != NAO_EXISTE) {
        printf("Matrícula %ld encontrada no índice %d\n", matricula, index);
    } else {
        printf("Matrícula %ld não encontrada\n", matricula);
    }
    printf("\n");

    // Removendo matrícula
    printf("Remoção: \n");
    removeMat(tabela, 23456789012);
    imprime(tabela);

    // Libera a memória
    free(tabela->matriculas);
    free(tabela);

    return 0;
}