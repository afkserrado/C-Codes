#include <stdio.h>
#include <stdlib.h>

// ##################################################### //
// ÁRVORE BINÁRIA DE BUSCA (ABB)

// Estrutura do nó da árvore
typedef struct no {
    int chave;
    int altura;
    struct no *esq;
    struct no *dir;
    struct no *mae;
} no;

// Estrutura da árvore
typedef struct arvore {
    no *raiz;
} arvore;

// Inicialização do nó da árvore
no *init_no (int chave) {
    // Alocação de memória
    no *novo = (no *)malloc(sizeof(no));
    
    // Falha de alocação
    if (novo == NULL) {
        printf("Falha de alocação de memória para o nó.\n");
        return NULL;
    }

    // Inicializações
    novo->chave = chave;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->mae = NULL;

    // Retorno
    return novo;
}

// Inicialização da árvore
arvore *init_arvore () {
    // Alocação de memória
    arvore *arv = (arvore *)malloc(sizeof(arvore));
    
    // Falha de alocação
    if (arv == NULL) {
        printf("Falha de alocação de memória para a árvore.\n");
        return NULL;
    }

    // Inicializações
    arv->raiz = NULL;

    // Retorno
    return arv;
}

// Atualiza a altura de um nó específico com base nos filhos
void atualizar_altura_no(no *x) {
    if (x == NULL) return;
    
    int alt_esq = (x->esq != NULL) ? x->esq->altura : -1;
    int alt_dir = (x->dir != NULL) ? x->dir->altura : -1;
    
    x->altura = 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

// Atualiza a altura de todos os nós ancestrais
void atualizar_alturas_ancestrais(no *mae_no) {
    while (mae_no != NULL) {
        int altura_anterior = mae_no->altura;
        atualizar_altura_no(mae_no);
        
        // Se a altura não mudou, os ancestrais também não mudam
        if (mae_no->altura == altura_anterior) {
            break;
        }
        
        mae_no = mae_no->mae;
    }
}

// Insere um novo nó na árvore
void inserir_no (arvore *arv, no *novo) {
    // Inicializações
    no *mae = NULL;
    no *atual = arv->raiz;

    // Busca a posição do novo nó na árvore
    while (atual != NULL) {
        mae = atual; // Salva a mãe

        if (novo->chave < atual->chave) { // Anda para a esquerda do atual nó
            atual = atual->esq;
        }
        else {
            atual = atual->dir; // Anda para a direita do atual nó
        }
    }

    // Vincula a mãe ao filho
    novo->mae = mae;

    // Árvore vazia
    if (mae == NULL) {
        arv->raiz = novo;
    }
    // O novo é o filho da esquerda
    else if (novo->chave < mae->chave) {
        mae->esq = novo;
    }
    // O novo é o filho da direita
    else {
        mae->dir = novo;
    }

    // Inicializa altura do novo nó como 0 (nó folha)
    novo->altura = 0;

    // Recalcula altura de TODOS os ancestrais a partir da mãe do novo nó
    atualizar_alturas_ancestrais(mae);
}

// Busca recursiva na ABB
no *buscar_no (no *raiz, int chave) {
    // Árvore vazia ou apenas com a raiz
    if (raiz == NULL || raiz->chave == chave) {
        return raiz;
    }

    if (chave < raiz->chave) { // Anda para a esquerda da raiz
        return buscar_no(raiz->esq, chave);
    }
    else {
        return buscar_no(raiz->dir, chave); // Anda para a direita da raiz
    }
}

// Encontra o nó com o menor valor em uma subárvore
no *minimo (no *min) {
    while (min->esq != NULL) {
        min = min->esq;
    }
    return min;
}

// Exclui um nó da árvore
void remover_no (arvore *arv, int chave) {
    no *alvo = buscar_no(arv->raiz, chave); // Busca o nó a remover

    // Chave não encontrada
    if (alvo == NULL) {
        printf("Elemento %d não encontrado na árvore.\n", chave);
        return;
    }

    // Chave encontrada
    no *no_removido; // Aponta para o nó que de fato será removido

    // Casos 1 e 2: alvo não tem filho ou tem apenas um filho
    if (alvo->esq == NULL || alvo->dir == NULL) {
        no_removido = alvo;
    // Caso 3: alvo tem dois filhos
    } else {
        // Encontra o sucessor em ordem (menor chave da subárvore à direita do alvo)
        no_removido = minimo(alvo->dir);
    }

    no *filho_do_removido; // Aponta para o filho de no_removido (nó a ser removido) ou para NULL
    if (no_removido->esq != NULL) {
        // Caso 2: no_removido tem apenas filho à esquerda → filho_do_removido será no_removido->esq
        filho_do_removido = no_removido->esq;
    } else {
        // Caso 1: no_removido não tem filhos → no_removido->dir == NULL → filho_do_removido será NULL
        // Caso 2: no_removido tem apenas filho à direita → filho_do_removido será no_removido->dir
        // Caso 3: no_removido (sucessor em ordem) não tem filhos ou tem apenas filho à direita → filho_do_removido será no_removido->dir
        filho_do_removido = no_removido->dir;
    }

    // Se o filho existe, atualiza a sua mãe
    if (filho_do_removido != NULL) {
        filho_do_removido->mae = no_removido->mae;
    }

    // Se o nó a remover for a raiz da árvore
    if (no_removido->mae == NULL) {
        arv->raiz = filho_do_removido;
    }
    // Se ele for filho da esquerda
    else if (no_removido == no_removido->mae->esq) {
        no_removido->mae->esq = filho_do_removido;
    }
    // Se for filho da direita
    else {
        no_removido->mae->dir = filho_do_removido;
    }

    // Se o nó removido for o sucessor em ordem, copia sua chave no lugar do alvo
    if (no_removido != alvo) {
        alvo->chave = no_removido->chave;
    }

    // Salva a mãe do nó que será removido para recalcular alturas depois
    no *mae_do_removido = no_removido->mae;

    // Libera memória do nó removido
    free(no_removido);
    printf("\nNó removido: %d", chave);

    // Recalcula alturas de TODOS os ancestrais a partir do ponto apropriado
    atualizar_alturas_ancestrais(mae_do_removido);
}

// Impressão dos nós in-ordem: ordem crescente dos dados (esquerda, raiz, direita)
void imprimir_ordem (no *x) {
    if (x != NULL) {
        imprimir_ordem(x->esq);
        printf(" %d(h = %d) ", x->chave, x->altura);
        imprimir_ordem(x->dir);
    }
}

// Impressão dos nós em pré-ordem: raiz, esquerda, direita
void imprimir_preordem (no *x) {
    if (x != NULL) {
        printf(" %d(h = %d) ", x->chave, x->altura);
        imprimir_preordem(x->esq);
        imprimir_preordem(x->dir);
    }
}

// Impressão dos nós em pós-ordem: esquerda, direita, raiz
void imprimir_posordem (no *x) {
    if (x != NULL) {
        imprimir_posordem(x->esq);
        imprimir_posordem(x->dir);
        printf(" %d(h = %d) ", x->chave, x->altura);
    }
}

// Libera a memória dos nós
void liberar_no(no *x) {
    if (x != NULL) {
        liberar_no(x->esq);
        liberar_no(x->dir);
        free(x);
    }
}

// Libera a memória dos nós e atribui NULL à raiz
void destruir_arvore(arvore *arv) {
    if (arv != NULL) {
        liberar_no(arv->raiz);
        arv->raiz = NULL;
    }
}

int main() {
    // Inicializa a árvore
    arvore *arv1 = init_arvore();
    arvore *arv2 = init_arvore();

    // Árvore 1
    printf("Árvore 1:\n");
    inserir_no(arv1, init_no(9));
    inserir_no(arv1, init_no(4));
    inserir_no(arv1, init_no(12));
    inserir_no(arv1, init_no(2));
    inserir_no(arv1, init_no(7));
    inserir_no(arv1, init_no(15));

    printf("EM ORDEM (ordem crescente): ");
    imprimir_ordem(arv1->raiz);

    printf("\nPRE-ORDEM (raiz, esquerda, direita): ");
    imprimir_preordem(arv1->raiz);

    printf("\nPOS-ORDEM (esquerda, direita, raiz): ");
    imprimir_posordem(arv1->raiz);

    // Busca por um valor
    int valor_busca = 7;
    no *resultado = buscar_no(arv1->raiz, valor_busca);
    if (resultado != NULL)
        printf("\nElemento %d encontrado na árvore.", valor_busca);
    else
        printf("\nElemento %d não encontrado na árvore.", valor_busca);

    // Árvore 2
    printf("\n");
    printf("\nÁrvore 2:\n");
    inserir_no(arv2, init_no(10));
    inserir_no(arv2, init_no(5));
    inserir_no(arv2, init_no(15));
    inserir_no(arv2, init_no(7));
    inserir_no(arv2, init_no(13));
    inserir_no(arv2, init_no(17));
    inserir_no(arv2, init_no(16));

    printf("EM ORDEM (ordem crescente): ");
    imprimir_ordem(arv2->raiz);

    printf("\nRemovendo a raiz (caso 3 - dois filhos):");
    remover_no(arv2, 10);
    printf("\nEM ORDEM (ordem crescente): ");
    imprimir_ordem(arv2->raiz);

    printf("\n\nRemovendo nó com apenas filho à direita (caso 2):");
    inserir_no(arv2, init_no(10));
    remover_no(arv2, 5);
    printf("\nEM ORDEM (ordem crescente): ");
    imprimir_ordem(arv2->raiz);

    printf("\n\nRemovendo folha (caso 1):");
    remover_no(arv2, 13);
    printf("\nEM ORDEM (ordem crescente): ");
    imprimir_ordem(arv2->raiz);

    printf("\n\nRemovendo nó com dois filhos novamente:");
    remover_no(arv2, 15);
    printf("\nEM ORDEM (ordem crescente): ");
    imprimir_ordem(arv2->raiz);

    printf("\n");

    // Exclui todos os nós
    destruir_arvore(arv2);
    printf("\nRemovendo todos os nós:");
    printf("\nEM ORDEM (ordem crescente): ");
    imprimir_ordem(arv2->raiz);

    printf("\n");

    // Libera os nós e a árvore
    destruir_arvore(arv1);
    free(arv1);
    free(arv2);
    arv1 = NULL;
    arv2 = NULL;

    return 0;
}