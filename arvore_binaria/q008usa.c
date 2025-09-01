#include <stdio.h>
#include <stdlib.h>
#include "q008.h"

// gcc -o q008usa.exe q008usa.c q008.c -lm
// .\q008usa.exe

int main() {
    TAB* arv = TAB_cria(10,
                    TAB_cria(5,
                        TAB_cria(2, NULL, NULL),
                        TAB_cria(7, NULL, NULL)
                    ),
                    TAB_cria(20,
                        TAB_cria(15, NULL, NULL),
                        NULL
                    )
                );

    printf("Árvore:\n");
    TAB_imp_pre(arv);

    printf("Quantidade de nós: %d", ni(arv));

    return 0;
}