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

        // Gerar todas as combinações de 3 até numVertices
        std::vector<int> vertexIndices(numVertices);              // Vetor de índices de vértices [0, 1, 2, ..., numVertices-1]
        std::iota(vertexIndices.begin(), vertexIndices.end(), 0); // Preenche o vetor com valores consecutivos

        // Para cada tamanho possível de subgrafo, de 3 a numVertices
        for (int size = 3; size <= numVertices; ++size)
        {
            std::vector<bool> combSelector(numVertices, false);
            std::fill(combSelector.begin(), combSelector.begin() + size, true);

            // Gerar todas as combinações de vértices de tamanho 'size'
            do
            {
                // Criar um novo grafo para a combinação atual
                Graph subgraph(numVertices);

                // Inicializar a matriz de adjacência do subgrafo com -1
                for (auto &row : subgraph.adjacencyMatrix)
                {
                    std::fill(row.begin(), row.end(), -1);
                }

                // Para cada vértice, verificar se ele está incluído na combinação atual
                for (int i = 0; i < numVertices; ++i)
                {
                    if (combSelector[i])
                    {
                        for (int j = 0; j < numVertices; ++j)
                        {
                            if (combSelector[j])
                            {
                                // Se ambos os vértices estão incluídos, copiar o valor da aresta original
                                subgraph.adjacencyMatrix[i][j] = (adjacencyMatrix[i][j] != 0) ? 1 : 0;
                            }
                        }
                    }
                }

                subgraphs.push_back(subgraph);
            } while (std::prev_permutation(combSelector.begin(), combSelector.end()));
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

    /**
     * Checks if the graph contains a cycle.
     * 
     * @return true if the graph contains a cycle, false otherwise.
     */
    bool isCycle()
    {
        std::vector<int> visited(numVertices, 0);
        std::stack<int> stack;
        stack.push(0);
        visited[0] = 1;
        while (!stack.empty())
        {
            int current = stack.top();
            stack.pop();
            for (int i = 0; i < numVertices; i++)
            {
                if (adjacencyMatrix[current][i] == 1)
                {
                    if (visited[i] == 1)
                    {
                        bool allTrue = std::all_of(visited.begin(), visited.end(), [](bool b) { return b; });
                        if(allTrue){
                            return true;
                        }
                    }
                    else if (visited[i] == 0)
                    {
                        visited[i] = 1;
                        stack.push(i);
                    }
                }
            }
            visited[current] = 2;
        }
        return false;
    }
};
