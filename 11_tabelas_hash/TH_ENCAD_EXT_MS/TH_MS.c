#include "TH_MS.h"

int TH_hash(int mat, int tam){
  return mat % tam; // calcula índice na tabela hash
}

void TH_inicializa(char *tabHash, char *dados, int n){
  FILE *fp = fopen(dados, "wb"); // abre arquivo para escrita (cria/sobrescreve)
  if(!fp) exit(1); // se não achou o arquivo, exit(1)
  fclose(fp); //fecha fp pois o arquivo de dados já foi inicializado

  fp = fopen(tabHash, "wb");  //abre arquivo para escrita (cria/sobrescreve)
  if(!fp) exit(1); // se não achou o arquivo, exit(1)
  int i, elem = -1;  // elem=-1
  for(i = 0; i < n; i++) fwrite(&elem, sizeof(int), 1, fp); // grava -1 em cada posição do arquivo
  fclose(fp); //fecha fp pois o arquivo de tabHash já foi inicializado
}

TA* TH_aloca(int mat, float cr){
  TA *novo = (TA*)malloc(sizeof(TA)); // aloca na memória RAM (não no arquivo)
  novo->mat = mat; 
  novo->cr = cr;
  novo->prox = -1; // -1 indica fim da lista
  novo->status = 1; // 1 = ativo
  return novo;
}

TA* TH_busca(char *tabHash, char *dados, int n, int mat){
  FILE *fp = fopen(tabHash,"rb"); // abre tabela hash para leitura
  if(!fp)exit(1);

  int pos, h = TH_hash(mat,n); // inicializa pos e o índice da hash
  fseek(fp, h*sizeof(int), SEEK_SET); // posiciona no indice correto
  fread(&pos, sizeof(int), 1, fp); // lê a posição inicial
  fclose(fp);

  if(pos == -1)return NULL; // se a posição corresponde a -1, a lista naquela posição está vazia

  fp = fopen(dados,"rb"); // abre arquivo de dados
  if(!fp) exit(1);

  fseek(fp, pos, SEEK_SET); // vai a posição do primeiro elemento
  TA aux;
  fread(&aux, sizeof(TA), 1, fp); // lê o registro

  while(1){
    if((aux.mat == mat) && (aux.status)){ // se encontrou e está ativo
      TA *resp = TH_aloca(aux.mat, aux.cr); // cria cópia em MP
      resp->prox = aux.prox; // atribui proximo
      fclose(fp); // fecha arquivo
      return resp; // retora o ponteiro
    }
    if(aux.prox == -1){ // se chegou ao fim da lista (não achou nada)
      fclose(fp);
      return NULL;
    }
    fseek(fp, aux.prox, SEEK_SET); // vai para a posição do próximo elemento
    fread(&aux, sizeof(TA), 1, fp); // lê o registro
  }
}

float TH_retira(char *tabHash, char *arq, int n, int mat){
  FILE *fp = fopen(tabHash,"rb");
  if(!fp) exit(1);

  int pos, h = TH_hash(mat,n);
  fseek(fp, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fp);
  fclose(fp);

  if(pos == -1) return -1; // não encontrou

  float cr = -1; 
  fp = fopen(arq,"rb+"); // abre arquivo de dados para leitura e escrita
  if(!fp) exit(1);

  TA aux;
  while(1){
    fseek(fp, pos, SEEK_SET); // vai a posição do primeiro elemento
    fread(&aux, sizeof(TA), 1, fp); // lê o registro

    if((aux.mat == mat) && (aux.status)){ // se encontrou e está ativo
      cr = aux.cr;  // captura aquele cr
      aux.status = 0; // marca como removido
      fseek(fp, pos, SEEK_SET); // reposiciona o ponteiro do arquivo para a mesma posição onde o registro foi lido
      fwrite(&aux, sizeof(TA), 1, fp); // reescreve o registro no arquivo, agora com status = 0
      fclose(fp);
      return cr;
    }

    if(aux.prox == -1){  // fim da lista 
      fclose(fp);
      return cr; // retorna -1 (não encontrado)
    }
    pos = aux.prox;
  }
}

void TH_insere(char *tabHash, char *arq, int n, int mat, float cr){
  FILE *fph = fopen(tabHash, "rb+"); // abre tabela hash para leitura/escrita
  if(!fph) exit(1);

  int pos, h = TH_hash(mat, n);
  fseek(fph, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fph); // lê posição inicial da lista

  int ant, prim_pos_livre;
  ant = prim_pos_livre = -1;

 
  FILE *fp = fopen(arq,"rb+");
  if(!fp){
    fclose(fph);
    exit(1);
  }

  TA aux;

  // FASE 1: Percorre a lista procurando pela matrícula e por espaço livre
  while(pos != -1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(TA), 1, fp);

    if(aux.mat == mat){ // Matrícula já existe
      aux.cr = cr; // Atualiza CR
      aux.status = 1; // Reativa se necessário
      fseek(fp, pos, SEEK_SET);
      fwrite(&aux, sizeof(TA), 1, fp);
      fclose(fp);
      fclose(fph);
      return;
    }

     // Guarda primeira posição livre encontrada
    if((!aux.status) && (prim_pos_livre == -1))prim_pos_livre=pos;
    ant = pos; // Guarda posição anterior
    pos = aux.prox; // Avança para próximo
  }

  // FASE 2: Inserção de novo elemento
  if(prim_pos_livre == -1){ // Não há espaço livre, insere no final
    aux.mat = mat;
    aux.cr = cr;
    aux.prox = -1;
    aux.status = 1;

    fseek(fp, 0L, SEEK_END); // Vai para o final do arquivo
    pos = ftell(fp); // Pega posição atual (novo endereço)
    fwrite(&aux, sizeof(TA), 1, fp); // Escreve novo registro

    if(ant != -1){ // Há elemento anterior - atualiza seu ponteiro
      fseek(fp, ant, SEEK_SET);
      fread(&aux, sizeof(TA), 1, fp);
      aux.prox = pos;
      fseek(fp, ant, SEEK_SET);
      fwrite(&aux, sizeof(TA), 1, fp);
    }
    else{ // É o primeiro elemento - atualiza tabela hash
      fseek(fph, h*sizeof(int), SEEK_SET);
      fwrite(&pos, sizeof(int), 1, fph);
    }
    fclose(fp);
    fclose(fph);
    return;
  }
  // Reutiliza espaço livre
  fseek(fp, prim_pos_livre, SEEK_SET);
  fread(&aux, sizeof(TA), 1, fp);
  aux.mat = mat;
  aux.cr = cr;
  aux.status = 1;
  fseek(fp, prim_pos_livre, SEEK_SET);
  fwrite(&aux, sizeof(TA), 1, fp);
  fclose(fp);
  fclose(fph);
  return;
}

void TH_imprime (char *nome_hash, char *nome_dados, int m){
  FILE *fp = fopen(nome_hash, "rb");
  if(!fp) exit(1);
  int vet[m];
  fread(&vet, sizeof(int), m, fp);
  fclose(fp);

  fp = fopen(nome_dados, "rb");
  if(!fp) exit(1);
  int i, pos;
  for(i = 0; i < m; i++){
    int p = vet[i];
    if(p != -1) printf("%d:\n", i);
    TA x;
    while(p != -1){
      fseek(fp, p, SEEK_SET);
      pos = ftell (fp);
      fread(&x, sizeof(TA), 1, fp);
      printf("$%d: matricula: %d\tcr: %f\tstatus: %d\tprox_end: $%d\n", pos, x.mat, x.cr, x.status, x.prox);
      p = x.prox;
    }
  }
  fclose(fp);
}
