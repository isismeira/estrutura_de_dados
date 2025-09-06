typedef struct arvbusca {
    char nome[20];   // nome da figura
    int dim[4];      // até 4 dimensões
    int area;        // chave de comparação
    struct arvbusca *esq, *dir;
} TABB;

TABB* TABB_inicializa(TABB* a);
TABB* TABB_cria(char* n, int* d, TABB* esq, TABB* dir);
void TABB_imp_sim(TABB *a);
TABB* TABB_insere(TABB* a, char* nome, int* d);
TABB* TABB_busca(TABB* a, int area);
TABB* TABB_retira(TABB* a, int area);