#include "graph.h"

#include <chrono>

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
    Graph g(8);
    g.generateCompleteGraph();

    auto start = std::chrono::high_resolution_clock::now();

    // gerar subgrafos
    std::vector<std::vector<int>> permutations = g.generateAllPermutations();
    // printPermutations(permutations);
    int cycle = 0;
    for (std::vector<int> p : permutations)
    {
        if (g.isCycle(p))
        {
            cycle++;
            std::cout << "Ciclo " << cycle << ": ";
            for (int i = 0; i < p.size(); i++)
            {
                std::cout << p[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Tempo de execucao: " << diff.count() << "s" << std::endl;
}
