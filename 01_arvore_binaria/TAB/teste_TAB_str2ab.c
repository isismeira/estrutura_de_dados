#include <string.h>
#include "TAB.h"

//< 30 < 20 < > < > > < 40 < > < > > >
int acha_sub_arv_bin(char *str, int menor, int maior){
  if((maior == menor) && (menor)) return 0;
  if(str[0] == '<') return 1 + acha_sub_arv_bin(&str[1], menor + 1, maior);
  if(str[0] == '>') return 1 + acha_sub_arv_bin(&str[1], menor, maior + 1);
  return 1 + acha_sub_arv_bin(&str[1], menor, maior);
}

TAB *aux(char *str, int ini, int fim){
  if(!strncmp(&str[ini], "< >", (fim - ini + 1))) return NULL;
  ini += 2; //str[ini] == '<'
  char saux[strlen(str)];
  int i = 0;
  while(str[ini] != ' ') saux[i++] = str[ini++];
  saux[i] = '\0';
  int fim_esq = acha_sub_arv_bin(&str[ini + 1], 0, 0) + ini, 
      fim_dir = acha_sub_arv_bin(&str[fim_esq + 2], 0, 0) + fim_esq + 1;
  printf("esq = (%d,%d)\tdir = (%d,%d)\n", ini + 1, fim_esq, fim_esq + 2, fim_dir); 
  return TAB_cria (atoi(saux), aux(str, ini + 1, fim_esq), aux(str, fim_esq + 2, fim_dir));
}

TAB *str2ab(char *str){
  if(!str[0]) return NULL;
  return aux(str, 0, strlen(str) - 1);
}

int main(void){
  char ent[1001];
  scanf(" %1000[^\n]", ent);
  TAB *a = str2ab(ent);
  printf("\n");
  TAB_imp_ident(a);
  TAB_libera(a);
  return 0;
}
