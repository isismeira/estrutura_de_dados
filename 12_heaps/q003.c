#include <stdio.h>
#include <stdlib.h>

/*
    Refaça a (Q2) para heaps em arquivos binários.
*/

int pai(int ind){
    if(ind) return (((ind - sizeof(int)) / sizeof(int)) / 3) * sizeof(int);
    return -1;
}

int filho_k(int ind, int k){
    return ( (ind / sizeof(int)) * 3 + k ) * sizeof(int);
}


void min_heapfy(char* arq, int tamarq ,int ind) {
    int min = ind, filho_1 = filho_k(ind, 1), filho_2 = filho_k(ind, 2), filho_3 = filho_k(ind, 3);
    FILE *fp = fopen(arq, "rb+");

    int menor;
    fseek(fp, min, SEEK_SET);
    fread(&menor, sizeof(int), 1, fp);

    if (filho_1 < tamarq) { // !!!
        int valor_1;
        fseek(fp, filho_1, SEEK_SET);
        fread(&valor_1, sizeof(int), 1, fp);
        if (valor_1 < menor) min = filho_1;
    }
    
    if (filho_2 < tamarq) { // !!!
        int valor_2;
        fseek(fp, filho_2, SEEK_SET);
        fread(&valor_2, sizeof(int), 1, fp);
        if (valor_2 < menor) min = filho_2;
    }

    if (filho_3 < tamarq) { // !!!
        int valor_3;
        fseek(fp, filho_3, SEEK_SET);
        fread(&valor_3, sizeof(int), 1, fp);
        if (valor_3 < menor) min = filho_3;
    }

    if (min != indice) {
        int temp;
        fseek(fp, ind, SEEK_SET);
        fread(&temp, sizeof(int), 1, fp);
        fwrite(&menor, sizeof(int), 1, fp);

        fseek(fp, min, SEEK_SET);
        fwrite(&temp, sizeof(int), 1, fp);

        fclose(fp); // !!!
        // !!! se ainda pode ter filhos
        if ((tamarq - menor) > sizeof(int)) min_heapfy(arq, tamarq ,min);
    } else {
        fclose(fp);
    }
}

void build_min_heap(char* arq, int tamarq) {
    int ultimo_pai = pai(tamarq - sizeof(int));
    for (int i = ultimo_pai; i >= 0; i -= sizeof(int)) {
        min_heapfy(arq, tamarq, i);
    }
}

