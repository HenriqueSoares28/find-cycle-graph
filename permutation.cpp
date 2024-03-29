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
    Graph g(7);
    g.generateCompleteGraph();


    

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


