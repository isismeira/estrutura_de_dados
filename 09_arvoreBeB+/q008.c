#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB/TARVB.h"
#include "TARVBM/TARVBM.h"

typedef struct lseint{
  int lim_inf, lim_sup;
  struct lseint *prox;
} TLSEINT;


TLSEINT* TLSEINT_inicializa(void){
  return NULL;
}

TLSEINT* TLSEINT_insere(TLSEINT *l, int inf, int sup){
  TLSEINT *novo = (TLSEINT *) malloc(sizeof(TLSEINT));
  novo->prox = l;
  novo->lim_inf = inf;
  novo->lim_sup = sup;
  return novo;
}

void TLSEINT_imprime(TLSEINT *l){
  TLSEINT *p = l;
  while(p){
    printf("[%d,%d] ", p->lim_inf, p->lim_sup);
    p = p->prox;
  } 
}

void TLSEINT_libera(TLSEINT *l){
  TLSEINT *p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
}

// -------------------------------------------------------------------------------------------------

TLSEINT* misc(TARVB* a, int n) {
    TLSEINT* l = TLSEINT_inicializa(); 
    TARVB* p = a; 
    if (!p) return NULL;

    int elem_achado = 0; 

    while (p && !elem_achado) {

        int nao_achou_nada = 1;

        // ------------ VERIFICA SE O ELEMENTO ESTÁ NO NÓ ------------
        for (int i = 0; i < p->nchaves; i++) {
            if (p->chave[i] == n) { 
                elem_achado = 1; 
                break; 
            }
        }
        if (elem_achado) break;


        // --------------------- CASO: UMA CHAVE ---------------------
        if (p->nchaves == 1) {

            if (p->chave[0] <= n) { 
                l = TLSEINT_insere(l, p->chave[0], INT_MAX);

                if (!p->filho[1]) return NULL;  // evita segfault
                p = p->filho[1];

                nao_achou_nada = 0;

            } else { 
                l = TLSEINT_insere(l, INT_MIN, p->chave[0]);

                if (!p->filho[0]) return NULL; 
                p = p->filho[0];

                nao_achou_nada = 0;
            }
        }

        // ---------------- CASO: DUAS OU MAIS CHAVES ----------------
        else {

            // intervalo antes da primeira chave
            if (n < p->chave[0]) {
                l = TLSEINT_insere(l, INT_MIN, p->chave[0]);

                if (!p->filho[0]) return NULL;
                p = p->filho[0];

                nao_achou_nada = 0;
            }

            // tenta achar um intervalo intermediário
            if (nao_achou_nada) {
                for (int j = 0; j < p->nchaves - 1; j++) {

                    int ant = p->chave[j];
                    int dps = p->chave[j + 1];

                    if (ant <= n && n < dps) {

                        l = TLSEINT_insere(l, ant, dps);

                        if (!p->filho[j + 1]) return NULL;
                        p = p->filho[j + 1];

                        nao_achou_nada = 0;
                        break;
                    }
                }
            }

            // intervalo após a última chave
            if (nao_achou_nada) {

                l = TLSEINT_insere(l, p->chave[p->nchaves - 1], INT_MAX);

                if (!p->filho[p->nchaves]) return NULL;
                p = p->filho[p->nchaves];

                nao_achou_nada = 0;
            }
        }

        if (nao_achou_nada) return NULL;
    }

    if (!elem_achado) return NULL;

    return l;
}


/*
TLSEINT* misc(TARVB* a, int n) {
    TLSEINT* l = TLSEINT_inicializa(); // inicializo a lista encadeada
    TARVB* p = a; 
    if (!p) return NULL;
    int elem_achado = 0; 
    while(p && !elem_achado) { // enquanto existe um nó e o elemento não foi achado
        int nao_achou_nada = 1;
        for (int i = 0; i < p->nchaves; i++) { // primeiro, saber se o elemento que queremos esta naquele nó
            if (p->chave[i] == n) elem_achado = 1; // se está, sai do loop while e aquele nó ão terá nenhuma chave entrando na lista encadeada
            break;
        }
        // ... caso o elemento buscado não esteja no nó ...
        //... se o nó só tem uma chave
        if (p->nchaves == 1) {
            if (p->chave[0] <= n) { // se essa chave for menor ou igual ao elemento buscado
                l = TLSEINT_insere(l, p->chave[0], INT_MAX); // insiro na lista encadeada
                p = p->filho[1]; // desço para o filho direito
                nao_achou_nada = 0;
            } else { // se essa chave maior que o elemento buscado
                l = TLSEINT_insere(l, INT_MIN, p->chave[0]); // insiro na lista encadeada
                p = p->filho[0]; // desço para o filho esquerdo
                nao_achou_nada = 0;
            }
        } 
        for (int j = 0; j < p->nchaves - 1; j++) { // caso tenha mais de uma chave
            int ant = p->chave[j];
            int dps = p->chave[j + 1];
            if (ant <= n && dps > n) { // tento encontrar um antecessor menor ou igual ao elemento e um sucessor maior que o elemento
                l = TLSEINT_insere(l, ant, dps); // insiro na lista encadeada
                p = p->filho[j + 1]; // desço para o filho ente o antecessor e sucessor
                nao_achou_nada = 0;
                break;
            }
        }
        if (nao_achou_nada) return NULL;
    }
    if (!elem_achado) return NULL; // se não achou o elemento, retorna null
    return l;
}
*/