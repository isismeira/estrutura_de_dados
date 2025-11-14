#include <stdio.h>
#include <stdlib.h>

typedef struct viz {
    int id_viz;
    int cor;
    struct viz *prox_viz;
} TVIZ;

typedef struct grafo {
    int id_no;
    int cor;
    TVIZ *prim_viz;
    struct grafo *prox_no;
} TG;

// ------------------- Funções básicas -------------------
TG* TG_inicializa() {
    return NULL;
}

TG* TG_busca_no(TG* g, int x) {
    if ((!g) || (g->id_no == x)) return g;
    return TG_busca_no(g->prox_no, x);
}

TVIZ* TG_busca_aresta(TG *g, int no1, int no2) {
    TG *p1 = TG_busca_no(g,no1), *p2 = TG_busca_no(g,no2);
    if ((!p1) || (!p2)) return NULL;
    TVIZ *resp = p1->prim_viz;
    while ((resp) && (resp->id_viz != no2)) resp = resp->prox_viz;
    return resp;
}

TG* TG_ins_no(TG *g, int x) {
    TG *p = TG_busca_no(g, x);
    if (!p) {
        p = (TG*) malloc(sizeof(TG));
        p->id_no = x;
        p->prox_no = g;
        p->prim_viz = NULL;
        p->cor = -1;
        g = p;
    }
    return g;
}

void TG_ins_um_sentido(TG *g, int no1, int no2) {
    TG *p = TG_busca_no(g, no1);
    TVIZ *nova = (TVIZ *) malloc(sizeof(TVIZ));
    nova->id_viz = no2;
    nova->prox_viz = p->prim_viz;
    nova->cor = -1;
    p->prim_viz = nova;
}

void TG_ins_aresta(TG *g, int no1, int no2) {
    TVIZ *v = TG_busca_aresta(g, no1, no2);
    if (v) return;
    TG_ins_um_sentido(g, no1, no2);
    TG_ins_um_sentido(g, no2, no1);
}

// ------------------- Funções que faltaram -------------------
int conta_nos(TG *g) {
    int n = 0;
    while (g) {
        n++;
        g = g->prox_no;
    }
    return n;
}

int indice_no(TG *g, int id) {
    int i = 0;
    while (g) {
        if (g->id_no == id) return i;
        g = g->prox_no;
        i++;
    }
    return -1;
}

void dfs_conect(TG *g, int id_atual, int *visitado) {
    int idx = indice_no(g, id_atual);
    visitado[idx] = 1;

    TG *no_atual = TG_busca_no(g, id_atual);
    for (TVIZ *v = no_atual->prim_viz; v; v = v->prox_viz) {
        int idx_viz = indice_no(g, v->id_viz);
        if (!visitado[idx_viz])
            dfs_conect(g, v->id_viz, visitado);
    }
}

// É conectado  
int eh_conectado(TG *g) {
    if (!g) return 0;

    int n = conta_nos(g);
    int *visitado = (int *)calloc(n, sizeof(int));

    dfs_conect(g, g->id_no, visitado);

    int conectado = 1;
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            conectado = 0;
            break;
        }
    }

    free(visitado);
    return conectado;
}

// Tem k arestas
int tem_k_arestas(TG* g, int k) {
    int contador = 0;
    TG *aux = g;
    while (aux) {
        TVIZ *v = aux->prim_viz;
        while (v) {
            contador++;
            v = v->prox_viz;
        }
        aux = aux->prox_no;
    }
    return (contador / 2 == k);
}
// ------------------- Códigos que eu fiz -------------------

int tem_menos_tres_cores(TG *g) {
    int cores[100] = {0};
    int num_cores = 0;
    TG *aux = g;
    while (aux) {
        int c = aux->cor;
        int novo = 1;
        for (int i = 0; i < num_cores; i++) {
            if (cores[i] == c) {
                novo = 0;
                break;
            }
        }
        if (novo) cores[num_cores++] = c;
        aux = aux->prox_no;
    }
    return num_cores >= 3;
}

int pode_ser_tripartido_por_cor(TG *g) {
    TG *aux = g;
    while (aux) {
        for (TVIZ *v = aux->prim_viz; v; v = v->prox_viz) {
            if (aux->cor == v->cor) {
                return 0; 
            }
        }
        aux = aux->prox_no;
    }
    return 1;
}

int tripartido_por_k_arestas(TG* g, int k) {
    if (!eh_conectado(g)) return 0;
    if (!tem_menos_tres_cores(g)) return 0;
    if (!tem_k_arestas(g, k)) return 0;
    if (!pode_ser_tripartido_por_cor(g)) return 0;
    return 1;
}

// --------------------------------------

int main() {
    TG *g = TG_inicializa();

    g = TG_ins_no(g, 1);
    g = TG_ins_no(g, 2);
    g = TG_ins_no(g, 3);
    g = TG_ins_no(g, 4);

    TG_ins_aresta(g, 1, 2);
    TG_ins_aresta(g, 2, 3);
    TG_ins_aresta(g, 3, 4);
    TG_ins_aresta(g, 4, 1);
    TG_ins_aresta(g, 1, 3);

    TG_busca_no(g,1)->cor = 0;
    TG_busca_no(g,2)->cor = 1;
    TG_busca_no(g,3)->cor = 2;
    TG_busca_no(g,4)->cor = 0;

    int k = 5; 

    if (tripartido_por_k_arestas(g, k))
        printf("O grafo EH tripartido por %d arestas.\n", k);
    else
        printf("O grafo NAO eh tripartido por %d arestas.\n", k);

    return 0;
}
