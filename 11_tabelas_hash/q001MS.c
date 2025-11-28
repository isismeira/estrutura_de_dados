#include <stdio.h>
#include <stdlib.h>

// ===========================================================================================================================================================================================================================
typedef struct numeros {
    int valor;
    int prox;
    int status;
} TN;

int TH_hash(int x, int n){
    return x % n;
}

/* Inicializa tabela hash (arquivo tabHash) e arquivo de dados */
void TH_inicializa(char *tabHash, char *dados, int n){
    FILE *fp;

    /* inicializa arquivo de dados vazio */
    fp = fopen(dados, "wb");
    if(!fp){ printf("Erro inic dados\n"); exit(1); }
    fclose(fp);

    /* inicializa tabela hash com -1 */
    fp = fopen(tabHash, "wb");
    if(!fp){ printf("Erro inic hash\n"); exit(1); }

    int vazio = -1;
    for(int i=0;i<n;i++)
        fwrite(&vazio, sizeof(int), 1, fp);

    fclose(fp);
}

/* Carrega TN em RAM */
TN *TH_aloca(int v){
    TN *n = malloc(sizeof(TN));
    n->valor = v;
    n->prox = -1;
    n->status = 1;
    return n;
}

/* Busca no arquivo */
TN* TH_busca(char *tabHash, char *dados, int n, int v){
    FILE *fph = fopen(tabHash,"rb");
    if(!fph) exit(1);

    int pos;
    int h = TH_hash(v,n);
    fseek(fph, h*sizeof(int), SEEK_SET);
    fread(&pos, sizeof(int), 1, fph);
    fclose(fph);

    if(pos == -1) return NULL;

    FILE *fp = fopen(dados,"rb");
    if(!fp) exit(1);

    TN aux;
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(TN), 1, fp);

    while(1){
        if(aux.status && aux.valor == v){
            TN *resp = TH_aloca(aux.valor);
            resp->prox = aux.prox;
            resp->status = aux.status;
            fclose(fp);
            return resp;
        }
        if(aux.prox == -1){
            fclose(fp);
            return NULL;
        }
        fseek(fp, aux.prox, SEEK_SET);
        fread(&aux, sizeof(TN), 1, fp);
    }
}

/* Remove logicamente */
int TH_retira(char *tabHash, char *dados, int n, int v){
    FILE *fph = fopen(tabHash,"rb");
    if(!fph) exit(1);

    int pos, h = TH_hash(v,n);
    fseek(fph, h*sizeof(int), SEEK_SET);
    fread(&pos, sizeof(int), 1, fph);
    fclose(fph);

    if(pos == -1) return -1;

    FILE *fp = fopen(dados,"rb+");
    if(!fp) exit(1);

    TN aux;
    int atual = pos;

    while(1){
        fseek(fp, atual, SEEK_SET);
        fread(&aux, sizeof(TN), 1, fp);

        if(aux.status && aux.valor == v){
            aux.status = 0;
            fseek(fp, atual, SEEK_SET);
            fwrite(&aux, sizeof(TN), 1, fp);
            fclose(fp);
            return 1;
        }
        if(aux.prox == -1){
            fclose(fp);
            return -1;
        }
        atual = aux.prox;
    }
}

/* Insere na cadeia */
void TH_insere(char *tabHash, char *dados, int n, int v){
    FILE *fph = fopen(tabHash,"rb+");
    if(!fph) exit(1);

    int pos, h = TH_hash(v,n);
    fseek(fph, h*sizeof(int), SEEK_SET);
    fread(&pos, sizeof(int), 1, fph);

    FILE *fp = fopen(dados,"rb+");
    if(!fp){ fclose(fph); exit(1); }

    int ant = -1;
    int livre = -1;
    TN aux;

    int atual = pos;
    /* percorre lista */
    while(atual != -1){
        fseek(fp, atual, SEEK_SET);
        fread(&aux, sizeof(TN), 1, fp);

        if(aux.valor == v && aux.status == 1){
            fclose(fp);
            fclose(fph);
            return;
        }

        if(aux.status == 0 && livre == -1)
            livre = atual;

        ant = atual;
        atual = aux.prox;
    }

    /* novo registro */
    TN novo;
    novo.valor = v;
    novo.status = 1;
    novo.prox = -1;

    int novo_pos;

    /* usa área livre se existir */
    if(livre != -1){
        fseek(fp, livre, SEEK_SET);
        fwrite(&novo, sizeof(TN), 1, fp);
        novo_pos = livre;
    } else {
        fseek(fp, 0L, SEEK_END);
        novo_pos = ftell(fp);
        fwrite(&novo, sizeof(TN), 1, fp);
    }

    /* liga na cadeia */
    if(ant == -1){
        fseek(fph, h*sizeof(int), SEEK_SET);
        fwrite(&novo_pos, sizeof(int), 1, fph);
    } else {
        fseek(fp, ant, SEEK_SET);
        fread(&aux, sizeof(TN), 1, fp);
        aux.prox = novo_pos;
        fseek(fp, ant, SEEK_SET);
        fwrite(&aux, sizeof(TN), 1, fp);
    }

    fclose(fp);
    fclose(fph);
}

