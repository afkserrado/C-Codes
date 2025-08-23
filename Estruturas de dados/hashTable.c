// ## Hash Table com Endereçamento Fechado e Expansão Dinâmica ##

#include <stdio.h>
#include <stdlib.h>

// Constantes e variáveis globais
int tamTab = 5; // Tamanho inicial da tabela
#define ocupMax 0.80 // Taxa de ocupação máxima da tabela

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
    int qtdMat; // Quantidade de matrículas cadastradas
    int capacidade; // Quantidade de espaços disponíveis
} HashTable;

// Cabeçalho
HashTable *init_hash ();
unsigned int hash (int capacidade, long int matricula);
unsigned int ProbingLinear (int capacidade, unsigned int index, int i);
int insere (HashTable *tabela, long int matricula);
void redimensiona (HashTable *tabela);
int busca (HashTable *tabela, long int matricula);
long int removeMat (HashTable *tabela, long int matricula);
void reorganiza(HashTable *tabela, int probeIndex);

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
    tabela->matriculas = (long int *)malloc(sizeof(long int) * tamTab);

    // Verifica a alocação de memória
    if (tabela->matriculas == NULL) {
        printf("Não foi possível alocar memória para as matrículas.\n");
        return NULL;
    }

    // Inicializa a tabela com valores inválidos
    for (int i = 0; i < tamTab; i++) {
        tabela->matriculas[i] = -1;
    }

    tabela->capacidade = tamTab;
    tabela->qtdMat = 0;

    return tabela;
}

// Função hash: aplica módulo 20 para determinar os índices
unsigned int hash (int capacidade, long int matricula) {
    return matricula % capacidade;
}

// Calcula um novo índice em caso de colisão
unsigned int ProbingLinear (int capacidade, unsigned int index, int i) {
    return (index + i) % capacidade;
}

// Função para inserir uma matrícula na hash table
int insere (HashTable *tabela, long int matricula) {  
    unsigned int index = hash(tabela->capacidade, matricula);

    // Verifica se a tabela está cheia
    float txOcup = (float)tabela->qtdMat / tabela->capacidade;
    if (txOcup >= ocupMax) {
        redimensiona(tabela);
    }

    // Probing Linear para gerenciamento de colisões
    for (int i = 0; i < tabela->capacidade; i++) {
        unsigned int probeIndex = ProbingLinear(tabela->capacidade, index, i);

        // Index vazio
        if (tabela->matriculas[probeIndex] == -1) {
            tabela->matriculas[probeIndex] = matricula;
            tabela->qtdMat++;
            return SUCESSO;
        }

        if (tabela->matriculas[probeIndex] == matricula) {
            return EXISTE; // Matrícula já cadastrada
        }
    }

    return TABELA_CHEIA;
}
 
// Redimensiona a tabela quando a txOcup chega no limite
void redimensiona (HashTable *tabela) {
    int capacidadeAntiga = tabela->capacidade;
    int capacidadeNova;
    
    // Dobra a capacidade da tabela
    capacidadeNova = capacidadeAntiga * 2;
     
    // Realoca espaço
    long int *novaTabela = (long int *)realloc(tabela->matriculas, sizeof(long int) * capacidadeNova);

    // Verifica a alocação de memória
    if (novaTabela == NULL) {
        printf("Não foi possível realocar memória para as matrículas.\n");
        return;
    }

    // Reinicializa os campos da tabela
    tabela->matriculas = novaTabela;
    tabela->capacidade = capacidadeNova;
    tabela->qtdMat = 0;

    // Inicializa os novos espaços da tabela com -1 (vazio)
    for (int i = tabela->capacidade / 2; i < tabela->capacidade; i++) {
        tabela->matriculas[i] = -1;
    }

    // Re-hash dos elementos existentes (redistribuição)
    for (int i = 0; i < capacidadeAntiga; i++) {
        if (tabela->matriculas[i] != -1) {
            long int matricula = tabela->matriculas[i]; // Guarda a matrícula
            tabela->matriculas[i] = -1; // Remove o elemento temporariamente
            insere(tabela, matricula); // Reinsere o elemento
        }
    }
}

