#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB/TARVB.h"
#include "TARVBM/TARVBM.h"

TARVB* maior(TARVB* a) {
    if (!a) return NULL;
    TARVB* atual = a;
    while(atual->filho[atual->nchaves]){
        int ultimo_indice = (atual->nchaves - 1);
        atual = atual->filho[ultimo_indice + 1];
    }
    return atual;
}

//gcc q002.c TARVB/TARVB.c -o q002

int main() {

    int t = 2;  // ordem mínima da árvore B
    TARVB *arv = TARVB_Inicializa();

    // Montando a árvore
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

    printf("Maior elemento: %i", maior(arv)->chave[maior(arv)->nchaves-1]);

    TARVB_Libera(arv);
    return 0;
}