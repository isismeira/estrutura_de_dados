#include "q005.h"

// gcc -o q005usa.exe q005usa.c q005.c -lm
// .\q005usa.exe

int main() {
    TG *g1 = TG_inicializa();
    
    // Insere nós no g1
    g1 = TG_ins_no(g1, 1);
    g1 = TG_ins_no(g1, 2);
    g1 = TG_ins_no(g1, 3);
    g1 = TG_ins_no(g1, 4);
    
    // Insere arestas entre os nós
    TG_ins_aresta(g1, 1, 2);
    TG_ins_aresta(g1, 1, 3);
    TG_ins_aresta(g1, 2, 3);
    TG_ins_aresta(g1, 2, 4);
    TG_ins_aresta(g1, 3, 4);

    TG *g2 = TG_inicializa();
    
    // Insere nós no g2
    g2 = TG_ins_no(g2, 1);
    g2 = TG_ins_no(g2, 2);
    g2 = TG_ins_no(g2, 3);
    g2 = TG_ins_no(g2, 4);
    
    // Insere arestas entre os nós
    TG_ins_aresta(g2, 1, 2);
    TG_ins_aresta(g2, 1, 3);
    TG_ins_aresta(g2, 2, 3);
    TG_ins_aresta(g2, 2, 4);
    
    printf("São iguais?: %i", ig(g1,g2));
    
    // Libera a memória alocada
    TG_libera(g1);
    TG_libera(g2);
    
    return 0;
}