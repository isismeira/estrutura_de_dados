#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALOR_MIN -2000000000

typedef struct dado{
  int info, cong;
}TDado;

void inicializaMP(TDado *mp, int n){
  int i;
  for(i = 0; i < n; i++){
    mp[i].info = VALOR_MIN;
    mp[i].cong = 1;
  }
}

//Procedimento que recebe parte do nome (isto e, inicio), junta com o inteiro 
//parte e finaliza com ".txt". A string e escrita em saida. 
void geraNomePart(char *saida, char *inicio, int parte){ //Rosseti: 2016/09/20
  char aux[5];
  strcpy(saida, inicio);
  sprintf(aux, "%d", parte);
  strcat(saida, aux);
  strcat(saida, ".txt");
}

//Funcao que conta o numero de elementos congelados diferentes de 
//menos infinito. Ela retorna zero se existem elementos descongelados ou 
//se todos os congelados sao iguais a VALOR_MIN, ou o numero de 
//elementos congelados diferentes de VALOR_MIN.
int existeElemCongDifMenosInf(TDado *mp, int n){
  int achou = 0, i;
  for(i = 0; i < n; i++){
    if(!mp[i].cong) return 0;
    if(mp[i].info != VALOR_MIN) achou++;
  }
  return achou;
}

//Funcao que retorna o menor elemento descongelado e seu indice. Senao,
//ela retorna o indice igual a MAX_MP.
void descobreMenor(TDado *mp, int MAX_MP, int *menor, int *menor_ind){
  int i, j = 0;
  (*menor) = VALOR_MIN;
  (*menor_ind) = MAX_MP;
  while(j < MAX_MP){
    if(!mp[j].cong){
      (*menor) = mp[j].info;
      (*menor_ind) = j;
      break;
    }
    else j++;
  }  
  for(i = j + 1; i < MAX_MP; i++) 
    if((mp[i].info < (*menor)) && (!mp[i].cong) && (mp[i].info != VALOR_MIN)){
      (*menor) = mp[i].info;
      (*menor_ind) = i;
    }
}

//Funcao que faz a operacao de selecao com substituicao, retornando o 
//numero de particoes geradas. Ela recebe o nome do arquivo de entrada, 
//a parte do nome dos arquivos de particao e o tamanho de memoria usada 
//no processo.
int selSubst(char *in, char *out, int MAX_MP){
  TDado mp[MAX_MP];
  inicializaMP(mp, MAX_MP);
  int part = 0;
  char nome_part[51];

  geraNomePart(nome_part, out, ++part);

  FILE *fp = fopen(in, "rt"), *fpart;
  if(!fp) exit(1);

  //preenche a MP.
  int i, r, aux;
  for(i = 0; i < MAX_MP; i++){
    r = fscanf(fp, "%d", &aux);
    if(r != 1)break;
    mp[i].info = aux;
    mp[i].cong = 0;
  }

  //se o arquivo de entrada nao esta vazio.
  int menor, menor_ind; //Rosseti: 2016/09/20
  if(i){
    fpart = fopen(nome_part,"wt");
    if(!fpart)exit(1);
    //se o arquivo de entrada e menor que a MP.
    if(i < MAX_MP){ //Rosseti: 2016/09/20
      fclose(fp);
      while(1){
        descobreMenor(mp, MAX_MP, &menor, &menor_ind);
        if(menor_ind == MAX_MP){
          fclose(fpart);
          break;
        }
        fprintf(fpart,"%d\n", menor);
        mp[menor_ind].info = VALOR_MIN;
        mp[menor_ind].cong = 1;
      }
      return part;
    }
  }

  //quando o arquivo e maior que a MP, faca leitura de 
  //dados ate encontrar o final do arquivo de entrada.
  while(r == 1){
    //se a MP esta toda congelada com elementos do arquivo.
    if(existeElemCongDifMenosInf(mp, MAX_MP)){
      //fecha a particao.
      fclose(fpart);
      //descongela a MP.
      for(i = 0; i < MAX_MP; i++) if(mp[i].info != VALOR_MIN) mp[i].cong = 0;
      //gera a nova particao.
      geraNomePart(nome_part, out, ++part);
      fpart = fopen(nome_part,"wt");
      if(!fpart) exit(1);
    }

    //realiza o processo de selecao por substituicao, escolhendo o 
    //menor elemento, colocando-o na particao e obtendo o proximo 
    //elemento a entrar na MP.
    descobreMenor(mp, MAX_MP, &menor, &menor_ind);
    fprintf(fpart, "%d\n", menor);
    r = fscanf(fp, "%d", &aux);
    if(r == 1){
      mp[menor_ind].info = aux;
      //se o elemento que entrou na particao era maior que o ultimo lido,
      //congela a particao.
      if(aux < menor) mp[menor_ind].cong = 1;
    }
    else{
      //se nao existe mais dado no arquivo, preenche a MP com os valores iniciais.
      mp[menor_ind].info = VALOR_MIN;
      mp[menor_ind].cong = 1;
      //copia todos os elementos que devem estar na particao atual e nao foram 
      //incluidos ainda.
      do{
        descobreMenor(mp, MAX_MP, &menor, &menor_ind);
        if(menor_ind == MAX_MP){
          fclose(fpart);
          break;
        }
        fprintf(fpart, "%d\n", menor);
        mp[menor_ind].info = VALOR_MIN;
        mp[menor_ind].cong = 1;
      }while(1);
    }//else
  }//while
  fclose(fp);

  //se existem elementos congelados e preciso abrir uma nova particao e 
  //inseri-los nela.
  for(i = 0; i < MAX_MP; i++) if(mp[i].info != VALOR_MIN) break;
  if(i != MAX_MP){
    int j;
    for(j = i; j < MAX_MP; j++) if(mp[j].info != VALOR_MIN) mp[j].cong = 0;
    geraNomePart(nome_part, out, ++part);
    fpart = fopen(nome_part, "wt");
    if(!fpart) exit(1);
    while(1){
      descobreMenor(mp, MAX_MP, &menor, &menor_ind);
      if(menor_ind == MAX_MP){
        fclose(fpart);
        break;
      }
      fprintf(fpart, "%d\n", menor);
      mp[menor_ind].info = VALOR_MIN;
      mp[menor_ind].cong = 1;
    }
  }
  return part;
}

int main(void){ //Rosseti: 2016/09/20
  char nome[31];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nome);
  /*
  FILE *fp = fopen(nome, "wt");
  if(!fp) exit(1);
  int nvet, i = 0, aux;
  printf("Digite o numero de elementos distintos do arquivo: ");
  scanf("%d", &nvet);
  while (i < nvet){
    scanf("%d", &aux);
    if(aux >= 0){ 
      fprintf(fp,"%d\n",aux);
      i++;
    }
  }
  fclose(fp);
  */
  char saida[31];
  printf("Digite o pedaco do nome do arquivo de particao: ");
  scanf("%s",saida);

  printf("Digite o tamanho (maior que zero) da memoria principal: ");
  int tam;
  while(1){
    scanf("%d",&tam);
    if(tam > 0)break;
  }

  int n = selSubst(nome, saida, tam);
  if(n == 1)printf("Selecao com substituicao gerou %d particao\n",n);
  else if(n > 1)printf("Selecao com substituicao gerou %d particoes\n",n);

  return 0;
}
