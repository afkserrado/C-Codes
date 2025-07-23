#include <stdio.h>
#include <stdlib.h>

// ##################################################### //
// ÁRVOR BINÁRIA DE BUSCA (ABB) DO TIPO ADELSON-VELSKY AND LANDIS (AVL)

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

// Atualiza a altura de toda a árvore
void calc_alt_arvore(no *x) {
    if (x == NULL) {return;}

    // Percorre a árvore recursivamente em pós-ordem, começando pela raiz
    calc_alt_arvore(x->esq);
    calc_alt_arvore(x->dir);
    calc_alt_no(x);
}

// Atualiza a altura de um nó específico com base nos filhos
void calc_alt_no(no *x) {
    if (x == NULL) return;
    
    int alt_esq = (x->esq != NULL) ? x->esq->altura : -1;
    int alt_dir = (x->dir != NULL) ? x->dir->altura : -1;
    
    x->altura = 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

// Atualiza a altura de todos os nós ancestrais
void calc_alt_ancestrais(no *mae_no) {
    while (mae_no != NULL) {
        int altura_anterior = mae_no->altura;
        calc_alt_no(mae_no);
        
        // Se a altura não mudou, os ancestrais também não mudam
        if (mae_no->altura == altura_anterior) {
            break;
        }
        
        mae_no = mae_no->mae;
    }
}

// Calcula o fator de balanceamento do nó (dir - esq)
int calc_fb_no (no *x) {
    int alt_esq = (x->esq != NULL) ? x->esq->altura : -1;
    int alt_dir = (x->dir != NULL) ? x->dir->altura : -1;

    return alt_dir - alt_esq; // Diferença entre as alturas das subárvores
}

// Rotação simples à direita
void rt_dir(arvore *arv, no *v) {
    no* u = v->esq;
    no* t = u->dir; 

    // Rotação
    u->dir = v; // v se torna filho direito de u
    v->esq = t; // t se torna filho esquerdo de v
    v->mae = u; // u se torna mãe de v

    if (t != NULL) {
        t->mae = v; // v se torna mãe de t
    }

    // Atualiza a raiz da árvore
    if (v->mae == NULL) {
        arv->raiz = u;
    }

    // Atualiza as alturas
    calc_alt_no(v);
    calc_alt_no(u);
}

// Balanceia a árvore
void balancear_arvore (arvore *arv, no *x) {
    while (x != NULL) {
        int fb = calc_fb_no(x);

        // Caso 1: desbalanceamento à esquerda (fb < -1)
        if (fb < -1 && calc_fb_no(x->esq) <= 0) {
            //Rotação simples à direita
            rt_dir(arv, x);
        }

        // Caso 2: desbalanceamento à direita (fb > 1)
        else if (fb > 1 && calc_fb_no(x->dir) >= 0) {
            // Rotação simples à esquerda
            rt_esq(arv, x);
        }

        // Caso 3: rotação dupla esquerda-direita
        else if (fb < -1 && calc_fb_no(x->esq) > 0) {
            rt_esq_dir(arv, x);
        }

        // Caso 4: rotação dupla direita-esquerda
        else if (fb > 1 && calc_fb_no(x->dir) < 0) {
            rt_dir_esq(arv, x);
        }

        // Move x para o próximo ancestral
        x = x->mae;
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

    // Recalcula altura dos ancestrais a partir da mãe do novo nó
    calc_alt_ancestrais(mae);

    // Calcula o fator de balanceamento
    balancear_arvore(arv, mae);
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

// Exclui um nó da árvore
void remover_no (arvore *arv, int chave, int flagImprimir) {
    no *alvo = buscar_no(arv->raiz, chave); // Busca o nó a remover

    // Caso 1: chave não encontrada
    if (alvo == NULL) {
        printf("Elemento %d não encontrado na árvore.\n", chave);
        return;
    }

    // Guarda a mãe do alvo para atualizar as alturas
    no *mae_alvo = alvo->mae;

    // Caso 2: nó sem filhos: apenas remove
    if (alvo->esq == NULL && alvo->dir == NULL) {
        
        // Alvo é a raiz
        if (mae_alvo == NULL) {
            arv->raiz = NULL;
        }
        // Alvo não é a raiz
        else {
            if (mae_alvo->esq == alvo) {
                mae_alvo->esq = NULL;
            }
            else {
                mae_alvo->dir = NULL;
            }
        }
        
        free(alvo);
    }

    // Caso 3: nó com apenas um filho: o filho assume o lugar da mãe
    else if (alvo->esq == NULL || alvo->dir == NULL) {
        
        no *filho_alvo;

        // Filho da direita assume o lugar do alvo
        if (alvo->esq == NULL) {
            filho_alvo = alvo->dir;
        } 
        // Filho da esquerda assume o lugar do alvo
        else {
            filho_alvo = alvo->esq;
        } 
        
        // Alvo é a raiz
        if (mae_alvo == NULL) {
            arv->raiz = filho_alvo;
        }
        // Alvo não é a raiz
        // Mãe do alvo aponta para o filho do alvo
        else { 
            if (mae_alvo->esq == alvo) {
                mae_alvo->esq = filho_alvo; 
            }
            else {
                mae_alvo->dir = filho_alvo;
            }
        }

        filho_alvo->mae = mae_alvo; // Filho do alvo aponta para a mãe do alvo
        
        free(alvo);
    }

    // Caso 4: nó com mais de um filho: o sucessor em ordem assume o lugar do alvo
    else {
        no *sucessor = alvo->dir;

        // Busca o sucessor em ordem: menor chave da subárvore direita do alvo
        while (sucessor->esq != NULL) {
            sucessor = sucessor->esq;
        }

        int temp = sucessor->chave;
        remover_no(arv, temp, 0); // Entra no caso 3
        alvo->chave = temp; // Troca os dados
    }

    // Evita imprimir e recalcular alturas após chamada recursiva no caso 4
    if (flagImprimir == 1) {
        // Libera memória do nó removido
        printf("\nNó removido: %d", chave);

        // Recalcula alturas de TODOS os ancestrais a partir do ponto apropriado
        calc_alt_ancestrais(mae_alvo);
    }
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
    remover_no(arv2, 10, 1);
    printf("\nEM ORDEM (ordem crescente): ");
    imprimir_ordem(arv2->raiz);

    printf("\n\nRemovendo nó com apenas filho à direita (caso 2):");
    inserir_no(arv2, init_no(10));
    remover_no(arv2, 5, 1);
    printf("\nEM ORDEM (ordem crescente): ");
    imprimir_ordem(arv2->raiz);

    printf("\n\nRemovendo folha (caso 1):");
    remover_no(arv2, 13, 1);
    printf("\nEM ORDEM (ordem crescente): ");
    imprimir_ordem(arv2->raiz);

    printf("\n\nRemovendo nó com dois filhos novamente:");
    remover_no(arv2, 15, 1);
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