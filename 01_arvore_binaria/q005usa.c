#include <stdio.h>
#include <stdlib.h>
#include "q005.h"

// gcc -o q005usa.exe q005usa.c q005.c -lm
// .\q005usa.exe

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

    TAB* arv_2 = TAB_cria(10,
                    TAB_cria(5,
                        TAB_cria(3, NULL, NULL),
                        TAB_cria(7, NULL, NULL)
                    ),
                    TAB_cria(20,
                        TAB_cria(15, NULL, NULL),
                        NULL
                    )
                );  
                
    TAB* arv_3 = TAB_cria(10,
                    TAB_cria(5,
                        TAB_cria(3, NULL, NULL),
                        TAB_cria(7, NULL, NULL)
                    ),
                    TAB_cria(20,
                        TAB_cria(16, NULL, NULL),
                        NULL
                    )
                );
                
    if (igual(arv_1, arv_2) == 0) {
        printf("As árvores são iguais\n");
    } else {
        printf("As árvores não são iguais\n");
    }            

    if (igual(arv_2, arv_3) == 0) {
        printf("As árvores são iguais\n");
    } else {
        printf("As árvores não são iguais\n");
    } 
    
    return 0;
}                