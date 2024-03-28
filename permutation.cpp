#include "graph.h"

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.printGraph();    
    g.generateSubgraphs();

    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


    //gerar subgrafos
    std::vector<Graph> subgraphs = g.generateSubgraphs();

    for (Graph graph : subgraphs) {
        graph.printGraph();
        std::cout << std::endl;
    }
}