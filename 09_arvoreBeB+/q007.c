#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB/TARVB.h"
#include "TARVBM/TARVBM.h"

// Implementação Árvore B
int nf_b_aux(TARVB* a,int contador) {
    if (a && a->folha) {
        for (int i = 0; i < a->nchaves; i++)
            contador++;
    }
    int novo_contador = contador;
    for (int j = 0; j <= a->nchaves; j++) {
        if (a->filho[j])
            novo_contador = nf_b_aux(a->filho[j], novo_contador);
    }
    return novo_contador;
}

int nf_b(TARVB* a) {
    if (!a) return 0;
    return nf_b_aux(a,0);
}

// Implementação Árvore B+ (aqui é diferente, podemos descer até o último nó e pular de nó folha em nó folha com prox)

int nf_bm(TARVBM* a) {
    if (!a) return 0;
    TARVBM* aux = a;
    while(aux->filho[0])
        aux = aux->filho[0];
    int contador = 0;    
    while(aux) { 
        contador += aux->nchaves; //!!!
        aux = aux->prox; // !!!
    }    
    return contador;        
}

//gcc q007.c TARVB/TARVB.c TARVBM/TARVBM.c -o q007

int main() {

    int t = 2; 
    TARVB *arvb = TARVB_Inicializa();

    arvb = TARVB_Insere(arvb, 20, t);
    arvb = TARVB_Insere(arvb, 40, t);
    arvb = TARVB_Insere(arvb, 10, t);
    arvb = TARVB_Insere(arvb, 30, t);
    arvb = TARVB_Insere(arvb, 50, t);
    arvb = TARVB_Insere(arvb, 15, t);
    arvb = TARVB_Insere(arvb, 12, t);
    arvb = TARVB_Insere(arvb, 21, t);
    arvb = TARVB_Insere(arvb, 29, t);
    arvb = TARVB_Insere(arvb, 28, t);
    arvb = TARVB_Insere(arvb, 11, t);

    printf("Árvore B:\n");
    TARVB_Imprime(arvb);
    printf("\n");


    printf("Nós folhas: %i\n", nf_b(arvb));


    TARVB_Libera(arvb);

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


    printf("Nós folhas: %i\n", nf_bm(arvbm));


    TARVBM_libera(arvbm);

    return 0;
}