#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB/TARVB.h"
#include "TARVBM/TARVBM.h"

int nf_aux(TARVB* a,int contador) {
    if (a && a->folha) {
        for (int i = 0; i < a->nchaves; i++)
            contador++;
    }
    int novo_contador = contador;
    for (int j = 0; j <= a->nchaves; j++) {
        if (a->filho[j])
            novo_contador = nf_aux(a->filho[j], novo_contador);
    }
    return novo_contador;
}

int nf(TARVB* a) {
    if (!a) return 0;
    return nf_aux(a,0);
}

//gcc q007.c TARVB/TARVB.c -o q007

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


    printf("Nós folhas: %i\n", nf(arv));


    TARVB_Libera(arv);
    return 0;
}