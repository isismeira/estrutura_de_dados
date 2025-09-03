typedef struct arvbin TAB;

TAB* TAB_inicializa(void);
TAB* TAB_cria(int raiz, TAB* esq, TAB* dir);
void TAB_imp_pre(TAB* a);
int igual(TAB* a1, TAB* a2);