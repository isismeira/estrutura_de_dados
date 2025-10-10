#include "q004.h" // Mudança: estava incluindo "q003.h", o correto é "q004.h"

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

// 4) Retorne a quantidade de caminhos que somam N em uma árvore binária simples
int quant_caminhos(TAB *a, int N) {
    int qtd_nos = qtd_de_nos(a);
    int* nos = malloc(qtd_nos * sizeof(int));

    preenche_nos(a, nos, 0); // Mudança: removido o argumento extra incorreto

    int caminhos_igual_n = 0;

    for (int i = 0; i < qtd_nos; i++) { // Mudança: i inicia em 0 (não 1)
        for (int j = i; j < qtd_nos; j++) { // Mudança: j inicia em i (não i-1)
            int soma = soma_dois_nos(a, nos[i], nos[j]);
            if (soma == N) {
                caminhos_igual_n++;
            }
        }
    }

    free(nos); // Mudança: liberar memória alocada
    return caminhos_igual_n;
}

int qtd_de_nos(TAB* a) {
    if (!a) return 0;
    return 1 + qtd_de_nos(a->esq) + qtd_de_nos(a->dir); // Mudança: simplificado, removido if redundante
}

int preenche_nos(TAB* a, int* nos, int pos) {
    if (!a) return pos;
    nos[pos++] = a->info;
    pos = preenche_nos(a->esq, nos, pos);
    pos = preenche_nos(a->dir, nos, pos);
    return pos;
}  

TAB* maior_nivel(TAB *a, int N, int M) {
    if (a == NULL) return NULL;

    if (a->info == N || a->info == M)
        return a;

    TAB *esq = maior_nivel(a->esq, N, M);
    TAB *dir = maior_nivel(a->dir, N, M);

    if (esq && dir)
        return a;

    return (esq != NULL) ? esq : dir;
}

int soma_dois_nos(TAB* a, int N, int M) {
    TAB* melhor_ancestral = maior_nivel(a, N, M);
    if (!melhor_ancestral) return 0; // Mudança: evita segmentation fault se ancestral não for encontrado

    int contador_n = 0;
    soma_raiz_n(melhor_ancestral, N, &contador_n); 
    int contador_m = 0;
    soma_raiz_n(melhor_ancestral, M, &contador_m); 
    return melhor_ancestral->info + contador_n + contador_m;
}

void soma_raiz_n(TAB* melhor_ancestral, int N, int* contador) {
    if (!melhor_ancestral) return; // Mudança: evita ponteiro nulo

    if (melhor_ancestral->info == N) {
        return;
    } else {
        if (melhor_ancestral->esq && TAB_busca(melhor_ancestral->esq, N)) { // Mudança: checa se existe subárvore esquerda
            (*contador) += melhor_ancestral->esq->info;
            soma_raiz_n(melhor_ancestral->esq, N, contador);
        } 
        else if (melhor_ancestral->dir && TAB_busca(melhor_ancestral->dir, N)) { // Mudança: checa se existe subárvore direita
            (*contador) += melhor_ancestral->dir->info;
            soma_raiz_n(melhor_ancestral->dir, N, contador);
        }
    }
}
