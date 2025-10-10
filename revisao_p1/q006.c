#include "q006.h"

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

// 6) Escreva uma função que receba uma árvore binária e teste as seguintes propriedades: (a) se o nó se encontra no nível par, ele tem ZERO ou dois filhos; e (b) se ele está no nível ímpar, ele só pode ter UM filho. A função retorna UM, se a árvore segue essas propriedades, e ZERO, caso contrário. A função deve ter o seguinte protótipo: int teste_arv(TAB* a); 

int teste_arv(TAB* a) {
    int resultado =  teste_arv_aux(a,0);
    if (resultado != 0) {
        return 0;
    }
    return 1;
}

int teste_arv_aux(TAB* a, int nivel) {
    if (a) {
        if (nivel % 2 == 0) {
            if((a->dir && a->esq) || (!a->dir && !a->esq)) {
                return 0 + teste_arv_aux(a->esq, nivel + 1) + teste_arv_aux(a->dir, nivel+1);
            } else {
                return 1;
            }    
        } else {
            if((a->dir && !a->esq) || (!a->dir && a->esq)) {
                return 0 + teste_arv_aux(a->esq, nivel + 1) + teste_arv_aux(a->dir, nivel+1);
            } else {
                 return 1;
            }
        }
    }
}