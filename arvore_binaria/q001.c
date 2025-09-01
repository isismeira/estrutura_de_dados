#include <stdio.h>
#include <stdlib.h>
#include "q001.h"

typedef struct arvbin {
    int info;
    struct arvbin *esq, *dir;
}TAB;

TAB* TAB_inicializa(void) {
    return NULL;
}

// Função que copia a árvore
TAB* copia(TAB* a) {
    if (!a) return NULL; // Caso base: árvore vazia
    TAB* nova = (TAB*)malloc(sizeof(TAB));
    nova->info = a->info;
    nova->esq = copia(a->esq);
    nova->dir = copia(a->dir);
    return nova;
}