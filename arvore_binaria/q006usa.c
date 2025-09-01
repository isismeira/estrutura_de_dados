#include <stdio.h>
#include <stdlib.h>
#include "q006.h"

// gcc -o q006usa.exe q006usa.c q006.c -lm
// .\q006usa.exe

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

    printf("Antes:\n");
    TAB_imp_pre(arv);

    arv = retira_pares(arv);

    printf("\nDepois de remover pares:\n");
    TAB_imp_pre(arv);

    return 0;
}
