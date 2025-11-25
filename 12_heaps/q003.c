#include <stdio.h>
#include <stdlib.h>

/*
    Heap TERNÁRIA DE MÍNIMO EM MEMÓRIA SECUNDÁRIA
    Adaptação direta da heap binária de máximo do arquivo heap_arq.c.
    Agora cada nó possui 3 filhos:
        filho 1 → 3*i + 1
        filho 2 → 3*i + 2
        filho 3 → 3*i + 3
    Todos os índices são offsets em bytes (i * sizeof(int)).
*/

/* índice (em bytes) do pai de um nó armazenado em “ind” */
int pai(int ind){
    if(ind) return (((ind - sizeof(int)) / sizeof(int)) / 3) * sizeof(int);
    return -1;
}

/* índice (em bytes) do filho k (k ∈ {1,2,3}) */
int filho_k(int ind, int k){
    return ( (ind / sizeof(int)) * 3 + k ) * sizeof(int);
}

/* min_heapfy no arquivo */
void min_heapfy(char *narq, int tamarq, int ind){
    int menor = ind;
    int elem_menor, aux;

    int f1 = filho_k(ind, 1);
    int f2 = filho_k(ind, 2);
    int f3 = filho_k(ind, 3);

    FILE *fp = fopen(narq, "rb+");
    if(!fp) exit(1);

    /* lê o pai */
    fseek(fp, ind, SEEK_SET);
    fread(&elem_menor, sizeof(int), 1, fp);

    /* filho 1 */
    if(f1 < tamarq){
        fseek(fp, f1, SEEK_SET);
        fread(&aux, sizeof(int), 1, fp);
        if(aux < elem_menor){
            menor = f1;
            elem_menor = aux;
        }
    }

    /* filho 2 */
    if(f2 < tamarq){
        fseek(fp, f2, SEEK_SET);
        fread(&aux, sizeof(int), 1, fp);
        if(aux < elem_menor){
            menor = f2;
            elem_menor = aux;
        }
    }

    /* filho 3 */
    if(f3 < tamarq){
        fseek(fp, f3, SEEK_SET);
        fread(&aux, sizeof(int), 1, fp);
        if(aux < elem_menor){
            menor = f3;
            elem_menor = aux;
        }
    }

    /* se houve troca */
    if(menor != ind){
        int intermediario;

        /* lê valor do pai */
        fseek(fp, ind, SEEK_SET);
        fread(&intermediario, sizeof(int), 1, fp);

        /* troca com o filho menor */
        fseek(fp, menor, SEEK_SET);
        fwrite(&intermediario, sizeof(int), 1, fp);

        fseek(fp, ind, SEEK_SET);
        fwrite(&elem_menor, sizeof(int), 1, fp);

        fclose(fp);

        /* se ainda pode ter filhos */
        if((tamarq - menor) > sizeof(int))
            min_heapfy(narq, tamarq, menor);
    }
    else fclose(fp);
}

/* constrói a min-heap completa */
void build_minheap(char *narq){
    int tam;
    FILE *fp = fopen(narq, "rb");
    if(!fp) exit(1);

    fseek(fp, 0L, SEEK_END);
    tam = ftell(fp);
    fclose(fp);

    int ultimo_pai = pai(tam - sizeof(int));

    for(int i = ultimo_pai; i >= 0; i -= sizeof(int)){
        min_heapfy(narq, tam, i);
    }
}

/* heapsort usando heap de mínimo */
void heapsort(char *narq){
    build_minheap(narq);

    int tam;
    FILE *fp = fopen(narq, "rb");
    if(!fp) exit(1);

    fseek(fp, 0L, SEEK_END);
    tam = ftell(fp);
    fclose(fp);

    int j = tam;

    for(int i = tam - sizeof(int); i >= 0; i -= sizeof(int)){
        int prim, ult;

        fp = fopen(narq, "rb+");
        if(!fp) exit(1);

        /* lê último elemento */
        fseek(fp, i, SEEK_SET);
        fread(&ult, sizeof(int), 1, fp);

        /* lê primeiro elemento */
        fseek(fp, 0L, SEEK_SET);
        fread(&prim, sizeof(int), 1, fp);

        /* troca primeiro ↔ último */
        fseek(fp, 0L, SEEK_SET);
        fwrite(&ult, sizeof(int), 1, fp);

        fseek(fp, i, SEEK_SET);
        fwrite(&prim, sizeof(int), 1, fp);

        fclose(fp);

        /* diminui a área válida da heap */
        j -= sizeof(int);
        min_heapfy(narq, j, 0);
    }
}

/* Programa de teste (mesmo estilo do arquivo original) */
int main(void){
    char nome_arq[31];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arq);

    int nvet, i = 0, aux;
    printf("Digite o número de elementos: ");
    scanf("%d", &nvet);

    int vet[nvet];

    while(i < nvet){
        scanf("%d", &aux);
        if(aux >= 0){
            vet[i++] = aux;
        }
    }

    /* escreve o vetor no arquivo */
    FILE *fp = fopen(nome_arq, "wb");
    if(!fp) exit(1);
    fwrite(vet, sizeof(int), nvet, fp);
    fclose(fp);

    /* ordena */
    heapsort(nome_arq);

    int resp[nvet];
    fp = fopen(nome_arq, "rb");
    fread(resp, sizeof(int), nvet, fp);
    fclose(fp);

    printf("\nVerificação da ordenação:\n");
    for(i = 0; i < nvet; i++)
        printf("[%d]: %d -> %d\n", i, vet[i], resp[i]);

    return 0;
}

