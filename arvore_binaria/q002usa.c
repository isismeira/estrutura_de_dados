#include <stdio.h>
#include <stdlib.h>
#include "q002.h"

// gcc -o q002usa.exe q002usa.c q002.c -lm
// .\q002usa.exe

int main() {
    /* Montando a árvore:
           10
          /  \
         5    20
        /  \  /
       3   7 15       */

    TAB* arv = TAB_cria(10,
                    TAB_cria(5,
                        TAB_cria(3, NULL, NULL),
                        TAB_cria(7, NULL, NULL)
                    ),
                    TAB_cria(20,
                        TAB_cria(15, NULL, NULL),
                        NULL
                    )
                );

    printf("Arvore original (in-order): ");
    TAB_imp_pre(arv);
    printf("\n");

    // Criando espelho
    TAB* arv_espelho = espelho(arv);

    printf("Arvore espelhada (in-order): ");
    TAB_imp_pre(arv_espelho);
    printf("\n");

    return 0;
}