// Função para buscar uma matrícula na hash table
int busca (HashTable *tabela, long int matricula) {
    unsigned int index = hash(tabela->capacidade, matricula);

    // Rehash com Probing Linear para buscar a matrícula pelo index
    for (int i = 0; i < tabela->capacidade; i++) {
        unsigned int probeIndex = ProbingLinear(tabela->capacidade, index, i);

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

long int removeMat (HashTable *tabela, long int matricula) {
    int probeIndex = busca(tabela, matricula);

    // Matrícula não encontrada
    if (probeIndex == NAO_EXISTE) {
        return NAO_EXISTE;
    }

    // Matrícula encontrada
    tabela->matriculas[probeIndex] = -1; // Remove a matrícula
    int qtdMat_Inicial = tabela->qtdMat; // Guarda a qtd de elementos antes da remoção

    // Reorganiza os elementos deslocados
    reorganiza(tabela, probeIndex);

    // Atualiza a qtd de matrículas na tabela
    tabela->qtdMat = qtdMat_Inicial - 1;

    return matricula;
}

/*void reorganiza (HashTable *tabela, long int matricula, int indexAtual) {
    // Recalcula o índice inicial da matrícula removida    
    unsigned int indexInicial = hash(tabela->capacidade, matricula);

    // Percorre os elementos que estão em posições após o removido
    for (int i = indexAtual + 1; i < tabela->capacidade; i++) {
        unsigned int probeIndex = ProbingLinear(tabela->capacidade, indexInicial, i);

        // Verifica se algum elemento foi deslocado
        // Se matriculas[probeIndex] == -1, não houve colisão
        // Isto é, não houve realocação/deslocamento de elemento nessa posição
        if (tabela->matriculas[probeIndex] == -1) {
            break; // Não há mais elementos deslocados
        }

        // Calcula o index original da matrícula
        unsigned indexOriginal = hash(tabela->capacidade, tabela->matriculas[probeIndex]);

        // Verifica se o elemento foi deslocado e precisa ser realocado
        if (indexOriginal != probeIndex) {
            // Guarda a matrícula deslocada e remove temporariamente da tabela
            long int matriculaMovida = tabela->matriculas[probeIndex];
            tabela->matriculas[probeIndex] = -1;
            tabela->qtdMat--;
            
            // Insere a matrícula deslocada no índice correto
            insere(tabela, matriculaMovida);
        }
    }
}*/

void reorganiza (HashTable *tabela, int indexAtual) {
    // Percorre as posições subsequentes ao elemento removido, de forma linear
    for (int i = indexAtual + 1; i < tabela->capacidade; i++) {
        if (tabela->matriculas[i] == -1) {
            break; // Não há mais elementos. A partir daqui, todos os índices estão vazios
        }
        
        // Calcula o índice ideal deste elemento
        int indexIdeal = hash(tabela->capacidade, tabela->matriculas[i]);
        
        // Se o elemento não está no seu lugar ideal
        if (i != indexIdeal) {
            long int matriculaMovida = tabela->matriculas[i]; // Guarda a matrícula
            tabela->matriculas[i] = -1; // Remove a matrícula temporariamente
            tabela->qtdMat--; // Decrementa a qtd temporariamente
            
            // Reinsere a matrícula (se possível, no indexIdeal)
            insere(tabela, matriculaMovida); 
        }
    }
}

// Função para imprimir as matrículas
void imprime (HashTable *tabela) {
    float txOcup = (float)tabela->qtdMat / tabela->capacidade;
    printf("qtdMat = %d | Capacidade = %d | txOcup = %.2f\n", tabela->qtdMat, tabela->capacidade, txOcup);
    for (int i = 0; i < tabela->capacidade; i++) {
        if (tabela->matriculas[i] != -1) {
            printf("Índice %d: %ld\n", i, tabela->matriculas[i]);
        }
    }
}

int main () {

    // Inicializa a hash table
    HashTable *tabela = init_hash();

    long int retorno;

    // Inserindo números de matrícula
    printf("Inserção: \n");
    long int matriculas[] = {12345678901, 12345678901, 12335678901, 23456789012, 34567890123, 45678901234, 12345678905, 12345678906};
    int qtd = sizeof(matriculas) / sizeof(matriculas[0]);

    for (int i = 0; i < qtd; i++) {
        retorno = insere(tabela, matriculas[i]);

        if (retorno == EXISTE) {
            printf("Matrícula %ld já cadastrada.\n", matriculas[i]);
        }
        else if (retorno == TABELA_CHEIA) {
            printf("Tabela cheia. Matrícula %ld não cadastrada.\n", matriculas[i]);
        }
    }

    // Imprimindo a tabela
    imprime(tabela);
    printf("\n");

    // Buscando matrícula
    printf("Busca: \n");
    long int matricula = 23456789012;
    retorno = busca(tabela, matricula);
    if (retorno != NAO_EXISTE) {
        printf("Matrícula %ld encontrada no índice %ld.\n", matricula, retorno);
    } 
    else {
        printf("Matrícula %ld não encontrada.\n", matricula);
    }
    printf("\n");

    // Removendo matrícula
    printf("Remoção: \n");
    matricula = 23456789012;
    retorno = removeMat(tabela, matricula);
    if (retorno != NAO_EXISTE) {
        printf("Matrícula %ld removida.\n", retorno);
        imprime(tabela);
    }
    else {
        printf("Matrícula %ld não encontrada.\n", matricula);
    }    

    // Libera a memória
    free(tabela->matriculas);
    free(tabela);

    return 0;
}