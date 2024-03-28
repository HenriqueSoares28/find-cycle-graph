
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

/**
 * @class Graph
 * @brief Represents a graph data structure.
 *
 * The Graph class provides methods to manipulate and operate on a graph.
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
                if(adjacencyMatrix[i][j] == -1){
                    std::cout << "X ";
                } else {
                    std::cout << adjacencyMatrix[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    /**
     * @brief Generates all subgraphs of the graph.
     * @return A list of Graph objects representing all subgraphs.
     */
    std::vector<Graph> generateSubgraphs()
    {
        std::vector<Graph> subgraphs;

        // Iterate through all possible subsets of vertices
        for (int subset = (1 << 3) - 1; subset < (1 << numVertices); subset++)
        {
            int numSelectedVertices = 0;
            for (int i = 0; i < numVertices; i++)
            {
                if (subset & (1 << i))
                {
                    numSelectedVertices++;
                }
            }
            if (numSelectedVertices >= 3)
            {
                Graph subgraph(numVertices); // Create a new graph for each subset
                for (int i = 0; i < numVertices; i++)
                {
                    for (int j = 0; j < numVertices; j++)
                    {
                        if ((subset & (1 << i)) && (subset & (1 << j)))
                        {
                            if (isEdge(i, j))
                            {
                                // There's an edge between i and j, include it in the subgraph
                                subgraph.addEdge(i, j);
                            }
                            else
                            {
                                // No edge between i and j, set 0 in the adjacency matrix
                                subgraph.removeEdge(i, j);
                            }
                        }
                        else
                        {
                            // Vertex i or j is not in the subset, set -1 in the adjacency matrix
                            subgraph.addEdge(i, j, -1);
                        }
                    }
                }
                subgraphs.push_back(subgraph); // Add the generated subgraph to the list
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
};
