#include <stdio.h>
#include <stdlib.h>
#include "TARVB/TARVB.h"

typedef struct lse{
  int info;
  struct lse *prox;
}TLSE;

TLSE* TLSE_inicializa(void){
  return NULL;
}

TLSE* TLSE_insere(TLSE *l, int elem){
  TLSE *novo = (TLSE *) malloc(sizeof(TLSE));
  novo->prox = l;
  novo->info = elem;
  return novo;
}

void TLSE_libera(TLSE *l){
  TLSE *p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
}

// ----------------------------------------------------

void mN_aux(TARVB *a, TLSE **l, int N) {  // !!! **l
    if (a) {
        TARVB* p = a;
        int i;
        for (i = 0; i < p->nchaves; i++) {
            if (p->filho[i])
                mN_aux(p->filho[i], l, N);

            if (p->chave[i] < N)
                *l = TLSE_insere(*l, p->chave[i]);   // !!! *l
        }

        if (p->filho[p->nchaves])
            mN_aux(p->filho[p->nchaves], l, N);
    }
}

TLSE* mN(TARVB *a, int N) {
    TLSE* l = TLSE_inicializa();
    mN_aux(a, &l, N); // !!!  &l
    return l;
}
