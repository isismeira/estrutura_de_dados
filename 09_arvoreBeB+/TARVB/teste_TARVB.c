#include "TARVB.h"

// gcc -o teste_TARVB.exe teste_TARVB.c TARVB.c -lm
// .\teste_TARVB.exe
int main(){

  TARVB *arvore = TARVB_Inicializa();
  int t;
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num = 0;
  int from;
  while(num != -1){
    printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
    scanf("%d", &num);
    if(num == -9){
      scanf("%d", &from);
      arvore = TARVB_Retira(arvore, from, t);
      TARVB_Imprime2(arvore);
    }
    else if(num == -1){
      printf("\n");
      TARVB_Imprime2(arvore);
      TARVB_Libera(arvore);
      return 0;
    }
    else if(!num){
      printf("\n");
      TARVB_Imprime2(arvore);
    }
    else arvore = TARVB_Insere(arvore, num, t);
    printf("\n\n");
  }
  return 0;
}
