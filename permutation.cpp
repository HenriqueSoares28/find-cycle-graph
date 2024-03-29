#include "graph.h"

int main()
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 2);
    g.addEdge(4, 2);

    // gerar subgrafos
    std::vector<Graph> subgraphs = g.generatePermutationSubgraphs();

    // verifica se existe ciclo
    int cycleCount = 0;
    for (Graph graph : subgraphs)
    {
        if (graph.remapSubgraph().isCycle()) // faz o remap de cada  subgraph e verifica se é um ciclo
        {
            graph.printGraph();
            cycleCount++;
            std::cout << std::endl;
        }
    }
    std::cout << cycleCount << std::endl;
}
