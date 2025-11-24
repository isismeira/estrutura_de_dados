#include <stdio.h>
#include <stdlib.h>

/*
    Refaça a biblioteca de heap para uma heap com K filhos
*/

int pai(int ind, int k) {
    if (ind > 0) return (ind-1) / k; //!!!
    return -1;
}

// retorna ínidce do r-ésimo filho
int filho_k(int ind, int r, int k) {
    return ind * k + r // !!!
}

void max_heapfy(int *vet, int n, int ind, int k){
    int maior = ind;
    for(int r = 1; r <= k; ++r){  // !!!
        int f = filho_k(ind, r, k);
        if (f < n && vet[f] > vet[maior]) maior = f;
    }
    if (maior != ind){
        int tmp = vet[ind];
        vet[ind] = vet[maior];
        vet[maior] = tmp;
        max_heapfy(vet, n, maior, k);
    }
}


void build_max_heap(int *vet, int n, int k){
    int ultimo_pai = pai(n - 1, k);
    for(int i = ultimo_pai; i >= 0; --i)
        max_heapfy(vet, n, i, k);
}

void heapsort(int *vet, int n, int k){
    build_max_heap(vet, n, k);
    for(int tamanho = n - 1; tamanho >= 1; --tamanho){
        int tmp = vet[0];
        vet[0] = vet[tamanho];
        vet[tamanho] = tmp;
        max_heapfy(vet, tamanho, 0, k);
    }
}
