#include <stdio.h>
#include <stdlib.h>
#include "q009.h"

typedef struct arvbin {
    int info;
    struct arvbin *esq, *dir;
}TAB;

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

int nf(TAB* a) {
    if (!a) return 0;
    
    if (!a->esq && !a->dir)
        return 1;
    
    return nf(a->esq) + nf(a->dir);
}