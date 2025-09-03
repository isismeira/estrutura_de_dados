typedef struct arvbin TAB;

TAB* TAB_inicializa(void);

TAB* TAB_cria(int raiz, TAB* esq, TAB* dir);

TAB* copia(TAB* a);