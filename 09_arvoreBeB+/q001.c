#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB/TARVB.h"
#include "TARVBM/TARVBM.h"

// Escreva uma função que retorna o sucessor de um elemento na árvore. Se o elemento for o maior da estrutura, sua função deve retornar INT_MAX:

// Implementação árvore B

int menor_elem(TARVB *a){
    while(a && !a->folha) // enquanto a não for nulo e não for folha
        a = a->filho[0]; // desce para o filho mais a esquerda
    if(!a) // se chegou a um nó nulo
        return INT_MAX; // indica que não foi encontrado
    return a->chave[0]; // retorna a primeira chave do nó folha
}

int suc_b(TARVB *arv, int ch){
    TARVB *atual = arv;
    int sucessor = INT_MAX;

    while(atual){
        int i = 0;

        // Avança até a posição onde ch estaria
        while (i < atual->nchaves && ch >= atual->chave[i]) 
            i++;

        // i agora está na primeira chave > ch (possível sucessor)
        if(i < atual->nchaves){
            if(atual->chave[i] > ch && atual->chave[i] < sucessor)
                sucessor = atual->chave[i];
        }

        // Se achamos a chave na posição anterior, exploramos o filho da direita
        if(i > 0 && atual->chave[i-1] == ch){
            // Se tem filho à direita, o sucessor é o menor da subárvore direita
            if(!atual->folha){
                int menor = menor_elem(atual->filho[i]);
                if(menor < sucessor) sucessor = menor;
            }
            break;
        }

        // Se for folha, termina
        if(atual->folha) break;

        // Caminha para o filho onde ch poderia estar
        atual = atual->filho[i];
    }

    return sucessor;
}

//gcc q001.c TARVB/TARVB.c -o q001

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

    printf("Árvore B:\n");
    TARVB_Imprime(arv);
    printf("\n");

    // Testes
    int v[] = {10, 20, 30, 40, 50};
    int n = 5;

    for(int i = 0; i < n; i++){
        int e = v[i];
        int s = suc_b(arv, e);

        if(s == INT_MAX)
            printf("Sucessor(%d) = INT_MAX (não existe maior)\n", e);
        else
            printf("Sucessor(%d) = %d\n", e, s);
    }

    TARVB_Libera(arv);
    return 0;
}