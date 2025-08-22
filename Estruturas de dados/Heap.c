// ## Max Heap ## 

#include <stdio.h>
#include <stdlib.h>

#define max 11 // 10 + 1 (índice 0, que é desprezado)

// Funções do heap
void troca (int *x, int *y);
int filhoEsq (int i);
int filhoDir (int i);
void HeapInsere (int heap[], int num, int *n);
void HeapSobe (int heap[], int i);
void HeapImprime (int heap[], int n);
int HeapRemove (int heap[], int *n);
void Heapfy (int heap[], int i, int n);
void ConstroiHeap (int heap[], int n);

void troca (int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Calcula a posição do pai de um elemento na posição i
int pai (int i) {
    return i / 2;
}

// Calcula o filho esquerdo de um elemento na posição i
int filhoEsq (int i) {
    return 2 * i;
}

// Calcula o filho direito de um elemento na posição i
int filhoDir (int i) {
    return 2 * i + 1;
}

// Insere um elemento no Heap
void HeapInsere (int heap[], int num, int *n) {
    // Heap cheio
    if (*n >= max) {
        printf("Heap cheio!\n");
        return;
    }
    
    (*n)++; // Incrementa o tamanho da heap
    heap[*n] = num; // Insere no final da heap
    HeapSobe(heap, *n); // Mantém a propriedade do Max Heap

    /*
    Obs.: no Heap o índice inicia na posição 1. Por isso o tamanho do Heap é incrementado antes da inserção do novo elemento no vetor. Isso é necessário para simplificar o cálculo dos índices (pai e filhos). Portanto, a raiz do Heap ocupa o índice 1 e o índice 0 sempre é desprezado.
    */
}

// Mantém a propriedade do Max Heap após a inserção
void HeapSobe (int heap[], int i) {
    int j = pai(i); // Pai do elemento recém-inserido
    
    // Verifica se o elemento na posição i é não-raiz
    if (i > 1) {
        // Pai é menor que o filho
        if (heap[j] < heap[i]) {
            troca(&heap[j], &heap[i]); // Sobe o filho
            HeapSobe(heap, j); // Chamada recursiva
        }
    }
}

// Remove um elemento do Heap
int HeapRemove (int heap[], int *n) {
    // Heap vazio
    if (*n <= 0) {
        printf("Heap vazio!\n");
        return -1;
    }
    
    // Elemento a ser removido
    int raiz = heap[1];

    // Troca o primeiro e último elementos de posição
    heap[1] = heap[*n]; // Coloca o último elemento na raiz
    heap[*n] = raiz; // Coloca a raiz no final
    (*n)--; // Exclusão lógica

    Heapfy(heap, 1, *n); // Mantém a propriedade do Max Heap
    return raiz;
}

// Mantém a propriedade do Max Heap após a exclusão
void Heapfy (int heap[], int i, int n) {
    int esq = filhoEsq(i);
    int dir = filhoDir(i);
    int maior = i;

    // Filho esquerdo é maior que o pai
    if (esq <= n && heap[esq] > heap[i]) {
        maior = esq;
    }

    // Filho direito é maior que o pai ou o filho esquerdo
    if (dir <= n && heap[dir] > heap[maior]) {
        maior = dir;
    }

    if (maior != i) {
        troca(&heap[maior], &heap[i]); // Sobe o filho
        Heapfy(heap, maior, n); // Chamada recursiva
    }
}

// Reorganiza um vetor inteiro para que ele siga a propriedade do Max Heap
void ConstroiHeap (int A[], int n) {
    for (int i = n/2; i >= 1; i--) { // Começa do meio do vetor até a raiz
        Heapfy(A, i, n); // Aplica o Heapfy em cada nó
    }
}

// Ordena o vetor
void HeapSort (int V[], int n) {
    // Constrói o Max Heap
    ConstroiHeap(V, n);

    // Ordena o vetor
    for (int i = n; i >= 1; i--) {
        troca(&V[1], &V[i]); // Troca a raiz (maior) com o último elemento
        n--; // Reduz o tamanho do Heap
        Heapfy(V, 1, n); // Mantém a propriedade do do Max Heap
    }
}

// Ordena o vetor
void HeapSort2 (int V[], int *n) {
    // Constrói o Max Heap
    ConstroiHeap(V, *n);

    // Ordena o vetor
    for (int i = *n; i >= 1; i--) {
        HeapRemove(V, n);
    }
}

// Exibir o conteúdo do Heap
void HeapImprime (int heap[], int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main () {
    int heap[max];
    int A[max] = {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int V[max] = {-1, 1, 4, 2, 3, 9, 7, 8, 10, 14, 16};
    int Z[max] = {-1, 1, 4, 2, 3, 9, 7, 8, 10, 14, 16};
    int tam = 0; // Tamanho da heap

    // Inserindo elementos no Heap
    HeapInsere(heap, 1, &tam);
    HeapInsere(heap, 4, &tam);
    HeapInsere(heap, 2, &tam);
    HeapInsere(heap, 3, &tam);
    HeapInsere(heap, 9, &tam);
    HeapInsere(heap, 7, &tam);
    HeapInsere(heap, 8, &tam);
    HeapInsere(heap, 10, &tam);
    HeapInsere(heap, 14, &tam);
    HeapInsere(heap, 16, &tam);

    printf("Heap após inserções: ");
    HeapImprime(heap, tam);

    // Removendo o maior elemento (raiz)
    int raiz = HeapRemove(heap, &tam);
    printf("Elemento removido: %d\n", raiz);
    printf("Heap após remoção: ");
    HeapImprime(heap, tam);

    // Heapyfica um vetor qualquer
    int n = sizeof(A)/sizeof(A[0]) - 1; // Qtd de elementos do vetor A, desprezando i = 0
    printf("Vetor A antes do Heapfy: ");
    HeapImprime(A, n);
    ConstroiHeap(A, n);
    printf("Vetor A após o Heapfy: ");
    HeapImprime(A, n);
    printf("\n");

    // Ordena o vetor
    n = sizeof(V)/sizeof(V[0]) - 1; // Qtd de elementos do vetor V, desprezando i = 0
    printf("Heap Sort sem HeapRemove: \n");
    printf("Vetor V antes do Heap Sort 1: ");
    HeapImprime(V, n);
    HeapSort(V, n);
    printf("Vetor V após o Heap Sort 1: ");
    HeapImprime(V, n);
    printf("\n");

    // Ordena o vetor com o HeapSort2, que utiliza o HeapRemove
    n = sizeof(Z)/sizeof(Z[0]) - 1; // Qtd de elementos do vetor Z, desprezando i = 0
    int m = n; // Conserva a qtd de elementos do vetor Z
    printf("Heap Sort com HeapRemove: \n");
    printf("Vetor Z antes do Heap Sort 2: ");
    HeapImprime(Z, n);
    HeapSort2(Z, &n);
    printf("Vetor Z após o Heap Sort 2: ");
    HeapImprime(Z, m);

    return 0;
}