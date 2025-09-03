#include <stdio.h>
#include <stdlib.h>
#include "q002.h"

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

// Função que retorna a árvore espelho
TAB* espelho(TAB* a) {
    if (!a) return NULL; // caso base
    // Cria nó novo, mas troca esquerda por direita
    TAB* novo = (TAB*)malloc(sizeof(TAB));
    novo->info = a->info;
    novo->esq = espelho(a->dir); // espelha direita no lugar da esquerda
    novo->dir = espelho(a->esq); // espelha esquerda no lugar da direita
    return novo;
}
//Uso: TAB* arv_espelho = espelho(arv);