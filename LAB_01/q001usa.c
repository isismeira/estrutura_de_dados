#include <stdio.h>
#include <stdlib.h>
#include "q001.h"

// gcc -o q001usa.exe q001usa.c q001.c -lm
// .\q001usa.exe

int main() {
    /* Montando a árvore:
           10
          /  \
         5    20
        /  \  /
       3   7 15       */

    TAB* arv_1 = TAB_cria(10,
                    TAB_cria(5,
                        TAB_cria(3, NULL, NULL),
                        TAB_cria(7, NULL, NULL)
                    ),
                    TAB_cria(20,
                        TAB_cria(15, NULL, NULL),
                        NULL
                    )
                );

    misc1(arv_1);
    return 0;
}                