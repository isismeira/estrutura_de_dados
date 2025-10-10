#include <stdio.h>
#include <stdlib.h>
#include "q006.h"

// gcc -o q006usa.exe q006usa.c q006.c -lm
// .\q006usa.exe

int main(void) {
    TAB *a = TAB_cria(5,
                TAB_cria(3,
                    TAB_cria(2, NULL, NULL),
                    NULL
                ),
                TAB_cria(8,
                    TAB_cria(7, NULL, NULL),
                    NULL
                )
            );

    
    printf("Segue as propriedades: %i", teste_arv(a));         

    return 0;
}
