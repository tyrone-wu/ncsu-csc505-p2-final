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
#include <iostream>
#include <omp.h>
#include "../include/GraphComponents.h"

// This just grabs the node opposite of vertex v through Edge e in Graph g
unsigned int getOpposite(unsigned int vIdx, Edge& e, Graph& graph) {
    unsigned int dIdx = graph.vertices[e.destination]->id;
    if (vIdx == dIdx)
        return graph.vertices[e.source]->id;
    return dIdx;
}

void parallelBFS(Graph& graph, unsigned int src, std::vector<int>& levels, unsigned int threads) {
    // Initialize current level
    levels[src] = 0;
    int currentLevel = 0;

    // Set of vertices at the current level
    std::vector<unsigned int> frontier;
    frontier.push_back(src);

    // Process current frontier
    while (!frontier.empty()) {

        // Set of vertices at next level
        std::vector<unsigned int> nextFrontiers[threads];

        // Traverse frontier together
        #pragma omp parallel for num_threads(threads)
        for (int i = 0; i < frontier.size(); i++) {

            // Iterate neighbors of vertex
            for (Edge* e : graph.vertices[frontier[i]]->incidentEdges) {

                // Check if vertex has been visited before
                unsigned int vOpp = getOpposite(frontier[i], *e, graph);
                if (levels[vOpp] == -1) {

                    // Ensures that only one threads obtains the -1 value at that level
                    int insert;
                    #pragma omp atomic capture
                    {
                        // Add unexplored neighbors to new frontier
                        insert = levels[vOpp];
                        levels[vOpp] = currentLevel + 1;
                    }

                    // The thread that got -1 will add the unexplored vertex to new frontier
                    if (insert == -1) {
                        int threadID = omp_get_thread_num();
                        nextFrontiers[threadID].push_back(vOpp);
                    }
                }
            }
        }

        // Compute new size of the frontier
        unsigned int fronterSize = 0;
        for (int i = 0; i < threads; i++) {
            fronterSize += nextFrontiers[i].size();
        }
        frontier.resize(fronterSize);

        // Move to next frontier
        int offset = 0;
        for (int i = 0; i < threads; i++) {
            for (int j = 0; j < nextFrontiers[i].size(); j++) {
                frontier[offset] = nextFrontiers[i][j];
                offset++;
            }
        }
        currentLevel++;
    }
}

// void parallelBFS(Graph& graph, unsigned int src, std::vector<int>& levels, unsigned int threads) {
//     // Initialize current level
//     levels[src] = 0;
//     int currentLevel = 0;

//     // Set of vertices at the current level
//     std::vector<unsigned int> frontier;
//     frontier.push_back(src);

//     // Process frontier
//     while (!frontier.empty()) {

//         // Set of vertices at next level
//         std::vector<unsigned int> nextFrontier;

//         // Parallelize processing of frontier
//         // #pragma omp parallel
//         // {
//         //     // Get thread id
//         //     int threadID = omp_get_thread_num();
//         //     // Get total number of threads
//         //     int threadNum = omp_get_num_threads();

//         // Traverse frontier together
//         #pragma omp parallel for
//         for (int i = 0; i < frontier.size(); i++) {

//             // Each thead maintains their own local next frontier
//             std::vector<unsigned int> localNextFrontier;
//             localNextFrontier.reserve(graph.vertices[frontier[i]]->incidentEdges.size());

//             // Iterate neighbors of vertex
//             for (Edge* e : graph.vertices[frontier[i]]->incidentEdges) {

//                 // Check if vertex has been visited before
//                 unsigned int vOpp = getOpposite(frontier[i], *e, graph);
//                 if (levels[vOpp] == -1) {

//                     // Ensures that only one threads obtains the -1 value at that level
//                     int insert;
//                     #pragma omp atomic capture
//                     {
//                         // Add unexplored neighbors to new frontier
//                         insert = levels[vOpp];
//                         levels[vOpp] = currentLevel + 1;
//                     }

//                     // The thread that got -1 will add the unexplored vertex to new frontier
//                     if (insert == -1) {
//                         localNextFrontier.push_back(vOpp);
//                     }
//                 }
//             }

//             // Merge threads local next frontiers
//             #pragma omp critical
//             {
//                 nextFrontier.insert(nextFrontier.end(), localNextFrontier.begin(), localNextFrontier.end());
//             }
//         }
//         // }

//         // Move to next frontier
//         frontier = nextFrontier;
//         currentLevel++;
//     }
// }

/**
 * @brief Gets the connected components of the graph
 * 
 * @param graph the graph to compute the algorithm on
 * @return std::vector<Vertex*> the vertices to each connected component
 */
std::vector<Vertex*> getConnectedComponents(Graph& graph) {
    //This keeps track of the start vertex for each connected component
    std::vector<Vertex*> connectedComponentsList;
    // Initialize levels vector, which also acts as a visited vector
    std::vector<int> levels(graph.vertices.size(), -1);
    // Get max threads
    unsigned int maxThreads = omp_get_max_threads();

    // Iterate vertices of graph
    for (int i = 0; i < graph.vertices.size(); i++) {
        // Explore vertex if not visited
        if (levels[i] == -1) {
            // Traverse vertex until no more and add to components list
            parallelBFS(graph, i, levels, maxThreads);
            connectedComponentsList.push_back(graph.vertices[i]);
        }
    }

    return connectedComponentsList;
}
