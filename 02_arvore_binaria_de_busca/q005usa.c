#include <stdio.h>
#include <stdlib.h>
#include "q005.h"

// gcc -o q005usa.exe q005usa.c q005.c -lm
// .\q005usa.exe

int main() {
    TABB* arv = NULL;

    // Inserindo figuras
    int dim1[4] = {4, 4, 0, 0};   // quadrado 4x4
    arv = TABB_insere(arv, "quadrado", dim1);

    int dim2[4] = {5, 10, 0, 0};  // retângulo 5x10
    arv = TABB_insere(arv, "retangulo", dim2);

    int dim3[4] = {6, 5, 0, 0};   // triângulo base=6, lado=5
    arv = TABB_insere(arv, "triangulo", dim3);

    int dim4[4] = {4, 10, 5, 5};  // trapézio
    arv = TABB_insere(arv, "trapezio", dim4);

    printf("\n==== Árvore em ordem (simétrica) ====\n");
    TABB_imp_sim(arv);

    // Busca
    int area_busca = 12; // por exemplo
    TABB* achou = TABB_busca(arv, area_busca);
    if (achou) {
        printf("\n\nFigura encontrada com área %d: %s\n", achou->area, achou->nome);
    } else {
        printf("\n\nNenhuma figura encontrada com área %d.\n", area_busca);
    }

    // Retirada
    printf("\n==== Removendo figura com área %d ====\n", 12);
    arv = TABB_retira(arv, 12);

    printf("\n==== Árvore após remoção ====\n");
    TABB_imp_sim(arv);

    return 0;
}
