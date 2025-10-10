#include <stdio.h>
#include <stdlib.h>
#include "q004.h"

// gcc -o q004usa.exe q004usa.c q004.c -lm
// .\q004usa.exe

int main(void) {

    TAB *a = TAB_cria(5,
                TAB_cria(3,
                    TAB_cria(2, NULL, NULL),
                    TAB_cria(4, NULL, NULL)
                ),
                TAB_cria(8,
                    TAB_cria(7, NULL, NULL),
                    TAB_cria(10, NULL, NULL)
                )
            );

    printf("Árvore (forma indentada):\n");
    TAB_imp_ident(a);

    int N;
    printf("\nDigite o valor N para verificar a quantidade de caminhos que somam N: ");
    scanf("%d", &N);

    int qtd = quant_caminhos(a, N);
    printf("\nQuantidade de caminhos que somam %d: %d\n", N, qtd);

    TAB_libera(a);
    return 0;
}
