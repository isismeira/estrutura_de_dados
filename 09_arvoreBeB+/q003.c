#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB/TARVB.h"
#include "TARVBM/TARVBM.h"

TARVB* menor(TARVB* a) {
    if (!a) return NULL;
    TARVB* atual = a;
    while(atual->filho[0]){
        atual = atual->filho[0];
    }
    return atual;
}

//gcc q003.c TARVB/TARVB.c -o q003

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

    printf("Menor elemento: %i", menor(arv)->chave[0]);

    TARVB_Libera(arv);
    return 0;
}