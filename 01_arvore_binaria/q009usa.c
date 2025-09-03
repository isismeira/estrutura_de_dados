#include <stdio.h>
#include <stdlib.h>
#include "q009.h"

// gcc -o q009usa.exe q009usa.c q009.c -lm
// .\q009usa.exe

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

    printf("Quantidade de folhas: %d", nf(arv));

    return 0;
}
