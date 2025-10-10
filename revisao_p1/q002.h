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

int* media(TAB* a, int* tam_vet);
void percorre_arvore(TAB* a,int* vetor_elementos_por_nivel,int* vetor_soma_por_nivel, int nivel);