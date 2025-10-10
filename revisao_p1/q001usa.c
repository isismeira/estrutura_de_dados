#include <stdio.h>
#include <stdlib.h>
#include "q001.h"

// gcc -o q001usa.exe q001usa.c q001.c -lm
// .\q001usa.exe

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



    int misc = misc1(arv);

    printf("\nSoma de todos os elementos de nível ímpar em uma árvore binária simples e subtração todos os de nível par: %i \n", misc);
    return 0;
}