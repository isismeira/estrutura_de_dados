#include <stdio.h>
#include <stdlib.h>
#include "q004.h"

// gcc -o q004usa.exe q004usa.c q004.c -lm
// .\q004usa.exe

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



    int qtd = 3;
    int* vetor = mN(arv, 10);

    printf("Foram encontrados %d elementos menores que 50:\n", qtd);
    for (int i = 0; i < qtd; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    free(vetor); // liberar memória alocada
    return 0;
}