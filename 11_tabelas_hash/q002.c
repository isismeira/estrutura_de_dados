#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// =================================================================================================================================================================================================================================

typedef struct num{
  int num, prox, qtde;
}TNUM;

int TH_hash(int num, int tam){
  return num % tam;
}

void TH_inicializa(char *tabDados, char *tabHash, int tam){
  FILE *fp = fopen(tabDados, "wb");
  if(!fp) exit(1);
  fclose(fp);
  fp = fopen(tabHash, "wb");
  if(!fp) exit(1);
  int i, elem = -1;
  for(i = 0; i < tam; i++)fwrite(&elem, sizeof(int), 1, fp);
  fclose(fp);
}

TNUM* TH_aloca(int num){
  TNUM *novo = (TNUM*)malloc(sizeof(TNUM));
  novo->num = num;
  novo->prox = -1;
  novo->qtde = 1;
  return novo;
}

TNUM* TH_busca(char *tabHash, char *dados, int tam, int num){
  FILE *fp = fopen(tabHash, "rb");
  if(!fp)exit(1);
  int pos, h = TH_hash(num, tam);
  fseek(fp, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fp);
  fclose(fp);
  if(pos == -1)return NULL;
  fp = fopen(dados,"rb");
  if(!fp) exit(1);
  fseek(fp, pos, SEEK_SET);
  TNUM aux;
  fread(&aux, sizeof(TNUM), 1, fp);
  while(1){
    if((aux.num == num) && (aux.qtde)){
      TNUM *resp = TH_aloca(aux.num);
      resp->prox = aux.prox;
      fclose(fp);
      return resp;
    }
    if(aux.prox == -1){
      fclose(fp);
      return NULL;
    }
    fseek(fp, aux.prox, SEEK_SET);
    fread(&aux, sizeof(TNUM), 1, fp);
  }
}

void TH_retira(char *tabHash, char *dados, int tam, int num){
  FILE *fp = fopen(tabHash,"rb");
  if(!fp) exit(1);
  int pos, h = TH_hash(num, tam);
  fseek(fp, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fp);
  fclose(fp);
  if(pos == -1) return;
  fp = fopen(dados,"rb+");
  if(!fp)exit(1);
  TNUM aux;
  while(1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(TNUM), 1, fp);
    if((aux.num == num) && (aux.qtde)){
      aux.qtde--;
      fseek(fp, pos, SEEK_SET);
      fwrite(&aux, sizeof(TNUM), 1, fp);
      fclose(fp);
      return;
    }
    if(aux.prox == -1){
      fclose(fp);
      return;
    }
    pos = aux.prox;
  }
}

void TH_insere(char *tabHash, char *dados, int tam, int num){
  FILE *fph = fopen(tabHash, "rb+");
  if(!fph) exit(1);
  int pos, h = TH_hash(num, tam);
  fseek(fph, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fph);
  int ant, prim_pos_livre;
  ant = prim_pos_livre = -1;
  FILE *fp = fopen(dados,"rb+");
  if(!fp){
    fclose(fph);
    exit(1);
  }
  TNUM aux;
  while(pos != -1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(TNUM), 1, fp);
    if(aux.num == num){
      aux.qtde++;
      fseek(fp, pos, SEEK_SET);
      fwrite(&aux, sizeof(TNUM), 1, fp);
      fclose(fp);
      fclose(fph);
      return;
    }
    if((!aux.qtde) && (prim_pos_livre == -1))prim_pos_livre=pos;
    ant = pos;
    pos = aux.prox;
  }
  if(prim_pos_livre == -1){
    aux.num = num;
    aux.prox = -1;
    aux.qtde = 1;
    fseek(fp, 0L, SEEK_END);
    pos = ftell(fp);
    fwrite(&aux, sizeof(TNUM), 1, fp);
    if(ant != -1){
      fseek(fp, ant, SEEK_SET);
      fread(&aux, sizeof(TNUM), 1, fp);
      aux.prox = pos;
      fseek(fp, ant, SEEK_SET);
      fwrite(&aux, sizeof(TNUM), 1, fp);
    }
    else{
      fseek(fph, h*sizeof(int), SEEK_SET);
      fwrite(&pos, sizeof(int), 1, fph);
    }
    fclose(fp);
    fclose(fph);
    return;
  }
  fseek(fp, prim_pos_livre, SEEK_SET);
  fread(&aux, sizeof(TNUM), 1, fp);
  aux.num = num;
  aux.qtde = 1;
  fseek(fp, prim_pos_livre, SEEK_SET);
  fwrite(&aux, sizeof(TNUM), 1, fp);
  fclose(fp);
  fclose(fph);
  return;
}

