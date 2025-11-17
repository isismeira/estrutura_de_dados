#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB/TARVB.h"
#include "TARVBM/TARVBM.h"

int ni_aux(TARVB* a,int contador) {
    if (a && !a->folha) {
        for (int i = 0; i < a->nchaves; i++)
            contador++;
    }
    int novo_contador = contador;
    for (int j = 0; j <= a->nchaves; j++) {
        if (a->filho[j])
            novo_contador = ni_aux(a->filho[j], novo_contador);
    }
    return novo_contador;
}

int ni(TARVB* a) {
    if (!a) return 0;
    return ni_aux(a,0);
}

//gcc q006.c TARVB/TARVB.c -o q006

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


    printf("Nós internos: %i\n", ni(arv));


    TARVB_Libera(arv);
    return 0;
}