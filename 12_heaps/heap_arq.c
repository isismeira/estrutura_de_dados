#include <stdio.h>
#include <stdlib.h>

/* Revisão de arquivos
  1) Arquivo NÃO é vetor, mas você pode tratá-lo como se fosse
    v[3] - > seek até posição 3*sizeof(int) bytes
            ler um inteiro
  2) Cada inteiro ocupa 4 bytes (geralmente)
    sizeof(int) -> é quase sempre 4
    Então, se o arquivo tem 10 inteiros -> tem 10 * 4 bytes
  3) Como posicionar o cursor no arquivo 
     O equivalente acessar v[i] em um vetor -> fseek(fp, i * sizeof(int), SEEK_SET);
  4) Ler um inteiro e colocar em x 
      fread(&x, sizeof(int), 1, fp);
  5) Escrever inteiro na posição atual do arquivo
      fwrite(&x, sizeof(int), 1, fp);
  6) Tamanho total do arquivo — ftell
      fseek(fp, 0, SEEK_END);
      tam = ftell(fp);
  7) indices de pai e filhos:
      offset:  0   4   8   12  16  20  24 ...
      valor : [A] [B] [C] [D] [E] [F] [G]
*/

int esq (int ind){ 
  return 2 * ind + sizeof(int);
}

int dir (int ind){ 
  return 2 * (ind + sizeof(int));
}

int pai(int ind){
  if(ind) return (((ind - sizeof(int))/sizeof(int))/2) * sizeof(int);
  return -1;
}


void max_heapfy(char *narq, int tamarq, int ind){ // vetor vira o nome do arquivo, n vira o tamanho do arquivo
  int e = esq(ind), d = dir(ind), maior = ind, aux, maior_elem; // ... + int aux e int maior elemento

  FILE *fp = fopen(narq, "rb+"); // abrir um arquivo binário para leitura e gravação
  if(!fp) exit(1); // senão existe, exit
  fseek(fp, maior, SEEK_SET); // leio o pai
  fread(&maior_elem, sizeof(int), 1, fp); // gravo o valor do pai em maior_elem

  if(e < tamarq){ // se o indice do filho esquerdo não ultrapassa o tamanho do arquivo
    fseek(fp, e, SEEK_SET); // leio ele
    fread(&aux, sizeof(int), 1, fp); //guardo ele em aux
    if(aux > maior_elem){ // se ele for maior dp que o pai
      maior = e; // atualiza o indice do maior
      maior_elem = aux; // atualiza o valor do maior
    }    
  } 

  if(d < tamarq){ // se o indice do filho direito não ultrapassa o tamanho do arquivo
    fseek(fp, d, SEEK_SET); // leio ele
    fread(&aux, sizeof(int), 1, fp); // guardo ele em aux
    if(aux > maior_elem){ // se ele for maior do que o maior_elem
      maior = d; // atualiza o indice do maior 
      maior_elem = aux; // atualizao valor do maior
    }    
  } 

  if(maior != ind){ // se o maior não pai
    int intermediario; // cria variavel para guardar o valor do pai
    fseek(fp, ind, SEEK_SET); // acessa posição do pai
    fread(&intermediario, sizeof(int), 1, fp); // guardo o valor do pai
    fseek(fp, maior, SEEK_SET); // busco a posição do filho maior
    printf("($%d) %d x ($%d) %d\n", ind, intermediario, maior, maior_elem);    
    fwrite(&intermediario, sizeof(int), 1, fp); //escreve o valor do pai no lugar do filho maior
    fseek(fp, ind, SEEK_SET); // volto a acessar a posição do pape
    fwrite(&maior_elem, sizeof(int), 1, fp); // escrevo o valor do filho no lugar do pai
    fclose(fp); // fecho o arquivo
    if((tamarq - maior) > 4) max_heapfy(narq, tamarq, maior); // se ainda há espaço para existir filhos
  }
  else 
    fclose(fp);
}


void build_maxheap(char *narq){
  int tam; // variável para guardar o tamanho do arquivo em bytes
  FILE *fp = fopen(narq, "rb"); //abre o arquivo binário
  if(!fp) exit(1); // se não existe o arquivo, exit
  fseek(fp, 0L, SEEK_END); // move o cursor para o final do aruqivo
  tam = ftell(fp); // retorna o tomanho do arquivo
  fclose(fp); // fecha o arquivo
  int i, ultimo_pai = pai(tam - sizeof(int)); // guarda o indice do último pai
  for(i = ultimo_pai; i >= 0; i = i - sizeof(int)){ // decrementando i
    printf("$%d:\n", i); 
    max_heapfy(narq, tam, i); // chamo heapfy
    printf("\n");
  }
}


void heapsort(char *narq){
  build_maxheap(narq); // transformo o arquivo em max_heap

  // guardo o tamanho total do arquivo
  int tam; 
  FILE *fp = fopen(narq, "rb");
  if(!fp) exit(1);
  fseek(fp, 0L, SEEK_END);
  tam = ftell(fp);
  // 
  int i, j = tam, aux;
  fclose(fp);

  printf("Depois de build_maxheap, trocando sempre o ultimo elemento pelo primeiro\n");
  for(i = tam - sizeof(int); i >= 0; i = i - sizeof(int)){ // inicializa no offset do último elemento do arquivo e decrementa para o índice de cada elemento
    int ult, prim; // armazena valores dos últimos e primeiro elementos
    fp = fopen(narq, "rb+"); // abre arquivo em modo leitura/escrita binária
    if(!fp) exit(1);
    fseek(fp, i, SEEK_SET); // acessa a posição do último elemento
    fread(&ult, sizeof(int), 1, fp); // guarda o valor do último elemento
    fseek(fp, 0L, SEEK_SET); // volta para a primeira posição
    fread(&prim, sizeof(int), 1, fp); // guarda o calor da primeira posição

    fseek(fp, 0L, SEEK_SET); //volta ao início para escrever
    fwrite(&ult, sizeof(int), 1, fp); // guardo o valor do último no primeiro elemento
    fseek(fp, i, SEEK_SET); // volto ao final para escrever
    fwrite(&prim, sizeof(int), 1, fp); // guardo o valor do primeiro no 

    fclose(fp);
    j -= sizeof(int); // decremento j 
    max_heapfy(narq, j, 0); // chamo max_heapfy na raiz
  }
}

int main(void){
  char nome_arq[31];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nome_arq);
  int nvet, i = 0, aux;
  printf("Digite o numero de elementos distintos do arquivo: ");
  scanf("%d", &nvet);
  int vet[nvet];
  while (i < nvet){
    scanf("%d", &aux);
    if(aux >= 0){
      //int j;
      //for(j = 0; j < i; j++) if (vet[j] == aux) break;
      //if (j == i) vet[i++] = aux;
      vet[i++] = aux;
    }
  }

  FILE *fp = fopen(nome_arq, "wb");
  if(!fp) exit(1);
  fwrite(&vet, sizeof(int), nvet, fp);
  fclose(fp);

  heapsort(nome_arq);
  int resp[nvet];
  fp = fopen(nome_arq, "rb");
  if(!fp) exit(1);
  fread(&resp, sizeof(int), nvet, fp);
  fclose(fp);

  printf("\nVerificacao da ordenacao...\n");
  for(i = 0; i < nvet; i++) printf("[%d]:\t%d\t%d\n", i, vet[i], resp[i]);

  return 0;
}