void TH_imprime(char *tabHash, char *dados, int n){
    FILE *fph = fopen(tabHash,"rb");
    int vet[n];
    fread(vet, sizeof(int), n, fph);
    fclose(fph);

    FILE *fp = fopen(dados,"rb");
    TN aux;

    for(int i=0;i<n;i++){
        int p = vet[i];
        printf("%d:\n",i);

        while(p != -1){
            fseek(fp,p,SEEK_SET);
            fread(&aux,sizeof(TN),1,fp);
            printf("  $%d: valor=%d status=%d prox=$%d\n",
                   p, aux.valor, aux.status, aux.prox);
            p = aux.prox;
        }
    }
    fclose(fp);
}

// ==================================================================================================================================================================================================================

// Interseção de conjuntos em MS
void inter(char* arq1, char* arq2, char* saida) {
    char tabHash[] = "hash.bin";
    char dados[] = "dados.bin";
    int n = 100003;

    TH_inicializa(tabHash, dados, n);

    FILE *f1 = fopen(arq1, "r");
    FILE *f2 = fopen(arq2, "r");
    FILE *out = fopen(saida, "w");

    int x;

    // Insere todos número de arq1 na hash
    while (fscanf(f1, "%d", &x) == 1)
        TH_insere(tabHash, dados, n, x);


    // Para cada número de arq 2, procura ele na Hash e se ele estiver lá, grava no output
    while (fscanf(f2, "%d", &x) == 1) {
        TN *p = TH_busca(tabHash, dados, n, x);
        if (p) fprintf(out, "%d\n", x);
    }

    fclose(f1);
    fclose(f2);
    fclose(out);
}

// Diferença simétrica de conjuntos em MS
void dif_sim(char* arq1, char* arq2, char* saida) {
    char tabHash[] = "hash.bin";
    char dados[] = "dados.bin";
    int n = 100003;

    TH_inicializa(tabHash, dados, n);

    FILE* f1 =  fopen(arq1, "r");
    FILE* f2 =  fopen(arq2, "r");
    FILE* out = fopen(saida, "w");

    int x;
    while (fscanf(f1, "%d", &x) == 1)
        TH_insere(tabHash, dados, n, x);

    int y;    
    while (fscanf(f2, "%d", &y) == 1) {
        if (TH_busca(tabHash, dados, n, y)) { //!
            TH_retira(tabHash,dados, n, y);
        } else {
            TH_insere(tabHash, dados, n, y);
        }    
    }
    
    FILE *dadosfp = fopen(dados, "rb");
    TN aux;

    while (fread(&aux, sizeof(TN), 1, dadosfp)) {
        if (aux.status == 1)
            fprintf(out, "%d\n", aux.valor);
    }
    
    fclose(f1);
    fclose(f2);
    fclose(dadosfp);
    fclose(out);
}

// União de conjuntos em MS
void uniao(char* arq1, char* arq2, char* saida) {
    char tabHash[] = "hash.bin";
    char dados[] = "dados.bin";
    int n = 100003;

    TH_inicializa(tabHash, dados, n);

    FILE* f1 =  fopen(arq1, "r");
    FILE* f2 =  fopen(arq2, "r");
    FILE* out = fopen(saida, "w");

    // !!!
    int x;
    while(fscanf(f1,"%d",&x)==1)
        TH_insere(tabHash,dados,n,x);

    while(fscanf(f2,"%d",&x)==1)
        TH_insere(tabHash,dados,n,x);

    FILE *fp=fopen(dados,"rb");
    TN aux;
    while(fread(&aux,sizeof(TN),1,fp))
        if(aux.status==1)
            fprintf(out,"%d\n",aux.valor);

    fclose(fp);
    fclose(f1);
    fclose(f2);
    fclose(out);
}

int main(){
    printf("INTER MS -> saida_inter.txt\n");
    inter("A.txt","B.txt","saida_inter.txt");

    printf("DIF SIM MS -> saida_difsim.txt\n");
    dif_sim("A.txt","B.txt","saida_difsim.txt");

    printf("UNIAO MS -> saida_uniao.txt\n");
    uniao("A.txt","B.txt","saida_uniao.txt");

    return 0;
}