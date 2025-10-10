#include <stdio.h>
#include <stdlib.h>

typedef struct arvbin{
  int info;
  struct arvbin *esq, *dir;
}TAB;

typedef struct lseint{
  int lim_inf; 
  int lim_sup; 
  struct lseint *prox;
} TLSEINT;

TAB *TAB_inicializa(void);
TAB *TAB_cria(int raiz, TAB *esq, TAB *dir);

void TAB_imp_pre(TAB *a);
void TAB_imp_pos(TAB *a);
void TAB_imp_sim(TAB *a);
void TAB_imp_ident(TAB *a);

void TAB_libera(TAB *a);

TAB *TAB_busca(TAB *a, int elem);

int TAB_altura(TAB *a);

TLSEINT* misc(TAB *a, int elem);
TLSEINT* lista_cria();
void misc_aux(TLSEINT** l, TAB* a, int elem); // Mudança: ** para passar referência correta
TLSEINT* insere_lista(TLSEINT* l, int valor); // Mudança: tipo corrigido
void lista_exibe(TLSEINT* l);