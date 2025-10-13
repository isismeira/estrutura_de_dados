#include "q012.h"

TG* TG_inicializa(){
  return NULL;
}

void TG_imprime(TG *g){
  while(g){
    printf("Vizinhos do No %d:\n", g->id_no);
    TVIZ *v = g->prim_viz;
    while(v){
      printf("%d ", v->id_viz);
      v = v->prox_viz;
    }
    printf("\n");
    g = g->prox_no;
  }
}

void TG_imp_rec(TG *g){
  if(g){
    printf("%d:\n", g->id_no);
    TVIZ *v = g->prim_viz;
    while(v){
      printf("%d ", v->id_viz);
      v = v->prox_viz;
    }
    TG_imp_rec(g->prox_no);
  }
}

void TG_libera_viz(TVIZ *v){
  while(v){
    TVIZ *temp = v;
    v = v->prox_viz;
    free(temp);
  }
}

void TG_libera_viz_rec(TVIZ *v){
  if(!v) return;
  TG_libera_viz_rec(v->prox_viz);
  free(v);
}

void TG_libera(TG *g){
  while(g){
    TG_libera_viz(g->prim_viz);
    TG *temp = g;
    g = g->prox_no;
    free(temp);
  }
}

void TG_libera_rec(TG *g){
  if(g){
    TG_libera_viz(g->prim_viz);
    TG_libera_rec(g ->prox_no);
    free(g);
  }
}

TG* TG_busca_no(TG* g, int x){
  if((!g) || (g->id_no == x)) return g;
  return(TG_busca_no(g->prox_no, x));
}

TVIZ* TG_busca_aresta(TG *g, int no1, int no2){
  TG *p1 = TG_busca_no(g,no1), *p2 = TG_busca_no(g,no2);
  if((!p1) || (!p2)) return NULL;
  TVIZ *resp = p1->prim_viz;
  while((resp) && (resp->id_viz != no2)) resp = resp->prox_viz;
  return resp;
}

TG* TG_ins_no(TG *g, int x){
  TG *p = TG_busca_no(g, x);
  if(!p){
    p = (TG*) malloc(sizeof(TG));
    p->id_no = x;
    p->prox_no = g;
    p->prim_viz = NULL;
    g = p;
  }
  return g;
}

void TG_ins_um_sentido(TG *g, int no1, int no2){
  TG *p = TG_busca_no(g, no1);
  TVIZ *nova = (TVIZ *) malloc(sizeof(TVIZ));
  nova->id_viz = no2;
  nova->prox_viz = p->prim_viz;
  p->prim_viz = nova;
}

void TG_ins_aresta(TG *g, int no1, int no2){
  TVIZ *v = TG_busca_aresta(g, no1, no2);
  if(v) return;
  TG_ins_um_sentido(g, no1, no2);
  TG_ins_um_sentido(g, no2, no1);
}

void TG_retira_um_sentido(TG *g, int no1, int no2){
  TG *p = TG_busca_no(g, no1);
  if(!p) return;
  TVIZ *ant = NULL, *atual = p->prim_viz;
  while((atual)&&(atual->id_viz != no2)){
    ant = atual;
    atual = atual->prox_viz;
  }
  if(!ant) p->prim_viz = atual->prox_viz;
  else ant->prox_viz = atual->prox_viz;
  free(atual);
}

void TG_retira_aresta(TG *g ,int no1, int no2){
  TVIZ* v = TG_busca_aresta(g,no1,no2);
  if(!v) return;
  TG_retira_um_sentido(g,no1,no2);
  TG_retira_um_sentido(g,no2,no1);
}

TG* TG_retira_no(TG *g, int no){
  TG *p = g, *ant = NULL;
  while((p)&& (p->id_no != no)){
    ant = p;
    p = p->prox_no;
  }
  if(!p) return g;
  while(p->prim_viz) TG_retira_aresta(g, no, p->prim_viz->id_viz);
  if(!ant) g = g->prox_no;
  else ant->prox_no = p->prox_no;
  free(p);
  return g;
}

// 14) Dado um grafo conectado, verifique se ele pode ser transformado em uma árvore binária. Se ele pode ser uma árvore binária, retorne um. Se não, retorne zero. DICA: use TLSE para resolver esta questão: int teste (TG *g); e

// 1) Cada nó do grafo não pode apontar para mais de dois nós
// 2) Cada nó só pode ser apontado por um nó (só pode ter um pai)

typedef struct TLSE{
  int pai, filho_1, filho_2;
  struct lseint *prox;
} TLSE;

TLSE* TLSE_inicializa(void){
  return NULL;
}

TLSE* TLSE_insere(TLSE *l, int pai, int filho_1, int filho_2){
  TLSE *novo = (TLSE *) malloc(sizeof(TLSE));
  novo->prox = l;
  novo->pai = pai;
  novo->filho_1 = filho_1;
  novo->filho_2 = filho_2;
  return novo;
}

TLSE* busca_por_filho_1(TLSE* l, int filho_1){
    TLSE* aux = l;
    for(aux; aux!=NULL; aux = aux->prox) {
        if (aux->filho_1 == filho_1)
            return filho_1           
    }
    return NULL;
}
TLSE* busca_por_filho_2(TLSE* l, int filho_2){
    TLSE* aux = l;
    for(aux; aux!=NULL; aux = aux->prox) {
        if (aux->filho_2 == filho_2)
            return filho_2           
    }
    return NULL;
}

int teste(TG *g) {
    TLSE* elementos_arvore = TLSE_inicializa();
    TG* aux = g;
    while(aux) {
        // 1) Cada nó do grafo não pode apontar para mais que dois nós
        int conta_vizinhos = 0;
        for (TVIZ* vizinho = aux->prim_viz; vizinho; vizinho = vizinho->prox_viz)
            conta_vizinhos++;
        if (conta_vizinhos >= 3)
            return 0    

        // 2) Cada nó só pode ser apontado por um nó (só pode ter um pai)
        for (TVIZ* vizinho = aux->prim_viz; vizinho; vizinho = vizinho->prox_viz)
            if ((busca_por_filho_1(elementos_arvore, vizinho->id_viz) != NULL) || (busca_por_filho_1(elementos_arvore, vizinho->id_viz) != NULL))
                return 0;   

        if (conta_vizinhos == 0)
            elementos_arvore = TLSE_insere(elementos_arvore, aux->id_no, NULL, NULL);
        else if (conta_vizinhos == 1)
            elementos_arvore = TLSE_insere(elementos_arvore, aux->id_no, aux->prim_viz->id_viz, NULL);
        else if(conta_vizinhos == 2)
            elementos_arvore = TLSE_insere(elementos_arvore, aux->id_no, aux->prim_viz->id_viz, aux->prim_viz->prox_viz->id_viz);
            
        aux = aux->prox_no;    
    }
    return 1;
}