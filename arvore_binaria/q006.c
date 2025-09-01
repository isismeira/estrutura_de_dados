#include <stdio.h>
#include <stdlib.h>
#include "q006.h"

typedef struct arvbin {
    int info;
    struct arvbin *esq, *dir;
}TAB;

TAB* TAB_inicializa(void) {
    return NULL;
}

TAB* TAB_cria(int raiz, TAB* esq, TAB* dir){
    TAB* novo = (TAB*)malloc(sizeof(TAB));
    novo->info = raiz;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

TAB* TAB_imp_pre(TAB* a) {
    if (a) {
        printf("%d\n", a->info);
        TAB_imp_pre(a->esq);
        TAB_imp_pre(a->dir);
    }
}

TAB* retira_pares(TAB* arv) {
    if (!arv) return NULL;

    // Primeiro, trata as subárvores
    arv->esq = retira_pares(arv->esq);
    arv->dir = retira_pares(arv->dir);

    // Agora verifica o nó atual
    if (arv->info % 2 == 0) { 
        TAB* temp;

        if (!arv->esq && !arv->dir) { 
            // Caso 1: folha
            free(arv);
            return NULL;
        }
        else if (!arv->esq) { 
            // Caso 2: só tem filho direito
            temp = arv->dir;
            free(arv);
            return temp;
        }
        else if (!arv->dir) { 
            // Caso 3: só tem filho esquerdo
            temp = arv->esq;
            free(arv);
            return temp;
        }
        else {
            // Caso 4: dois filhos -> escolhe arbitrariamente a esquerda
            temp = arv->esq;

            // Para não perder a subárvore direita, pendura ela no "fim" da subárvore esquerda (opcional)
            TAB* aux = temp;
            while (aux->dir) 
                aux = aux->dir;
            aux->dir = arv->dir;

            free(arv);
            return temp;
        }
    }
    return arv;
}
