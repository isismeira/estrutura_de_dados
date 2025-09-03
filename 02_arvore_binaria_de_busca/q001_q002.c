#include <stdio.h>
#include <stdlib.h>
#include "q001_q002.h"

TABB *TABB_inicializa(void){
  return NULL;
}

TABB *TABB_cria(int raiz, TABB *esq, TABB *dir){
  TABB *novo = (TABB *) malloc(sizeof(TABB));
  novo->info = raiz;
  novo->esq = esq;
  novo->dir = dir;
  return novo;
}

void TABB_imp_sim(TABB *a){ // obs. esse imprime os elementos em ordem crescente
  if(a){
    TABB_imp_sim(a->esq); 
    printf("%d ", a->info);
    TABB_imp_sim(a->dir);
  }
}

TABB* maior(TABB* a) {
    if (!a || !a->dir) 
        return a;
    else
        return maior(a->dir);
}

TABB* menor(TABB* a) {
    if(!a || !a->esq)
        return a;
    else
        return menor(a->esq);    
}