void TH_imprime (char *tabHash, char *dados, int tam){
  FILE *fp = fopen(tabHash, "rb");
  if(!fp) exit(1);
  int vet[tam];
  fread(&vet, sizeof(int), tam, fp);
  fclose(fp);

  fp = fopen(dados, "rb");
  if(!fp) exit(1);
  int i, pos;
  for(i = 0; i < tam; i++){
    int p = vet[i];
    if(p != -1) printf("%d:\n", i);
    TNUM x;
    while(p != -1){
      fseek(fp, p, SEEK_SET);
      pos = ftell (fp);
      fread(&x, sizeof(TNUM), 1, fp);
      printf("$%d: num: %d\tqtde: %d\tprox_end: $%d\n", pos, x.num, x.qtde, x.prox);
      p = x.prox;
    }
  }
  fclose(fp);
}

// =================================================================================================================================================================================================================================

void misc(char **arqs, int n, int porc, char *saida){
    int tam = 10000;
    TH_inicializa("dados.dat", "hash.dat", tam);
    
    // Para cada arquivo, inserir os números na tabela hash
    int i;
    for(i = 0; i < n; i++){
        FILE *fp = fopen(arqs[i], "r");
        if(!fp) {
            printf("Erro ao abrir arquivo: %s\n", arqs[i]);
            continue;
        }
        int visto[100000] = {0}; 
        int num;
        while(fscanf(fp, "%d", &num) == 1){
            if(!visto[num]){     
                TH_insere("hash.dat", "dados.dat", tam, num);
                visto[num] = 1;
            }
        }
        fclose(fp);
    }
    
    // Agora buscar números que aparecem em pelo menos 'porc'% dos arquivo. Para isso, precisamos contar em quantos arquivos cada número aparece

    // Abre o arquivo de saida para escrita
    FILE *fp_saida = fopen(saida, "w");
    if(!fp_saida) {
        printf("Erro ao criar arquivo de saída\n");
        return;
    }

    // Abre hash.dat e passa todo vetor de indices em hash.dat para MP
    FILE *fph = fopen("hash.dat", "rb");
    if(!fph) {
        fclose(fp_saida);
        return;
    }  
    int vet[tam];
    fread(vet, sizeof(int), tam, fph);
    fclose(fph);
    
    // Abre dados.dat
    FILE *fp_dados = fopen("dados.dat", "rb");
    if(!fp_dados) {
        fclose(fp_saida);
        return;
    }
    
    // Calcular o mínimo de arquivos necessários baseado na porcentagem
    int min_arquivos = ceil((porc / 100.0) * n);
    
    printf("Procurando números que aparecem em pelo menos %d de %d arquivos (%d%%)\n", 
           min_arquivos, n, porc);
    
    // Percorre a tabela hash e navega pelas listas encadeadas  
    int i_hash;
    for(i_hash = 0; i_hash < tam; i_hash++){
        int pos = vet[i_hash]; // contém a posição em "dados.dat" onde está o primeiro elemento do bucket
        while(pos != -1){ // Percorre a lista encadeada até encontrar -1
            // Lê e guarda o elemento naqurla poscao 
            TNUM elemento; 
            fseek(fp_dados, pos, SEEK_SET);
            fread(&elemento, sizeof(TNUM), 1, fp_dados);
            
            // Se a quantidade é >= ao mínimo necessário, escreve no arquivo de saída
            if(elemento.qtde >= min_arquivos && elemento.qtde > 0){
                fprintf(fp_saida, "%d\n", elemento.num);
                printf("Número %d aparece em %d arquivos\n", elemento.num, elemento.qtde);
            }
            // Passa para o próximo elemento da lista encadaeada
            pos = elemento.prox;
        }
    }
    
    fclose(fp_dados);
    fclose(fp_saida);
    
    TH_imprime("hash.dat", "dados.dat", tam);
}

int main(int argc, char **argv){
  if(argc < 4) {
    printf("ERRO: <./nome_exec> <arq_saida> <porcentagem> <lista arquivos a serem pesquisados>\n");
    printf("Exemplo: ./programa resultado.txt 70 arquivo1.txt arquivo2.txt arquivo3.txt\n");
  }
  else{
    int n = argc - 3, i;
    char **arq = (char **)malloc(sizeof(char *) * n);
    for(i = 0; i < n; i++){
      arq[i] = (char *) malloc(sizeof(char) * 31);
      strcpy(arq[i], argv[i + 3]);
    }
    
    printf("Arquivos a processar:\n");
    for(i = 0; i < n; i++) printf("arq[%d] = %s\n", i, arq[i]);
    
    misc(arq, n, atoi(argv[2]), argv[1]);
    
    for(i = 0; i < n; i++) free(arq[i]);
    free(arq);
  }  
  return 0;
}