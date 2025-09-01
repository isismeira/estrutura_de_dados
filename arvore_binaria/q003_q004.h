typedef struct arvbin {
    int info;
    struct arvbin *esq, *dir;
} TAB;

TAB* TAB_inicializa(void);

TAB* TAB_cria(int raiz, TAB* esq, TAB* dir);

void TAB_imp_pre(TAB* a);

TAB* maior(TAB* a);

TAB* menor(TAB* a);