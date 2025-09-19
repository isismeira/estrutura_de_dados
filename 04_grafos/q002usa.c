#include "q002.h"

// gcc -o q002usa.exe q002usa.c q002.c -lm
// .\q002usa.exe

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
    TG_ins_aresta(grafo, 2, 4);
    TG_ins_aresta(grafo, 3, 4);
    
    // Imprime o grafo
    printf("Grafo após inserções:\n");
    TG_imprime(grafo);
    
    printf("Numero de arestas: %i\n", na(grafo));
    
    // Libera a memória alocada
    TG_libera(grafo);
    
    return 0;
}