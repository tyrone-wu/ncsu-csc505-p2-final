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
#include <omp.h>
#include "../include/GraphComponents.h"

// Performs parallel BFS
void parallelBFS(const std::vector<Vertex*>& vertices, const unsigned int src, std::vector<int>& levels, const unsigned int threads) {
    // Initialize current level
    levels[src] = 0;
    int currentLevel = 0;

    // Set of vertices at the current level
    std::vector<unsigned int> frontier;
    frontier.push_back(src);
    // Track next offset to pick up from
    unsigned int offset = 0;

    // Process current frontier
    #pragma omp parallel num_threads(threads)
    while (!frontier.empty()) {

        // Each thread maintains their own local next frontier
        std::vector<unsigned int> localNextFrontier;
        localNextFrontier.reserve(frontier.size());

        // Divide frontier exploration among threads
        // #pragma clang loop unroll(full)
        #pragma omp for schedule(dynamic)
        for (int i = 0; i < frontier.size(); i++) {

            // Index of the vertex frontier
            unsigned int frontierVertex = frontier[i];
            // Get incident edges of frontier vertex
            std::vector<unsigned int> incidentEdges = vertices[frontierVertex]->incidentEdges;

            // Iterate neighbors of vertex
            // #pragma clang loop unroll(disable)
            for (unsigned int toIdx : incidentEdges) {
                // Check if vertex has been visited before
                if (levels[toIdx] == -1) {

                    // Ensures that only one threads obtains the -1 value at that level
                    int insert;
                    #pragma omp atomic capture
                    {
                        // Add unexplored neighbors to new frontier
                        insert = levels[toIdx];
                        levels[toIdx] = currentLevel + 1;
                    }

                    // The thread that got -1 will add the unexplored vertex to new frontier
                    if (insert == -1) {
                        localNextFrontier.push_back(toIdx);
                    }
                }
            }
        }

        // Get index offset of where to writing
        unsigned int localOffset;
        #pragma omp atomic capture
        {
            localOffset = offset;
            offset += localNextFrontier.size();
        }

        // Wait for all threads to reach this point
        #pragma omp barrier

        // Only single thread update global variables
        #pragma omp single
        {
            frontier.resize(offset);
            offset = 0;
            currentLevel++;
        }

        // Wait for all threads to reach this point
        #pragma omp barrier

        // Each thread write their own local next frontier
        // #pragma clang loop unroll(disable)
        for (int i = 0; i < localNextFrontier.size(); i++) {
            frontier[i + localOffset] = localNextFrontier[i];
        }

        // Wait for all threads to reach this point
        #pragma omp barrier
    }
}

/**
 * @brief Gets the connected components of the graph
 * 
 * @param graph the graph to compute the algorithm on
 * @param threads number of threads to utilize
 * @return std::vector<Vertex*> the vertices to each connected component
 */
std::vector<Vertex*> getConnectedComponents(Graph& graph, const unsigned int threads) {
    //This keeps track of the start vertex for each connected component
    std::vector<Vertex*> connectedComponentsList;
    // Initialize levels vector, which also acts as a visited vector
    std::vector<int> levels(graph.vertices.size(), -1);

    // Iterate vertices of graph
    for (int i = 0; i < graph.vertices.size(); i++) {
        // Explore vertex if not visited
        if (levels[i] == -1) {
            // Traverse vertex until no more and add to components list
            parallelBFS(graph.vertices, i, levels, threads);
            connectedComponentsList.push_back(graph.vertices[i]);
        }
    }

    return connectedComponentsList;
}
