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
    std::vector<Graph> generatePermutationSubgraphs()
    {
        std::vector<Graph> subgraphs;
        std::vector<std::vector<int>> allPermutations = generateAllPermutations();
        for (std::vector<int> permutation : allPermutations)
        {
            Graph subgraph(numVertices);
            bool hasEdge = true;
            int i = 0;
            while (hasEdge && i < permutation.size() - 1)
            {
                hasEdge = false;
                if (isEdge(permutation[i], permutation[i + 1]))
                {
                    subgraph.addEdge(permutation[i], permutation[i + 1]);
                    hasEdge = true;
                } 
                i++;
            }
            if (hasEdge)
            {
                subgraphs.push_back(subgraph);
            }
        }
        return subgraphs; 
    }

    /**
     * @brief Overloaded equality operator for comparing two Graph objects.
     *
     * @param other The Graph object to compare with.
     * @return true if the two Graph objects are equal, false otherwise.
     */
    bool operator==(const Graph &other) const
    {
        if (numVertices != other.numVertices)
            return false;

        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                if (adjacencyMatrix[i][j] != other.adjacencyMatrix[i][j])
                    return false;

        return true;
    }

    /**
     * @brief Represents a graph data structure.
     */
    Graph remapSubgraph()
    {
        int numVertices = 0;
        for (int i = 0; i < adjacencyMatrix.size(); i++) // find valid vertex count
        {
            if (adjacencyMatrix[i][i] != -1)
                numVertices++;
        }

        Graph newGraph(numVertices);

        int newRow = 0, newCol = 0;
        for (int i = 0; i < adjacencyMatrix.size(); i++) // copy valid vertices to new graph
        {
            if (adjacencyMatrix[i][i] != -1)
            {
                for (int j = 0; j < adjacencyMatrix.size(); j++)
                {
                    if (adjacencyMatrix[j][j] != -1)
                    {
                        newGraph.adjacencyMatrix[newRow][newCol] = adjacencyMatrix[i][j];
                        newCol++;
                    }
                }
                newRow++;
                newCol = 0;
            }
        }
        return newGraph;
    }


    // Gera permutações de um dado subconjunto
    void generatePermutations(std::vector<int> &subset, std::vector<std::vector<int>> &permutations)
    {
        std::sort(subset.begin(), subset.end());
        do
        {
            permutations.push_back(subset);
        } while (std::next_permutation(subset.begin(), subset.end()));
    }

    
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
