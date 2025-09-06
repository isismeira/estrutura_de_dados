typedef struct abb TABB;

typedef struct abb {
    int info;
    struct abb *esq, *dir;
}TABB;


TABB *TABB_inicializa(void);
TABB *TABB_cria(int raiz, TABB *esq, TABB *dir);

void TABB_imp_sim(TABB *a);

TABB *TABB_retira(TABB *a, int info);

int* mN(TABB* a, int N);
void aux_mN(TABB* a, int valor, int* vetor, int* contador);