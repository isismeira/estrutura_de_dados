#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALOR_MIN -2000000000

void inicializa(int *mp, int n){
  int i;
  for(i = 0; i < n; i++) mp[i] = VALOR_MIN;
}

void geraNomePart(char *saida, char *inicio, int parte){
  char aux[5];
  strcpy(saida, inicio);
  sprintf(aux, "%d", parte);
  strcat(saida, aux);
  strcat(saida, ".txt");
}

void descobreMenor(int *mp, int MAX_MP, int *menor, int *menor_ind){
  int i, j = 0;
  (*menor) = VALOR_MIN;
  (*menor_ind) = MAX_MP;
  while(j < MAX_MP){
    if(mp[j] != VALOR_MIN){
      (*menor) = mp[j];
      (*menor_ind) = j;
      break;
    }
    j++;
  }  
  for(i = j + 1; i < MAX_MP; i++) 
    if((mp[i] < (*menor)) && (mp[i] != VALOR_MIN)){
      (*menor) = mp[i];
      (*menor_ind) = i;
    }
}

int selNat(char *in, char *out, int MAX_MP, int MAX_RES){
  int mp[MAX_MP], res[MAX_RES], ind_res = 0;
  int part = 0;
  char nome_part[51];

  geraNomePart(nome_part, out, ++part);

  FILE *fp = fopen(in, "rt"), *fpart;
  if(!fp) exit(1);

  inicializa(mp, MAX_MP);
  inicializa(res, MAX_RES);
  int i, r, aux;
  for(i = 0; i < MAX_MP; i++){
    r = fscanf(fp, "%d", &aux);
    if(r != 1)break;
    mp[i] = aux;
  }

  int menor, menor_ind;
  if(i){
    fpart = fopen(nome_part,"wt");
    if(!fpart)exit(1);
    if(i < MAX_MP){
      fclose(fp);
      while(1){
        descobreMenor(mp, MAX_MP, &menor, &menor_ind);
        if(menor_ind == MAX_MP){
          fclose(fpart);
          break;
        }
        fprintf(fpart,"%d\n", menor);
        mp[menor_ind] = VALOR_MIN;
      }
      return part;
    }
  }
  else return 0;

  while(r == 1){
    if(ind_res == MAX_RES){
      for(i = 0; i < MAX_RES; i++) mp[i] = res[i];
      inicializa(res, MAX_RES);
      ind_res = 0;
      geraNomePart(nome_part, out, ++part);
      fpart = fopen(nome_part,"wt");
      if(!fpart) exit(1);
    }

    descobreMenor(mp, MAX_MP, &menor, &menor_ind);
    fprintf(fpart, "%d\n", menor);
    r = fscanf(fp, "%d", &aux);
    if(r == 1){
      if(aux > menor) mp[menor_ind] = aux;
      else{
        mp[menor_ind] = VALOR_MIN;
        while((r == 1) && (aux < menor)){
          res[ind_res++] = aux;
          if(ind_res == MAX_RES) break;
          r = fscanf(fp, "%d", &aux);
        }
        if(aux > menor) mp[menor_ind] = aux;
        else if((ind_res == MAX_RES) || (r != 1)){
          do{
            descobreMenor(mp, MAX_MP, &menor, &menor_ind);
            if(menor_ind == MAX_MP){
              fclose(fpart);
              break;
            }
            fprintf(fpart, "%d\n", menor);
            mp[menor_ind] = VALOR_MIN;
          }while(1);
        } //else if(r == 1)
      } //else
    } //if(r == 1)
    else{ // r e diferente de um...
      mp[menor_ind] = VALOR_MIN;
      do{
        descobreMenor(mp, MAX_MP, &menor, &menor_ind);
        if(menor_ind == MAX_MP){
          fclose(fpart);
          break;
        }
        fprintf(fpart, "%d\n", menor);
        mp[menor_ind] = VALOR_MIN;
      }while(1);
    }//else
  }//while
  fclose(fp);

  for(i = 0; i < MAX_RES; i++) if(res[i] != VALOR_MIN) break;
  if(i != MAX_RES){
    geraNomePart(nome_part, out, ++part);
    fpart = fopen(nome_part, "wt");
    if(!fpart) exit(1);
    while(1){
      descobreMenor(res, MAX_RES, &menor, &menor_ind);
      if(menor_ind == MAX_RES){
        fclose(fpart);
        break;
      }
      fprintf(fpart, "%d\n", menor);
      res[menor_ind] = VALOR_MIN;
    }
  }
  return part;
}

int main(void){
  char nome[31];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nome);

  char saida[31];
  printf("Digite o nome do arquivo de saida: ");
  scanf("%s",saida);

  int tam_mp, tam_res;
  printf("Digite o tamanho da memoria principal: ");
  scanf("%d", &tam_mp);

  printf("Digite o tamanho do reservatorio: ");
  scanf("%d", &tam_res);

  int n = selNat(nome, saida, tam_mp, tam_res);
  if(n == 1) printf("Selecao natural gerou 1 particao\n");
  else if(n > 1) printf("Selecao natural gerou %d particoes\n", n);

  return 0;
}
