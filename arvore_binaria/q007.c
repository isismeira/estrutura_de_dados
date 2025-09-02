#include <stdio.h>
#include <stdlib.h>
#include "q007.h"

typedef struct arvbin {
    int info;
    int cor; // 0 = preto, 1 = vermelho
    struct arvbin *esq, *dir;
}TAB;

TAB* TAB_inicializa(void) {
    return NULL;
}

TAB* TAB_cria(int raiz, TAB* esq, TAB* dir){
    TAB* novo = (TAB*)malloc(sizeof(TAB));
    novo->info = raiz;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

void TAB_imp_pre(TAB* a) {
    if (a) {
        printf("%d\n", a->info);
        TAB_imp_pre(a->esq);
        TAB_imp_pre(a->dir);
    }
}

void colore_aux(TAB* arv, int cor) {
    if (!arv) return;

    // atribui cor ao nó atual
    arv->cor = cor;

    // chama recursivamente para filhos com cor oposta
    colore_aux(arv->esq, 1 - cor);
    colore_aux(arv->dir, 1 - cor);
}

void colore(TAB* arv) {
    // começa pela raiz com a cor preta (0)
    colore_aux(arv, 0);
}