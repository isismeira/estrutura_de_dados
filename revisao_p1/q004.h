#include <stdio.h>
#include <stdlib.h>

typedef struct arvbin{
  int info;
  struct arvbin *esq, *dir;
}TAB;

TAB *TAB_inicializa(void);
TAB *TAB_cria(int raiz, TAB *esq, TAB *dir);

void TAB_imp_pre(TAB *a);
void TAB_imp_pos(TAB *a);
void TAB_imp_sim(TAB *a);
void TAB_imp_ident(TAB *a);

void TAB_libera(TAB *a);

TAB *TAB_busca(TAB *a, int elem);

int TAB_altura(TAB *a);

int quant_caminhos(TAB *a, int N);
int qtd_de_nos(TAB* a);
int preenche_nos(TAB* a, int* nos, int pos);

TAB* maior_nivel(TAB *a, int N, int M);
int soma_dois_nos(TAB* a, int N, int M);
void soma_raiz_n(TAB* melhor_ancestral, int N, int* contador);