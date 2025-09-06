#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "q005.h"

TABB* TABB_inicializa(TABB* a) {
    return NULL;
}

TABB* TABB_cria(char* n, int* d, TABB* esq, TABB* dir) {
    TABB* novo = (TABB*)malloc(sizeof(TABB));
    strcpy(novo->nome, n);
    memcpy(novo->dim, d, sizeof(int) * 4);
    int area = 0;

    if (strcmp(novo->nome, "quadrado") == 0 || strcmp(novo->nome, "retangulo") == 0) {
        area = d[0] * d[1];
    }
    else if (strcmp(novo->nome, "triangulo") == 0) {
        // d[0] = base, d[1] = lado (considerando equilátero/isosceles)
        int altura = sqrt(pow(d[1], 2) - pow(d[0] / 2, 2));
        area = (d[0] * altura) / 2;
    }
    else if (strcmp(novo->nome, "trapezio") == 0) {
        // d[0] = base menor, d[1] = base maior, d[2] = lado esquerdo, d[3] = lado direito
        int diferenca_bases = d[1] - d[0];
        int x = (d[2] * d[2] - d[3] * d[3] + diferenca_bases * diferenca_bases) / (2 * diferenca_bases);
        int altura = sqrt(d[2] * d[2] - x * x);
        area = (d[1] + d[0]) * altura / 2;
    }

    novo->area = area;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

void TABB_imp_sim(TABB *a){ 
  if(a){
    TABB_imp_sim(a->esq); 
    printf("Figura: %s\n", a->nome);
    printf("Dimensões: ");
    for (int i = 0; i < 4; i++) {
        printf("%i ", a->dim[i]);
    }
    printf("\nÁrea: %i\n", a->area);
    TABB_imp_sim(a->dir);
  }
}

TABB* TABB_insere(TABB* a, char* nome, int* d) {
    if (!a) return TABB_cria(nome, d, NULL, NULL);

    int area_nova;
    // calcula a área com base no nome + dimensões
    // (pode extrair isso para uma função auxiliar)
    if (strcmp(nome, "quadrado") == 0 || strcmp(nome, "retangulo") == 0) 
        area_nova = d[0] * d[1];
    else if (strcmp(nome, "triangulo") == 0) {
        int altura = sqrt(pow(d[1], 2) - pow(d[0]/2, 2));
        area_nova = (d[0] * altura) / 2;
    }
    else if (strcmp(nome, "trapezio") == 0) {
        int diferenca_bases = d[1] - d[0];
        int x = (d[2]*d[2] - d[3]*d[3] + diferenca_bases*diferenca_bases) / (2*diferenca_bases);
        int altura = sqrt(d[2]*d[2] - x*x);
        area_nova = (d[1] + d[0]) * altura / 2;
    }

    if (area_nova < a->area) 
        a->esq = TABB_insere(a->esq, nome, d);
    else 
        a->dir = TABB_insere(a->dir, nome, d);

    return a;
}

TABB* TABB_busca(TABB* a, int area) {
    if (!a) return NULL;
    if (area == a->area) return a;
    if (area < a->area) return TABB_busca(a->esq, area);
    else return TABB_busca(a->dir, area);
}

TABB* TABB_retira(TABB* a, int area) {
    if (!a) return NULL;

    if (area < a->area)
        a->esq = TABB_retira(a->esq, area);
    else if (area > a->area)
        a->dir = TABB_retira(a->dir, area);
    else { // achou
        if (!a->esq && !a->dir) { // caso folha
            free(a);
            return NULL;
        }
        else if (!a->esq || !a->dir) { // 1 filho
            TABB* temp = a->esq ? a->esq : a->dir;
            free(a);
            return temp;
        }
        else { // 2 filhos
            TABB* filho = a->esq;
            while (filho->dir) filho = filho->dir; // maior da esquerda
            a->area = filho->area;
            strcpy(a->nome, filho->nome);
            memcpy(a->dim, filho->dim, sizeof(int)*4);
            a->esq = TABB_retira(a->esq, filho->area);
        }
    }
    return a;
}
