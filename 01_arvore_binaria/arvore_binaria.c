#include <stdio.h>
#include <stdlib.h>
#include "arvore_binaria.h"

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

TAB* v2ab(int *vet, int n) {
    if(n<=0) return NULL;
    return TAB_cria(vet[n/2],
         v2ab(vet, n/2),
         v2ab(vet[n/2 + 1], n - n/2 - 1));
}

// 1) Percorrimento pré-ordem (prefixada): RAIZ ESQ DIR
void TAB_imp_pre(TAB* a) {
    if(a) {
        printf("%d\n", a->info);
        TAB_imp_pre(a->esq);
        TAB_imp_pre(a->dir);
    }
}

// 2) Percorrimento simétrico: ESQ RAIZ DIR
void TAB_imp_sim(TAB* a){
    if(a) {
        TAB_imp_sim(a->esq);
        printf("%d\n", a->info);
        TAB_imp_sim(a->dir);
    }
}

// 3) Percorrimento pós-ordem (pós-fixado): ESQ DIR RAIZ
void TAB_imp_pos(TAB* a) {
    if(a) {
        TAB_imp_pos(a->esq);
        TAB_imp_pos(a->dir);
        printf("%d\n", a->info);
    }
}

// 4) Percorrimento por nível (precisa de estrutura auxiliar de fila)
/*
void TAB_imp_nivel(TAB* a) {
    if (!a) return;
    TF* f = TF_cria();
    TF_insere(f,a);
    while(!TF_vazia(f)) {
        TAB* aux = TF_retira(f);
        printf("%d\n", aux->info);
        if(aux->esq) TF_insere(f,aux->esq);
        if(aux->dir) TF_insere(f,aux->dir);
    }
    TF_libera(f);
}
*/

void TAB_libera(TAB* a) {
    if(a) {
        TAB_libera(a->esq);
        TAB_libera(a->dir);
        free(a);
    }
}

TAB* TAB_busca(TAB* a, int x) {
    if((!a) || (a->info == x))
        return a;
    TAB* resp = TAB_busca(a->esq,x);
    if(resp) return resp;
    return TAB_busca(a->dir, x);   
}

int nivel(TAB* a, int x) {
    if(!a) return -1;
    return naux(a, x, 0);
}

int naux(TAB *a, int x, int resp) {
    if(!a) return -1;
    if(a->info==x) return resp;
    int e, d;
    e =naux(a->esq, x, resp + 1);
    if(e > 0) return e;
    d = naux(a->dir, x, resp + 1);
    return d;

}