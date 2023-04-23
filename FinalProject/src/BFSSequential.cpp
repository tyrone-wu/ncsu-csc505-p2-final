/**
 * @file BFS.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * 
 * @brief Class for bringing in the connected components algorithm using BFS.
 * 
 */

#include <vector>
#include <queue>
#include "../include/GraphComponents.h"

// This just grabs the node opposite of vertex v through Edge e in Graph g
unsigned int getOpposite(unsigned int vIdx, Edge& e, Graph& graph) {
    unsigned int dIdx = graph.vertices[e.destination]->id;
    if (vIdx == dIdx)
        return graph.vertices[e.source]->id;
    return dIdx;
}

// Performs bfs traversal and marking the vertices as visited
void bfs(unsigned int start, Graph& graph, std::vector<bool>& visited) {
    // Setup start vertex
    std::queue<unsigned int> queue;
    visited[start] = true;
    queue.push(start);

    // Explore graph from start vertex
    while (!queue.empty()) {
        // Explore vertex
        unsigned int vIdx = queue.front();
        queue.pop();

        // Add unexplored neighnors to queue
        for (Edge* e : graph.vertices[vIdx]->incidentEdges) {
            unsigned int opIdx = getOpposite(vIdx, *e, graph);
            if (!visited[opIdx]) {
                visited[opIdx] = true;
                queue.push(opIdx);
            }
        }
    }
}

/**
 * @brief Gets the connected components of the graph
 * 
 * @param graph the graph to compute the algorithm on
 * @return std::vector<Vertex*> the vertices to each connected component
 */
std::vector<Vertex*> getConnectedComponents(Graph& graph) {
    //This keeps track of the start vertex for each connected component
    std::vector<Vertex*> connectedComponentsList;
    // Initialize visited vector
    std::vector<bool> visited(graph.vertices.size(), false);

    // Iterate vertices of graph
    for (int i = 0; i < graph.vertices.size(); i++) {
        // Explore vertex if not visited
        if (!visited[i]) {
            // Traverse vertex until no more and add to components list
            bfs(i, graph, visited);
            connectedComponentsList.push_back(graph.vertices[i]);
        }
    }

    return connectedComponentsList;
}
