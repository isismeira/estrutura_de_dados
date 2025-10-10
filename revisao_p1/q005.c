#include "q005.h" 

TAB *TAB_inicializa(void){
  return NULL;
}

TAB *TAB_cria(int raiz, TAB *esq, TAB *dir){
  TAB *novo = (TAB *) malloc(sizeof(TAB));
  novo->info = raiz;
  novo->esq = esq;
  novo->dir = dir;
  return novo;
}

TAB *TAB_busca(TAB *a, int elem){
  if((!a) || (a->info == elem)) return a;
  TAB *resp = TAB_busca(a->esq, elem);
  if(resp) return resp;
  return TAB_busca(a->dir, elem);
}

void TAB_imp_pre(TAB *a){
  if(a){
    printf("%d ", a->info);
    TAB_imp_pre(a->esq);
    TAB_imp_pre(a->dir);
  }
}

void TAB_imp_pos(TAB *a){
  if(a){
    TAB_imp_pos(a->esq);
    TAB_imp_pos(a->dir);
    printf("%d ", a->info);
  }
}

void TAB_imp_sim(TAB *a){
  if(a){
    TAB_imp_sim(a->esq);
    printf("%d ", a->info);
    TAB_imp_sim(a->dir);
  }
}

void imp_aux(TAB *a, int andar){
  int j;
  if(a){
    imp_aux(a->dir, andar + 1);
    for(j = 0; j <= andar; j++) printf("\t"); 
    printf("%d\n", a->info);
    imp_aux(a->esq, andar + 1);
  }
  else{
   for(j = 0; j <= andar; j++) printf("\t");
   printf("N\n");
  }
}

void TAB_imp_ident(TAB *a){
  imp_aux(a, 0);
}

void TAB_libera(TAB *a){
  if(a){
    TAB_libera(a->esq);
    TAB_libera(a->dir);
    free(a);
  }
}

int maior(int x, int y){
  if(x >= y) return x;
  return y;
}

int TAB_altura(TAB *a){
  if(!a) return -1;
  return maior(TAB_altura(a->esq), TAB_altura(a->dir)) + 1;
}

// 5) Retornar todas as informações ancestrais de um nó na árvore binária, da raiz da árvore até o elemento passado como parâmetro, usando a biblioteca de lista encadeada - TLSEINT* misc(TAB *a, int elem), onde:
/*
typedef struct lseint{
  int lim_inf, lim_sup;
  struct lseint *prox;
} TLSEINT;
*/

TLSEINT* misc(TAB *a, int elem) {
    TLSEINT* lista = lista_cria();
    misc_aux(&lista,a,elem);
    lista_exibe(lista);
    return lista;
}

TLSEINT* lista_cria(){
	return NULL;
}

TLSEINT* insere_lista(TLSEINT* l, int valor) { 
    TLSEINT* novo = (TLSEINT*)malloc(sizeof(TLSEINT));
    novo->lim_inf = valor;
    novo->prox = NULL;

    if (l == NULL) {
        return novo;
    }

    TLSEINT* p = l;
    while (p->prox != NULL) {
        p = p->prox;
    }

    p->prox = novo;
    return l;
}

void lista_exibe(TLSEINT* l) {
	puts("#### Lista encadeada #####");
	TLSEINT* p;						
	for (p = l; p != NULL; p = p->prox)		
		printf("info = %d\n", p->lim_inf);		
 }


void misc_aux(TLSEINT** l, TAB* a, int elem) {
    if (!a) return; // !!!
    *l = insere_lista(*l, a->info); //!!!
    if (a->info == elem) return; //!!!  
     if (TAB_busca(a->esq, elem)) {
        misc_aux(l, a->esq, elem);
    } else {
        misc_aux(l, a->dir, elem);
    }
}