#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB/TARVB.h"
#include "TARVBM/TARVBM.h"

// Implementação árvore B

int ni_b_aux(TARVB* a,int contador) {
    if (a && !a->folha) {
        for (int i = 0; i < a->nchaves; i++)
            contador++;
    }
    int novo_contador = contador;
    for (int j = 0; j <= a->nchaves; j++) {
        if (a->filho[j])
            novo_contador = ni_b_aux(a->filho[j], novo_contador);
    }
    return novo_contador;
}

int ni_b(TARVB* a) {
    if (!a) return 0;
    return ni_b_aux(a,0);
}

// Implementação árvore B+ (igual)

int ni_bm_aux(TARVBM* a,int contador) {
    if (a && !a->folha) {
        for (int i = 0; i < a->nchaves; i++)
            contador++;
    }
    int novo_contador = contador;
    for (int j = 0; j <= a->nchaves; j++) {
        if (a->filho[j])
            novo_contador = ni_bm_aux(a->filho[j], novo_contador);
    }
    return novo_contador;
}

int ni_bm(TARVBM* a) {
    if (!a) return 0;
    return ni_bm_aux(a,0);
}

//gcc q006.c TARVB/TARVB.c TARVBM/TARVBM.c -o q006

int main() {

    int t = 2; 
    TARVB *arv = TARVB_Inicializa();

    arv = TARVB_Insere(arv, 20, t);
    arv = TARVB_Insere(arv, 40, t);
    arv = TARVB_Insere(arv, 10, t);
    arv = TARVB_Insere(arv, 30, t);
    arv = TARVB_Insere(arv, 50, t);
    arv = TARVB_Insere(arv, 15, t);
    arv = TARVB_Insere(arv, 12, t);
    arv = TARVB_Insere(arv, 21, t);
    arv = TARVB_Insere(arv, 29, t);
    arv = TARVB_Insere(arv, 28, t);
    arv = TARVB_Insere(arv, 11, t);

    printf("Árvore B:\n");
    TARVB_Imprime(arv);
    printf("\n");


    printf("Nós internos: %i\n", ni_b(arv));


    TARVB_Libera(arv);


    TARVBM *arvbm = TARVBM_inicializa();

    arvbm = TARVBM_insere(arvbm, 20, t);
    arvbm = TARVBM_insere(arvbm, 40, t);
    arvbm = TARVBM_insere(arvbm, 10, t);
    arvbm = TARVBM_insere(arvbm, 30, t);
    arvbm = TARVBM_insere(arvbm, 50, t);
    arvbm = TARVBM_insere(arvbm, 15, t);
    arvbm = TARVBM_insere(arvbm, 12, t);
    arvbm = TARVBM_insere(arvbm, 21, t);
    arvbm = TARVBM_insere(arvbm, 29, t);
    arvbm = TARVBM_insere(arvbm, 28, t);
    arvbm = TARVBM_insere(arvbm, 11, t);

    printf("Árvore B+:\n");
    TARVBM_imprime(arvbm);
    printf("\n");


    printf("Nós folhas: %i\n", ni_bm(arvbm));


    TARVBM_libera(arvbm);
    return 0;
}