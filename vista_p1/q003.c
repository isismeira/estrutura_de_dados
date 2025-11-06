#include <stdio.h>
#include <stdlib.h>

int maior(int x, int y){
  if(x >= y) return x;
  return y;
}

int TAB_altura(TAB *a){
  if(!a) return -1;
  return maior(TAB_altura(a->esq), TAB_altura(a->dir)) + 1;
}

void imprime_zz_level(TAB* a, int nivel, int esqdir){
    if(!a) return;
    if(nivel == 0){
        printf("%d ", a->info);
    } else if(nivel > 0){
        if (esqdir) {
            imprime_zz_level(a->esq, nivel-1, esqdir);
            imprime_zz_level(a->dir, nivel-1, esqdir);
        } else {
            imprime_zz_level(a->dir, nivel-1, esqdir);
            imprime_zz_level(a->esq, nivel-1, esqdir);
        }
    }
}


void imprime_zz_total(TAB* a){
    int h = altura(a);
    printf("%i\n", h);
    for(int i = 0; i <= h-1; i++){
        int esqdir = (i % 2 == 0);
        imprime_zz_level(a, i, esqdir);
    }
}
// ---
int main(){
    TAB* a = cria(40,
                  cria(20, cria(10,NULL,NULL), cria(30,NULL,NULL)),
                  cria(60, cria(50,NULL,NULL), cria(70,NULL,NULL)));

    printf("Impressao em zigue-zague:\n");
    imprime_zz_total(raiz);
    printf("\n");
    return 0;
}
