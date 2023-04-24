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
unsigned int getOpposite(unsigned int vIdx, Edge& e, const Graph& graph) {
    unsigned int dIdx = graph.vertices[e.destination]->id;
    if (vIdx == dIdx)
        return graph.vertices[e.source]->id;
    return dIdx;
}

// Performs parallel BFS
void parallelBFS(const Graph& graph, const unsigned int src, std::vector<int>& levels, const unsigned int threads) {
    // Initialize current level
    levels[src] = 0;
    int currentLevel = 0;

    // Set of vertices at the current level
    std::vector<unsigned int> frontier;
    frontier.push_back(src);
    // Set of vertices at next level
    std::vector<unsigned int> nextFrontiers[threads];

    // Process current frontier
    #pragma omp parallel num_threads(threads)
    while (!frontier.empty()) {

        // Traverse frontier together
        for (int i = omp_get_thread_num(); i < frontier.size(); i += omp_get_num_threads()) {

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

        // Wait for all threads to reach this point
        #pragma omp barrier

        // Ensures that only one thread sets to next frontier
        #pragma omp single
        {
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
                nextFrontiers[i].clear();
            }
            currentLevel++;
        }

        // Wait for all threads to reach this point
        #pragma omp barrier
    }
}

// void parallelBFS(Graph& graph, unsigned int src, std::vector<int>& levels, unsigned int threads) {
//     // Initialize current level
//     levels[src] = 0;
//     int currentLevel = 0;

//     // Set of vertices at the current level
//     std::vector<unsigned int> frontier;
//     frontier.push_back(src);
//     // Set of vertices at next level
//     std::vector<unsigned int> nextFrontier;

//     // Process frontier
//     #pragma omp parallel num_threads(threads)
//     while (!frontier.empty()) {

//         // Traverse frontier together
//         for (int i = omp_get_thread_num(); i < frontier.size(); i += omp_get_num_threads()) {

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

//         // Wait for all threads to reach this point
//         #pragma omp barrier

//         // Ensures that only one thread sets to next frontier
//         #pragma omp single
//         {
//             frontier = nextFrontier;
//             nextFrontier.clear();
//             currentLevel++;
//         }

//         // Wait for all threads to reach this point
//         #pragma omp barrier
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
            parallelBFS(graph, i, levels, 1);
            connectedComponentsList.push_back(graph.vertices[i]);
        }
    }

    return connectedComponentsList;
}
