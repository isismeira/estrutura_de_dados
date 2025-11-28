#include <stdio.h>
#include <stdlib.h>

#define TAM_VET 101

typedef struct numeros {
    int valor;
    struct numeros *prox;
} TN;

typedef TN* TH[TAM_VET];

int TH_hash(int v, int n){
    return v % n;
}

void TH_inicializa(TH tab, int n){
    for(int i = 0; i < n; i++)
        tab[i] = NULL;
}

TN* TH_busca(TH tab, int n, int valor){
    int h = TH_hash(valor, n);
    TN *p = tab[h];

    while(p && p->valor < valor)
        p = p->prox;

    if(p && p->valor == valor)
        return p;

    return NULL;
}

TN* TH_aloca(int valor){
    TN *novo = malloc(sizeof(TN));
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

void TH_insere(TH tab, int n, int valor){
    int h = TH_hash(valor, n);

    TN *p = tab[h];
    TN *ant = NULL;

    while(p && p->valor < valor){
        ant = p;
        p = p->prox;
    }

    if(p && p->valor == valor)
        return; // já existe

    TN *novo = TH_aloca(valor);
    novo->prox = p;

    if(!ant)
        tab[h] = novo;
    else
        ant->prox = novo;
}

int TH_retira(TH tab, int n, int valor){
    int h = TH_hash(valor, n);

    TN *p = tab[h];
    TN *ant = NULL;

    while(p && p->valor < valor){
        ant = p;
        p = p->prox;
    }

    if(!p || p->valor != valor)
        return 0; // não existe

    if(!ant)
        tab[h] = p->prox;
    else
        ant->prox = p->prox;

    free(p);
    return 1;
}

void TH_imprime(TH tab, int n){
    for(int i = 0; i < n; i++){
        printf("%d: ", i);

        TN *p = tab[i];
        if(!p){
            printf("NULL\n");
            continue;
        }

        printf("\n");
        while(p){
            printf("\tValor: %d | prox=%p\n", p->valor, p->prox);
            p = p->prox;
        }
    }
}

void TH_libera(TH tab, int n){
    for(int i = 0; i < n; i++){
        TN *p = tab[i];
        while(p){
            TN *q = p;
            p = p->prox;
            free(q);
        }
    }
}


// ==================================================================================================================================================================================================================

// Interseção de conjuntos em MP
void inter(int* vetA, int nA, int* vetB, int nB){
    TH tabHash; // vetor estático de TAM_VET listas
    TH_inicializa(tabHash, TAM_VET);

    // insere A na tabela
    for(int i = 0; i < nA; i++)
        TH_insere(tabHash, TAM_VET, vetA[i]);

    // verifica B
    for(int i = 0; i < nB; i++)
        if(TH_busca(tabHash, TAM_VET, vetB[i]))
            printf("%d\n", vetB[i]);
}


// Diferença simétrica de conjuntos em MP
void dif_sim(int* vetA, int nA, int* vetB, int nB){
    TH tabHash;
    TH_inicializa(tabHash, TAM_VET);

    // insere A
    for(int i = 0; i < nA; i++)
        TH_insere(tabHash, TAM_VET, vetA[i]);

    // processa B
    for(int i = 0; i < nB; i++){
        if(TH_busca(tabHash, TAM_VET, vetB[i]))
            TH_retira(tabHash, TAM_VET, vetB[i]);
        else
            TH_insere(tabHash, TAM_VET, vetB[i]);
    }

    // imprime tudo que sobrou
    for(int i = 0; i < TAM_VET; i++){
        TN* p = tabHash[i];
        while(p){
            printf("%d\n", p->valor);
            p = p->prox;
        }
    }
}

// União de conjuntos
void uniao(int* vetA, int nA, int* vetB, int nB){
    TH tabHash;
    TH_inicializa(tabHash, TAM_VET);

    // insere A
    for(int i = 0; i < nA; i++){
        if(!TH_busca(tabHash, TAM_VET, vetA[i])){
            TH_insere(tabHash, TAM_VET, vetA[i]);
            printf("%d\n", vetA[i]);
        }
    }

    // insere B
    for(int i = 0; i < nB; i++){
        if(!TH_busca(tabHash, TAM_VET, vetB[i])){
            TH_insere(tabHash, TAM_VET, vetB[i]);
            printf("%d\n", vetB[i]);
        }
    }
}


// ==================================================================================================================================================================================================================

int main(){
    printf("INTER MP:\n");
    inter("A.txt",5,"B.txt",4);

    printf("\nDIF SIM MP:\n");
    dif_sim("A.txt",5,"B.txt",4);

    printf("\nUNIAO MP:\n");
    uniao("A.txt",5,"B.txt",4);

    return 0;
}
