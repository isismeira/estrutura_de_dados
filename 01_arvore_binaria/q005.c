#include <stdio.h>
#include <stdlib.h>
#include "q005.h"

typedef struct arvbin {
    int info;
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

TAB* TAB_imp_pre(TAB* a) {
    if (a) {
        printf("%d\n", a->info);
        TAB_imp_pre(a->esq);
        TAB_imp_pre(a->dir);
    }
}

int igual(TAB* a1, TAB* a2) {
    // Caso base: se ambas forem NULL, são iguais
    if (!a1 && !a2) return 1;

    // Se uma for NULL e a outra não, são diferentes
    if (!a1 || !a2) return 0;

    // Se valores diferentes, não são iguais
    if (a1->info != a2->info) return 0;

    // Recursão: ambas as subárvores devem ser iguais
    return igual(a1->esq, a2->esq) && igual(a1->dir, a2->dir);
}