#include <stdio.h>
#include <stdlib.h>

int esq(int ind){ // retorna o índice do filho esquerdo
  return (ind * 2 + 1);
}

int dir(int ind){ // retorna o índice do filho direito
  return (ind * 2 + 2);
}

int pai(int ind){ // retorna índice do pai
  if(ind > 0) return (ind - 1)/2;
  return -1;
}

// max_heapfy(): Corrigir um único “nó” do heap e garantir que ele e seus filhos obedeçam às regras de max-heap. Ela assume que as subárvores abaixo já são heaps, mas o nó atual pode estar errado.
/*
 1)Compara o pai com seus dois filhos.
 2)Descobre quem é o maior dos três.
 3)Se um filho for maior que o pai → troca pai e filho.
 4)Como a troca pode bagunçar a subárvore abaixo, ela continua corrigindo recursivamente
*/

void max_heapfy(int *vet, int n, int ind){
  int e = esq(ind), d = dir(ind), maior = ind; 
  if(e < n && vet[e] > vet[ind]) maior = e; // se o filho esquerdo é menor que n e maior do que o pai, ele pode ser o maior
  if(d < n && vet[d] > vet[maior]) maior = d; // se o filho direito é menor que n e maior que o maior atual, ele pode ser o maior
  if(maior != ind){  // se o maior não é o pai
    // troca o pai com o maior filho
    int temp = vet[ind];
    vet[ind] = vet[maior];
    vet[maior] = temp;
    // chama recursivamente chamando o maior como indice
    max_heapfy(vet, n, maior);
  }
}

// build_max_heap(): Transformar um vetor qualquer em um max-heap válido. Ela faz heapify de baixo para cima, começando no último pai até chegar na raiz.
void build_max_heap(int *v, int n){
  int i, ultimo_pai = pai(n - 1); // inicializa o ultimo indice pai
  for(i = ultimo_pai; i >= 0; i--) // decrementa i
    max_heapfy(v, n, i); // chama recursivamente heapfy para i
}


// heapsort(): Usar a heap para ordenar o vetor inteiro.
/*
 1) Primeiro chama build_max_heap e transforma o vetor em um max-heap.
 2) Troca o maior elemento (posição 0) com o último do vetor.
 3) Reduz o tamanho da heap (ignora o último elemento, agora fixado).
 4) Chama max_heapfy para consertar a nova raiz.
 5) Repete até o vetor ficar ordenado.
*/
/*
Heap inicial:
[10, 5, 3, 4, 1]

Passo 1 — troca maior com o fim:
[1, 5, 3, 4, 10]

Passo 2 — reduz a heap:
[1, 5, 3, 1,| 10]

Passo 3 - conserta a raiz:
[5, 4, 3, 1,| 10]

Passo 1 - troca o maior com o fim:
[1, 4, 3, 5,| 10]

Passo 2 — reduz a heap:
[1, 4, 3,| 5, 10]

Passo 3 - conserta a raiz:
[4, 1, 3,| 5, 10]

Passo 1 - troca o maior com o fim:
[3, 1, 4,| 5, 10]

Passo 2 - reduz a heap:
[3, 1,| 4, 5, 10]

Passo 3 - conserta a raiz:
[1, 3,| 4, 5, 10]
*/

void heapsort(int *v, int n){
  int i;
  build_max_heap(v, n); // primeiro transformo o vetor em um max_heap válido
  for(i = n - 1; i >= 1; i--){
    int temp = v[i];
    v[i] = v[0];
    v[0] = temp;
    max_heapfy(v, i, 0);
  }
}

int main(void){
  int *vet, n, i = 0;
  printf("Digite o tamanho do vetor de elementos a serem ordenados... ");
  scanf("%d",&n);
  if(n <= 0) return 0;
  vet = (int *) malloc(sizeof(int) * n);

  for(i = 0; i < n; i++) vet[i] = rand() % n;
 
  printf("Antes de ordenar com heapsort...\n");
  for(i = 0; i < n; i++) printf("%d ", vet[i]);
  printf("\n");

  heapsort(vet, n);

  printf("Depois de ordenar com heapsort...\n");
  for(i = 0; i < n; i++) printf("%d ", vet[i]);
  printf("\n");

  free(vet);
  return 0;
}
