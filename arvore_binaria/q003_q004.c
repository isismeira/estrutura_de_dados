#include <stdio.h>
#include <stdlib.h>
#include "q003_q004.h"

TAB* TAB_inicializa(void) {
    return NULL;
}

TAB* TAB_cria(int raiz, TAB* esq, TAB* dir)  {
    TAB* novo = (TAB*)malloc(sizeof(TAB));
    novo->info = raiz;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

void TAB_imp_pre(TAB* a) {
    if(a) {
        printf("%d\n", a->info);
        TAB_imp_pre(a->esq);
        TAB_imp_pre(a->dir);
    }
}

TAB* maior(TAB* a) {
    if (!a) return NULL;

    TAB* max_esq = maior(a->esq);
    TAB* max_dir = maior(a->dir);

    TAB* max = a; // começa assumindo que o próprio nó é o maior

    if (max_esq && max_esq->info > max->info)
        max = max_esq;

    if (max_dir && max_dir->info > max->info)
        max = max_dir;

    return max;
}

TAB* menor(TAB* a) {
    if (!a) return NULL;

    TAB* min_esq = menor(a->esq);
    TAB* min_dir = menor(a->dir);

    TAB* min = a;

    if (min_esq && min_esq->info < min->info) {
        min = min_esq;
    }
    if (min_dir && min_dir->info < min->info) {
        min = min_dir;
    }

    return min;
}
