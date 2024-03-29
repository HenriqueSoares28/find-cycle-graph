#include "graph.h"

int main()
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    

    // gerar subgrafos
    std::vector<Graph> subgraphs = g.generatePermutationSubgraphs();
    int i=0;
    for (Graph g : subgraphs)
    {
        g.printGraph();
        std::cout << std::endl;
        i++;
    }
    std::cout << i << std::endl;

 
}
