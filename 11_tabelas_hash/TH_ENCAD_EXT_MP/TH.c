#include <float.h>
#include "TH.h"

int TH_hash(int mat, int n){
  return mat % n; // calcula o índice na tabla hash
}

void TH_inicializa(TH tab, int n){
  int i;
  for(i = 0; i < n; i++)tab[i] = NULL; // inicializa todos os elementos da tabela com o mesmo NULL
}

TA* TH_busca(TH tab, int n, int mat){
  int h = TH_hash(mat, n); // calcula o índice hash
  TA *p = tab[h]; // pega a lista encadeada no índice h
  while((p) && (p->mat < mat)) p = p->prox; // percore a lista encadeada
  if((p) && (p->mat == mat)) return p; // se a chave (matricula) for a mesma que procuramos, retorna o ponteiro
  return NULL; // não encontrou, retorna NULL
}

TA* TH_aloca(int mat, float cr){
  TA *novo = (TA*) malloc (sizeof (TA)); // aloca memória para um novo elemento
  novo->mat = mat; // atribui a chave a ele (a matricula)
  novo->cr = cr; // atribui o cr a ela
  novo->prox = NULL; // não aponta para ninguem 
  return novo; // retorna novo nó
}

void TH_insere(TH tab, int n, int mat, float cr){
  int h = TH_hash(mat, n); // calcula o indice do novo elemento na hash
  TA *p = tab[h]; // cria um ponteiro apontando para o primeiro elemento...
  TA *ant = NULL; // ... e um ponteiro que vai sempre apontar para o elemento antes de p
  while((p) && (p->mat < mat)){ // percorre a lista mantendo ordenado
    ant = p;
    p = p->prox;
  }
  if((p) && (p->mat == mat)){ // se a matricula já existe, atualiza o CR
    p->cr = cr;
    return;
  }
  TA *novo = TH_aloca(mat, cr); // aloca o novo elemento
  novo->prox = p; // o elemento que vem depois do novo nó é p
  if(!ant)tab[h] = novo; // se ant é NULL, estamos inserindo no inicio da lista. ("tab[h] = novo" faz com que o novo elemento se torne o primeiro da lista)
  else ant->prox = novo; // caso contrario, ant vai apontar para o novo nó
}

void TH_libera(TH tab, int n){
  int i;
  for(i = 0; i < n; i++) // percorre todos os índices da hash 
    if(tab[i]){ // para cada indice da tabela percorre todos elementos da lista encadeada
      TA *p = tab[i], *q;
      while(p){
        q = p;
        p = p->prox;
        free(q); // libera um a um
      }
    }
}

float TH_retira(TH tab, int n, int mat){
  int h = TH_hash(mat, n);
  if(!tab[h]) return FLT_MIN; // se posição vazia, retorna erro
  TA *p = tab[h],*ant = NULL;
  float cr = FLT_MIN; // inicializa cr com FLT_MIN (assumindo erro) 
  while((p) && (p->mat < mat)){ // percorre a lista encadeada
    ant = p;
    p = p->prox;
  }
  if((!p) || (p->mat != mat)) return cr; // se não encontrou, retorna FLT_MIN
  // se não encontrou ajusta os nós
  if(!ant) tab[h] = p->prox; // se o elemento que queremos remover é o primeiro, tab[h] = p->prox
  else ant->prox = p->prox;  // caso contrário... ant->prox aponta para p->prox
  cr = p->cr; // guarda o cr registrado
  free(p); // libera
  return cr;
}

void TH_imprime(TH tab, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%d: ", i);
    if(tab[i]){
      TA *p = tab[i];
      printf("\n");
      while(p){
        printf("\t%d\t%f\t%p\n", p->mat, p->cr, p->prox);
        p = p->prox;
      }
    }
    else printf("NULL\n");
  }
}
