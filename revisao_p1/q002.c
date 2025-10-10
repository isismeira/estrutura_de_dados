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


// 2) Faça uma função que encontra a média simples de elementos em cada nível de uma árvore binária simples - int *media(TAB *a, int *tam_vet).
int* media(TAB* a, int* tam_vet) {

    int* vetor_elementos_por_nivel = calloc(*tam_vet, sizeof(int)); // !!!
    int* vetor_soma_por_nivel = calloc(*tam_vet, sizeof(int)); // !!!

    percorre_arvore(a,vetor_elementos_por_nivel, vetor_soma_por_nivel, 0);

     int* vetor_medias = malloc(*tam_vet * sizeof(int)); // !!!

    for (int i = 0; i < *tam_vet; i++) {
        vetor_medias[i] = vetor_soma_por_nivel[i] / vetor_elementos_por_nivel[i];
    }

    free(vetor_elementos_por_nivel); // !!!
    free(vetor_soma_por_nivel); // !!!

    return vetor_medias;
}

void percorre_arvore(TAB* a,int* vetor_elementos_por_nivel,int* vetor_soma_por_nivel, int nivel) {
    if (a) {
        vetor_elementos_por_nivel[nivel]++;
        vetor_soma_por_nivel[nivel]+=(a->info);
        percorre_arvore(a->esq,vetor_elementos_por_nivel, vetor_soma_por_nivel, nivel+1);
        percorre_arvore(a->dir,vetor_elementos_por_nivel, vetor_soma_por_nivel, nivel+1);
    }
}

/*
    int* media(TAB* a, int* tam_vet) {
        int vetor_elementos_por_nivel[tam_vet] = {0};
        int vetor_soma_por_nivel[tam_vet] = {0};
        percorre_arvore(a,vetor_elementos_por_nivel, vetor_soma_por_nivel);
        int vetor_medias[tam_vet] = {0};
        for (int i = 0; i < tam_vet - 1; i++) {
            vetor_medias[i] = vetor_soma_por_nivel[i] / vetor_elementos_por_nivel[i];
        }
        return vetor_medias
    }

    void percorre_arvore(TAB* a,int* vetor_elementos_por_nivel,int* vetor_soma_por_nivel, int nivel) {
        if (a) {
            vetor_elementos_por_nivel[nivel]++;
            vetor_soma_por_nivel[nivel]+=(a->info);
            percorre_arvore(a->esq,vetor_elementos_por_nivel, vetor_soma_por_nivel, nivel++);
            percorre_arvore(a->dir,vetor_elementos_por_nivel, vetor_soma_por_nivel, nivel++);
        }
    }
*/