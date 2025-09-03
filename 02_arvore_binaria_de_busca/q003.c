#include <stdio.h>
#include <stdlib.h>
#include "q003.h"

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

TABB *TABB_retira(TABB *a, int info){
  if(!a) return a;

  if(info < a->info) 
    a->esq = TABB_retira(a->esq, info);
  else if(info > a->info) 
    a->dir = TABB_retira(a->dir, info);
  else { // info encontrada
    if((!a->esq) && (!a->dir)){ // CASO (1): é folha
      free(a);
      a = NULL;
    }
    else if((!a->esq) || (!a->dir)){ // CASO (2): tem um filho
      TABB *temp = a;
      if(!a->esq) 
        a = a->dir;
      else  
        a = a->esq;
      free(temp); 
    }
    else{ // CASO (3): tem dois filhos
      TABB *filho = a->esq; // Passo 1: Vai para esquerda
      while (filho->dir) // Passo 2: vai para o filho mais a direita
        filho = filho->dir;
      a->info = filho->info; // Passo 3: "a" passa a ter a info do filho mais a direita
      filho->info = info; // Passo 4: o filho mais a direita passa a ter a info de "a"
      a->esq = TABB_retira(a->esq, info); // Passo 5: retira o filho mais a direita recursivamente
    }
  }
  return a; 
}


TABB* TABB_retira_impares(TABB* a) {
    if (a) {
        a->esq = TABB_retira_impares(a->esq);
        a->dir = TABB_retira_impares(a->dir);
        
        if((a->info) % 2 != 0) {
            a = TABB_retira(a, a->info);
        }
    }
    return a;
}