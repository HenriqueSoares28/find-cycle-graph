#include "graph.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

void printPermutations(const std::vector<std::vector<int>>& permutations)
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
    std::ofstream outputFile("results.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }
    outputFile << "Number of Vertices,Number of Edges,Execution Time (ms),Number of Cycles\n";

    for (int n = 3; n <= 10; ++n)
    {
        Graph g(n);
        g.generateCompleteGraph();

        auto start = std::chrono::steady_clock::now();

        std::vector<std::vector<int>> permutations = g.generateAllPermutations();
        // printPermutations(permutations);

        int cycle = 0;
        for (const std::vector<int>& p : permutations)
        {
            if (g.isCycle(p))
            {
                cycle++;
            }
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        double execTime = diff.count();

        int numEdges = n * (n - 1) / 2;

        outputFile << n << "," << numEdges << "," << execTime << "," << cycle << "\n";
    }

    outputFile.close();
    std::cout << "Results saved to 'results.csv'." << std::endl;

    return 0;
}
