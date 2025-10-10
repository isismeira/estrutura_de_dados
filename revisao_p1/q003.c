#include "q003.h"

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

// 3) Retorne o nó de maior nível que é ancestral tanto de N quanto de M - TAB* maior_nivel(TAB *a, int N, int M).
TAB* maior_nivel(TAB *a, int N, int M) {
    if (a == NULL) return NULL;

    if (a->info == N || a->info == M)
        return a;

    TAB *esq = maior_nivel(a->esq, N, M);
    TAB *dir = maior_nivel(a->dir, N, M);

    if (esq && dir)
        return a;

    return (esq != NULL) ? esq : dir;
}


// obs. Função para determinar a distância entre dois nós quaisquer
int distancia_dois_nos(TAB* a, int N, int M) {
    TAB* melhor_ancestral = maior_nivel(a, N, M);
    int contador_n = 0;
    distancia_raiz_n(melhor_ancestral, N, &contador_n); // !!!
    int contador_m = 0;
    distancia_raiz_n(melhor_ancestral, M, &contador_m); // !!!
    return contador_n + contador_m;
}

void distancia_raiz_n(TAB* melhor_ancestral, int N, int* contador) {
    if (melhor_ancestral) {
        if (melhor_ancestral->info == N) {
            return;
        } else {
            (*contador)++;
            if (TAB_busca(melhor_ancestral->esq, N)) { // !!!
                distancia_raiz_n(melhor_ancestral->esq, N, contador);
            } else {
                distancia_raiz_n(melhor_ancestral->dir, N, contador);
            }
        }
    }
}