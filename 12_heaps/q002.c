#include <stdio.h>
#include <stdlib.h>

/*
Generalize as operações de heaps binários de máximo para heaps ternários de
mínimo - int filho (int indice, int pos), onde pos {1,2,3} ∈ , int pai (int
indice) e void min_heapfy (int* heap, int n, int indice), onde os métodos
esquerda e direita são as operações filho (pos, 1) e filho(pos, 2), respectivamente.
*/

int pai(int ind) {
    if (ind > 0) return (ind - 1)/3;
    return -1;
}

int filho_k(int ind, int k) {
    return (ind * 3) + k;
}

void min_heapfy(int* vet, int n ,int ind) {
    int menor = ind, filho_1 = filho_k(ind,1), filho_2 = filho_k(ind,2), filho_3 = filho(ind, 3);
    if (filho_1 < n && vet[filho_1] < vet[ind]) menor = filho_1;
    if (filho_2 < n && vet[filho_2] < vet[menor]) menor = filho_2;
    if (filho_3 < n && vet[filho_3] < vet[menor]) menor = filho_3;
    if (menor != ind) {
        int temp = vet[ind];
        vet[ind] = vet[menor];
        vet[menor] = temp;
        min_heapfy(vet, n, menor);
    }
}

void build_min_heap(int* vet, int n) {
    int ultimo_pai = pai(n-1);
    for (int i = ultimo_pai; i >= 0; i--) {
        min_heapfy(vet,n,i);
    }
} 

void heapsort(int* vet, int n) {
    build_min_heap(vet,n);
    for (int i = n-1; i >= 1; i--) {
        int temp = vet[i];
        vet[i] = vet[0];
        vet[0] = temp;
        min_heapfy(vet,i,0);
    }
}