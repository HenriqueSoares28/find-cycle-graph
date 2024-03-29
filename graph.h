#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <stack>

/**
 * @class Graph
 * @brief Represents an undirected graph data structure.
 *
 * The Graph class provides methods to manipulate and operate on an undirected graph.
 */
class Graph
{
private:
    int numVertices;                               /**< The number of vertices in the graph. */
    std::vector<std::vector<int>> adjacencyMatrix; /**< The adjacency matrix representing the graph. */

public:
    /**
     * @brief Constructs a Graph object with the specified number of vertices.
     * @param vertices The number of vertices in the graph.
     */
    Graph(int vertices)
    {
        numVertices = vertices;
        adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
    }

    /**
     * @brief Adds an edge between two vertices in the graph.
     * @param src The source vertex.
     * @param dest The destination vertex.
     */
    void addEdge(int src, int dest)
    {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices)
        {
            adjacencyMatrix[src][dest] = 1;
            adjacencyMatrix[dest][src] = 1; // Add the reverse edge for undirected graph
        }
    }

    /**
     * @brief Adds an edge between two vertices in the graph.
     * @param src The source vertex.
     * @param dest The destination vertex.
     * @param weight The weight of the edge.
     */
    void addEdge(int src, int dest, int weight)
    {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices)
        {
            adjacencyMatrix[src][dest] = weight;
            adjacencyMatrix[dest][src] = weight; // Add the reverse edge for undirected graph
        }
    }

    /**
     * @brief Removes an edge between two vertices in the graph.
     * @param src The source vertex.
     * @param dest The destination vertex.
     */
    void removeEdge(int src, int dest)
    {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices)
        {
            adjacencyMatrix[src][dest] = 0;
            adjacencyMatrix[dest][src] = 0; // Remove the reverse edge for undirected graph
        }
    }

    /**
     * @brief Checks if there is an edge between two vertices in the graph.
     * @param src The source vertex.
     * @param dest The destination vertex.
     * @return True if there is an edge between the source and destination vertices, false otherwise.
     */
    bool isEdge(int src, int dest)
    {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices)
        {
            return adjacencyMatrix[src][dest] == 1;
        }
        return false;
    }

    /**
     * Generates a complete graph by adding edges between all pairs of vertices.
     * The graph must already have the desired number of vertices.
     */
    void generateCompleteGraph() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                addEdge(i, j);
            }
        }
    }

    /**
     * @brief Prints the adjacency matrix representation of the graph.
     */
    void printGraph()
    {
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (adjacencyMatrix[i][j] == -1)
                {
                    std::cout << "X ";
                }
                else
                {
                    std::cout << adjacencyMatrix[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    /**
     * Generates permutation subgraphs.
     *
     * @return A vector of Graph objects representing the permutation subgraphs.
     */
    bool isCycle(std::vector<int> inst)
    {
        for (int i = 0; i < inst.size() - 1; i++)
        {
            if (!isEdge(inst[i], inst[i + 1]))
            {
                return false;
            }
        }
        return isEdge(inst[inst.size() - 1], inst[0]);
    }



    /**
     * Generates all permutations of a given subset of integers.
     * 
     * @param subset The subset of integers to generate permutations from.
     * @param permutations The vector to store the generated permutations.
     */
    void generatePermutations(std::vector<int> &subset, std::vector<std::vector<int>> &permutations)
    {
        std::sort(subset.begin(), subset.end());
        do
        {
            permutations.push_back(subset);
        } while (std::next_permutation(subset.begin(), subset.end()));
    }

    /**
     * @brief Generates all permutations of subsets of a given vector.
     * 
     * This function generates all permutations of subsets of a given vector.
     * It returns a vector of vectors, where each inner vector represents a permutation.
     * 
     * @return std::vector<std::vector<int>> - A vector of vectors representing all permutations of subsets.
     */
    std::vector<std::vector<int>> generateAllPermutations()
    {
        int n = numVertices;
        std::vector<std::vector<int>> allPermutations;

        // Vetor original de 0 a n-1
        std::vector<int> original(n);
        for (int i = 0; i < n; ++i)
        {
            original[i] = i;
        }

        // Gerar subconjuntos de tamanho k e suas permutações
        for (int k = 3; k <= n; ++k)
        {
            std::vector<bool> mask(n, false);
            std::fill(mask.begin(), mask.begin() + k, true);

            do
            {
                std::vector<int> subset;
                for (int i = 0; i < n; ++i)
                {
                    if (mask[i])
                    {
                        subset.push_back(original[i]);
                    }
                }

                // Gerar e adicionar as permutações do subset atual
                generatePermutations(subset, allPermutations);

            } while (std::prev_permutation(mask.begin(), mask.end()));
        }
        return allPermutations;
    }
};
