#include <stdio.h>
#include <stdlib.h>
#include "q003.h"

// gcc -o q003usa.exe q003usa.c q003.c -lm
// .\q003usa.exe

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

    
    int distancia_2_7 =  distancia_dois_nos(arv, 2, 7);
    printf("Distancia: %i", distancia_2_7);
    int distancia_15_7 =  distancia_dois_nos(arv, 15, 7);
    printf("Distancia: %i", distancia_15_7);
    
    return 0;
}