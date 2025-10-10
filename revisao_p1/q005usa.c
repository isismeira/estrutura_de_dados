#include <stdio.h>
#include <stdlib.h>
#include "q005.h"

// gcc -o q005usa.exe q005usa.c q005.c -lm
// .\q005usa.exe

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

    TLSEINT* l = misc(a, 7);

    return 0;
}
