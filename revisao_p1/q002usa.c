#include <stdio.h>
#include <stdlib.h>
#include "q002.h"

// gcc -o q002usa.exe q002usa.c q002.c -lm
// .\q002usa.exe

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

    int altura = 3;
    int tam_vet = altura;
    
    printf("Árvore criada com altura: %d\n", altura);
    
    int* medias = media(arv, &tam_vet);
    
    if (medias != NULL) {
        printf("Médias por nível:\n");
        for (int i = 0; i < tam_vet; i++) {
            printf("Nível %d: média = %d\n", i, medias[i]);
        }
        
        free(medias);
    } else {
        printf("Árvore vazia!\n");
    }
    
    TAB_libera(arv);
    
    return 0;
}