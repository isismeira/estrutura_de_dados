#include <stdio.h>
#include <stdlib.h>
#include "q003_q004.h"

// gcc -o q003_q004usa.exe q003_q004usa.c q003_q004.c -lm
// .\q003_q004usa.exe

int main() {
    /* Montando a árvore:
           10
          /  \
         5    20
        /  \  /
       3   7 15       */

    TAB* arv = TAB_cria(10,
                    TAB_cria(5,
                        TAB_cria(3, NULL, NULL),
                        TAB_cria(7, NULL, NULL)
                    ),
                    TAB_cria(20,
                        TAB_cria(15, NULL, NULL),
                        NULL
                    )
                );

    printf("Arvore original (in-order): ");
    TAB_imp_pre(arv);
    printf("\n");
    
    TAB* menor_valor = menor(arv);
    printf("O menor valor eh", menor_valor->info);

    TAB* maior_valor = maior(arv);
    printf("O maior valor eh", maior_valor->info);
    
    /*
1. **Chamada inicial**: `maior(10)`

   * Vai chamar `maior(5)` e `maior(20)`.

2. **Chamando `maior(5)`**:

   * Chama `maior(3)` → retorna nó `3` (folha).
   * Chama `maior(7)` → retorna nó `7` (folha).
   * Assume `max = 5`.
   * Compara:

     * `3` > `5`? ❌
     * `7` > `5`? ✅ → agora `max = 7`.
   * Retorna **nó 7**.

3. **Chamando `maior(20)`**:

   * Chama `maior(15)` → retorna nó `15` (folha).
   * Chama `maior(NULL)` → retorna `NULL`.
   * Assume `max = 20`.
   * Compara:

     * `15` > `20`? ❌
     * `NULL` → ignora.
   * Retorna **nó 20**.

4. **Voltando para `maior(10)`**:

   * `max_esq = nó 7`
   * `max_dir = nó 20`
   * Assume `max = 10`.
   * Compara:

     * `7` > `10`? ❌
     * `20` > `10`? ✅ → agora `max = 20`.
   * Retorna **nó 20**.
*/

    return 0;
}