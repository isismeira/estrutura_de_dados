#include "TH_MS.h"

int main(void){
  int n, m;
  printf("Digite m... ");
  scanf("%d", &m);
  printf("Digite n... ");
  scanf("%d", &n);

  if((n <= 1) || (m <= 1)) return 0;

  char nome_dados[31], nome_hash[31];
  printf("Digite nome do arquivo de dados... ");
  scanf("%s", nome_dados);
  printf("Digite nome do arquivo de hash... ");
  scanf("%s", nome_hash);

  TH_inicializa(nome_hash, nome_dados, m);

  int i, mat;
  float cr;
  for(i = 0; i < n; i++){
    printf("Digite a matricula e o cr...\n");
    scanf("%d", &mat);
    scanf("%f", &cr);
    TH_insere(nome_hash, nome_dados, m, mat, cr);
  }
  TH_imprime(nome_hash, nome_dados, m);

  char resp;
  do{
    printf("Digite a matricula a ser removida... ");
    scanf("%d", &mat);
    cr = TH_retira(nome_hash, nome_dados, m, mat);
    if(cr != -1) printf("%d %f saiu\n", mat, cr);
    printf("Quer continuar? ");
    scanf(" %c", &resp);
  }while((resp != 'N') && (resp != 'n'));
  TH_imprime(nome_hash, nome_dados, m);

  printf("Digite a matricula a ser procurada... ");
  scanf("%d", &mat);
  TA *r = TH_busca(nome_hash, nome_dados, m, mat);
  if(!r)
    printf("Elemento nao encontrado!\n");
  else{
    printf("matricula: %d\tstatus: %d\tprox_end: %d\n", r->mat, r->status, r->prox);
    free(r);
  }
  
  do{
    printf("Digite a matricula e o cr... ");
    scanf("%d", &mat);
    scanf("%f", &cr);
    TH_insere(nome_hash, nome_dados, m, mat, cr);
    printf("Quer continuar? ");
    scanf(" %c", &resp);
  }while((resp != 'N') && (resp != 'n'));
  TH_imprime(nome_hash, nome_dados, m);

  return 0;
}
