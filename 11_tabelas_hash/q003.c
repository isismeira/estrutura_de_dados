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

void misc(char *arqa, char *arqb, char *saida, int K) {
    char dados[] = "dados_a.bin";
    char tabHash[] = "hash_a.bin";

    TH_inicializa(dados, tabHash, K);

    FILE *fa = fopen(arqa, "rb");
    if(!fa) { printf("Erro ao abrir %s\n", arqa); return; }

    int num;
    while(fread(&num, sizeof(int), 1, fa) == 1) {
        int resto = num % K;
        if(resto < 0) resto += K;

        TH_insere(tabHash, dados, K, num);
    }
    fclose(fa);

    FILE *fb = fopen(arqb, "rb");
    if(!fb) { printf("Erro ao abrir %s\n", arqb); return; }

    FILE *fsaida = fopen(saida, "wb");
    if(!fsaida) { printf("Erro ao criar %s\n", saida); return; }

    FILE *fpDados = fopen(dados, "rb");
    FILE *fpHash = fopen(tabHash, "rb");

    int vet[K];
    fread(vet, sizeof(int), K, fpHash);

    while(fread(&num, sizeof(int), 1, fb) == 1) {
        int restoB = num % K;
        if(restoB < 0) restoB += K;

        int complemento = K - restoB;
        if(complemento == K) complemento = 0;

        int pos = vet[complemento];

        while(pos != -1) {
            TNUM nodo;
            fseek(fpDados, pos, SEEK_SET);
            fread(&nodo, sizeof(TNUM), 1, fpDados);

            int restoA = nodo.num % K;
            if(restoA < 0) restoA += K;

            if(restoA + restoB == K) {
                fwrite(&nodo.num, sizeof(int), 1, fsaida);
                fwrite(&num,      sizeof(int), 1, fsaida);
            }

            pos = nodo.prox;
        }
    }

    fclose(fb);
    fclose(fpDados);
    fclose(fpHash);
    fclose(fsaida);
}

void ler_saida(const char *saida) {
    FILE *fp = fopen(saida, "rb");
    if(!fp) {
        printf("Erro ao abrir arquivo de saída %s\n", saida);
        return;
    }

    int a, b;

    printf("\n--- CONTEÚDO DE %s ---\n", saida);

    while(1) {
        size_t l1 = fread(&a, sizeof(int), 1, fp);
        size_t l2 = fread(&b, sizeof(int), 1, fp);

        if(l1 != 1 || l2 != 1)
            break;

        printf("(%d, %d)\n", a, b);
    }

    fclose(fp);
    printf("--- FIM ---\n\n");
}

int main(int argc, char **argv) {
    if(argc != 5) {
        printf("USO CORRETO:\n");
        printf("  ./programa <arquivoA> <arquivoB> <arquivo_saida> <K>\n\n");
        printf("EXEMPLO:\n");
        printf("  ./programa A.bin B.bin pares.bin 10\n");
        return 1;
    }

    char *arqa  = argv[1];
    char *arqb  = argv[2];
    char *saida = argv[3];
    int K       = atoi(argv[4]);

    if(K <= 0) {
        printf("Erro: K deve ser um inteiro positivo.\n");
        return 1;
    }

    printf("Processando...\n");
    printf("Arquivo A: %s\n", arqa);
    printf("Arquivo B: %s\n", arqb);
    printf("Arquivo de saída: %s\n", saida);
    printf("K = %d\n", K);

    misc(arqa, arqb, saida, K);
    printf("Pares gravados em %s:\n", saida);
    ler_saida(saida);

    printf("Concluído! Resultados gravados em %s\n", saida);

    return 0;
}
