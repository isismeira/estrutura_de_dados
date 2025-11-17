#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB/TARVB.h"
#include "TARVBM/TARVBM.h"

int igual(TARVB* a1, TARVB* a2) {
    if (!a1 && !a2) return 1;
    if (!a1 || !a2) return 0;
    if (a1->nchaves != a2->nchaves) return 0;
    int i = 0;
    for (i; i < a1->nchaves; i++) {
        if (a1->chave[i]!=a2->chave[i]) return 0;
        if (!igual(a1->filho[i],a2->filho[i])) return 0;
    }
    if (!igual(a1->filho[i+1],a2->filho[i+1])) return 0;
    int j = 0;
    for (j; j < a2->nchaves; j++) {
        if (a2->chave[j]!=a1->chave[j]) return 0;
        if (!igual(a2->filho[j],a1->filho[j])) return 0;
    }
     if (!igual(a1->filho[j+1],a2->filho[j+1])) return 0;
}

//gcc q004.c TARVB/TARVB.c -o q004

int main() {

    int t = 2; 
    TARVB *arv1 = TARVB_Inicializa();

    arv1 = TARVB_Insere(arv1, 20, t);
    arv1 = TARVB_Insere(arv1, 40, t);
    arv1 = TARVB_Insere(arv1, 10, t);
    arv1 = TARVB_Insere(arv1, 30, t);
    arv1 = TARVB_Insere(arv1, 50, t);
    arv1 = TARVB_Insere(arv1, 15, t);
    arv1 = TARVB_Insere(arv1, 12, t);
    arv1 = TARVB_Insere(arv1, 21, t);
    arv1 = TARVB_Insere(arv1, 29, t);
    arv1 = TARVB_Insere(arv1, 28, t);
    arv1 = TARVB_Insere(arv1, 11, t);

    TARVB *arv2 = TARVB_Inicializa();

    arv2 = TARVB_Insere(arv2, 20, t);
    arv2 = TARVB_Insere(arv2, 40, t);
    arv2 = TARVB_Insere(arv2, 10, t);
    arv2 = TARVB_Insere(arv2, 30, t);
    arv2 = TARVB_Insere(arv2, 50, t);
    arv2 = TARVB_Insere(arv2, 12, t);
    arv2 = TARVB_Insere(arv2, 21, t);
    arv2 = TARVB_Insere(arv2, 29, t);
    arv2 = TARVB_Insere(arv2, 28, t);
    arv2 = TARVB_Insere(arv2, 11, t);

    printf("É igual: %i", igual(arv1,arv2));
    return 0;
}