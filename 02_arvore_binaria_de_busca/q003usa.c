#include <stdio.h>
#include <stdlib.h>
#include "q003.h"

// gcc -o q003usa.exe q003usa.c q003.c -lm
// .\q003usa.exe

int main() {
    TABB* arv = TABB_cria(10,
                    TABB_cria(5,
                        TABB_cria(2, NULL, NULL),
                        TABB_cria(7, NULL, NULL)
                    ),
                    TABB_cria(20,
                        TABB_cria(15, NULL, NULL),
                        NULL
                    )
                );

    printf("Árvore original:\n");
    TABB_imp_sim(arv);

    arv = TABB_retira_impares(arv);

    printf("Árvore após retirar ímpares:\n");
    TABB_imp_sim(arv);

    return 0;
}