#include <stdio.h>
#include <stdlib.h>
#include "q002.h"

// gcc -o q002usa.exe q002usa.c q002.c -lm
// .\q002usa.exe

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

    int* medias[3] = media(arv_1);

    return 0;
}             