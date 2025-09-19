#include "TG.h"

int main(void){
  TG *g = TG_inicializa();
  int n;
  do{
    scanf("%d", &n);
    if(n <= 0) break;
    g = TG_ins_no(g, n);
    TG_imprime(g);
  }while(1);
  
  int m;
  do{
    scanf("%d%d", &n, &m);
    if((n <= 0) || (m <= 0)) break;
    TG_ins_aresta(g, n, m);
    TG_imprime(g);
  }while(1);
  
  char op;
  printf("Digite n ou a para retirar nos ou arestas...\n");
  do{
    scanf(" %c", &op);
    if(op == 'n'){
      scanf("%d", &n);
      g = TG_retira_no(g, n);
      TG_imprime(g);
    }
    else if(op == 'a'){
      scanf("%d%d", &n, &m);
      TG_retira_aresta(g, n, m);
      TG_imprime(g);
    }
    else break;
  }while(1);
  TG_libera(g);
  return 0;
}

