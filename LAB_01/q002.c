#include "q002.h"

TAB *TAB_inicializa(void){
  return NULL;
}

TAB *TAB_cria(int raiz, TAB *esq, TAB *dir){
  TAB *novo = (TAB *) malloc(sizeof(TAB));
  novo->info = raiz;
  novo->esq = esq;
  novo->dir = dir;
  return novo;
}

TAB *TAB_busca(TAB *a, int elem){
  if((!a) || (a->info == elem)) return a;
  TAB *resp = TAB_busca(a->esq, elem);
  if(resp) return resp;
  return TAB_busca(a->dir, elem);
}

void TAB_imp_pre(TAB *a){
  if(a){
    printf("%d ", a->info);
    TAB_imp_pre(a->esq);
    TAB_imp_pre(a->dir);
  }
}

void TAB_imp_pos(TAB *a){
  if(a){
    TAB_imp_pos(a->esq);
    TAB_imp_pos(a->dir);
    printf("%d ", a->info);
  }
}

void TAB_imp_sim(TAB *a){
  if(a){
    TAB_imp_sim(a->esq);
    printf("%d ", a->info);
    TAB_imp_sim(a->dir);
  }
}

void imp_aux(TAB *a, int andar){
  int j;
  if(a){
    imp_aux(a->dir, andar + 1);
    for(j = 0; j <= andar; j++) printf("\t"); //printf("   ");
    printf("%d\n", a->info);
    imp_aux(a->esq, andar + 1);
  }
  else{
   for(j = 0; j <= andar; j++) printf("\t");
   printf("N\n");
  }
}

void TAB_imp_ident(TAB *a){
  imp_aux(a, 0);
}

void TAB_libera(TAB *a){
  if(a){
    TAB_libera(a->esq);
    TAB_libera(a->dir);
    free(a);
  }
}

int maior(int x, int y){
  if(x >= y) return x;
  return y;
}

int TAB_altura(TAB *a){
  if(!a) return -1;
  return maior(TAB_altura(a->esq), TAB_altura(a->dir)) + 1;
}

int* media(TAB* a) { // tirei um parametro int* tam_vet
    int qtdd_niveis = TAB_altura(a) + 1;
    int somatorio_por_nivel[qtdd_niveis];
    int elementos_por_nivel[qtdd_niveis];
    conta_elementos_nivel(a, elementos_por_nivel, 0);
    soma_por_nivel(a, somatorio_por_nivel, 0);
    int media_por_nivel[qtdd_niveis];
    for (int i = 0; i < qtdd_niveis; i++) {
        media_por_nivel[i] = somatorio_por_nivel[i]/elementos_por_nivel[i];
    }
    return media_por_nivel;
}

void conta_elementos_nivel(TAB* a, int* elementos_por_nivel, int nivel) {
    if (a) {
        elementos_por_nivel[nivel]++;
        conta_elementos_nivel(a->esq, elementos_por_nivel, nivel++);
        conta_elementos_nivel(a->dir, elementos_por_nivel, nivel++);
    }
}

void soma_elementos_nivel(TAB* a, int* somatorio_por_nivel, int nivel) {
    if (a) {
        somatorio_por_nivel[nivel] += a->info;
        soma_elementos_nivel(a->esq, somatorio_por_nivel, nivel++);
        soma_elementos_nivel(a->dir, somatorio_por_nivel, nivel++);
    }
}