#include <stdio.h>
#include <stdlib.h>
#include "q001_q002.h"

// gcc -o q001_q002usa.exe q001_q002usa.c q001_q002.c -lm
// .\q001_q002usa.exe

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

    printf("Árvore:\n");
    TABB_imp_sim(arv);

    TABB* maior_elemento = maior(arv);
    printf("\nMaior elemento: %d \n", maior_elemento->info);

    TABB* menor_elemento = menor(arv);
    printf("\nMenor elemento: %d \n", menor_elemento->info);

    return 0;
}