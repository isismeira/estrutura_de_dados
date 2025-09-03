typedef struct arvbin TAB;

TAB* TAB_inicializa(void);
TAB* TAB_cria(int raiz, TAB* esq, TAB* dir);
void TAB_imp_pre(TAB* a);
TAB* retira_pares(TAB* arv);