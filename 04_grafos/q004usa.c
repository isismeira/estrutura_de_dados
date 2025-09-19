#include "q004.h"

// gcc -o q004usa.exe q004usa.c q004.c -lm
// .\q004usa.exe

int main() {
    TG *grafo = TG_inicializa();
    
    // Insere nós no grafo
    grafo = TG_ins_no(grafo, 1);
    grafo = TG_ins_no(grafo, 2);
    grafo = TG_ins_no(grafo, 3);
    grafo = TG_ins_no(grafo, 4);
    
    // Insere arestas entre os nós
    TG_ins_aresta(grafo, 1, 2);
    TG_ins_aresta(grafo, 1, 3);
    TG_ins_aresta(grafo, 2, 3);
    TG_ins_aresta(grafo, 2, 4);
    TG_ins_aresta(grafo, 3, 4);
    
    // Imprime o grafo
    printf("Grafo após inserções:\n");
    TG_imprime(grafo);
    
    printf("Todos os nós tem grau 3?: %i", testek(grafo, 3));
    
    // Libera a memória alocada
    TG_libera(grafo);
    
    return 0;
}