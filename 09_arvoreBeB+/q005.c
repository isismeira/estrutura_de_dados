#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB/TARVB.h"
#include "TARVBM/TARVBM.h"

// hahaha eZ

int conta_elementos(TARVB* a, int contador) {
    for (int i = 0; i < a->nchaves; i++){
        if (a) 
            contador++;

    }
    int novo_contador = contador;
    for (int j = 0; j <= a->nchaves; j++) {
        if (a->filho[j])
            novo_contador = conta_elementos(a->filho[j],novo_contador);
    }
    return novo_contador;
}

int preenche_elementos_pares(TARVB* a, int* lista_pares, int contador) {
    for (int i = 0; i < a->nchaves;i++){
        if (a) {
            if(a->chave[i] % 2 == 0) {
                lista_pares[contador] = a->chave[i];
                contador++;
            }
        }
    }
    int novo_contador = contador;
    for (int j = 0; j <= a->nchaves; j++) {
        if (a->filho[j])
            novo_contador = preenche_elementos_pares(a->filho[j],lista_pares,novo_contador);
    }
    return novo_contador;
}

TARVB* retira_pares(TARVB* a) {
    if (!a) return NULL;
    int n = conta_elementos(a,0);
    int* lista_pares = calloc(n, sizeof(int));
    int n_pares = preenche_elementos_pares(a, lista_pares, 0);
    for (int i = 0; i < n_pares; i++)
        a = TARVB_Retira(a,lista_pares[i],2);
    return a;    
}

//gcc q005.c TARVB/TARVB.c -o q005

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

    arv = retira_pares(arv);

    printf("Árvore B:\n");
    TARVB_Imprime(arv);
    printf("\n");

    TARVB_Libera(arv);
    return 0;
}