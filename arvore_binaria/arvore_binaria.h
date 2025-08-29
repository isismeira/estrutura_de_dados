typedef struct arvbin TAB;

TAB* TAB_inicializa(void);

TAB* TAB_cria(int raiz, TAB* esq, TAB* dir);

TAB* v2ab(int *vet, int n);

void TAB_imp_pre(TAB* a);

void TAB_imp_sim(TAB* a);

void TAB_imp_pos(TAB* a);

void TAB_libera(TAB* a);

TAB* TAB_busca(TAB* a, int x);

int nivel(TAB* a, int x);

int naux(TAB *a, int x, int resp);