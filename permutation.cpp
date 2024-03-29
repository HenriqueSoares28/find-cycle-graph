#include "graph.h"

void printPermutations(std::vector<std::vector<int>> permutations)
{
    for (int i = 0; i < permutations.size(); i++)
    {
        std::cout << "Permutation " << i + 1 << ": ";
        for (int j = 0; j < permutations[i].size(); j++)
        {
            std::cout << permutations[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);

    g.addEdge(3, 4);
    g.addEdge(4, 2);

    

    // gerar subgrafos
    std::vector<std::vector<int>> permutations = g.generateAllPermutations();
    //printPermutations(permutations);
    int cycle = 0;
    for (std::vector<int> p : permutations){
        if (g.isCycle(p)){
            std::cout << "Ciclo " << ++cycle << ": ";
            for (int i = 0; i < p.size(); i++)
            {
                std::cout << p[i] << " ";
            }
            std::cout << std::endl;
        }
    }


 
}


