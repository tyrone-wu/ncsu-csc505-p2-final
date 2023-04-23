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

// // This just grabs the node opposite of vertex v through Edge e in Graph g
// Vertex* getOpposite(Vertex& v, Edge& e, Graph& graph) {
//     Vertex* r = graph.vertices[e.destination];
//     if (r->id == v.id)
//         return graph.vertices[e.source];
//     return r;
// }

// This just grabs the node opposite of vertex v through Edge e in Graph g
unsigned int getOpposite(unsigned int vIdx, Edge& e, Graph& graph) {
    unsigned int dIdx = graph.vertices[e.destination]->id;
    if (vIdx == dIdx)
        return graph.vertices[e.source]->id;
    return dIdx;
}

void parallelBFS(Graph& graph, unsigned int src, std::vector<int>& levels) {
    // Initialize current level
    levels[src] = 0;
    int currentLevel = 0;

    // Set of vertices at the current level
    std::vector<unsigned int> frontier;
    frontier.push_back(src);
    // Set of vertices at next level
    std::vector<unsigned int> nextFrontier;

    // Process frontier
    while (!frontier.empty()) {

        // Iterate vertices of frontier
        for (unsigned int vIdx : frontier) {

            // Parallelize process
            #pragma omp parallel
            {
                // Get thread id
                int threadID = omp_get_thread_num();
                // Get total number of threads
                int threadNum = omp_get_num_threads();

                // Traverse frontier together
                for (int i = threadID; i < frontier.size(); i += threadNum) {

                    // Each thead maintains their own local next frontier
                    std::vector<unsigned int> localNextFrontier;

                    // Iterate neighbors of vertex
                    for (Edge* e : graph.vertices[vIdx]->incidentEdges) {

                        // Check if vertex has been visited before
                        unsigned int vOpp = getOpposite(vIdx, *e, graph);
                        if (levels[vOpp] == -1) {

                            // Ensures that only one threads obtains the -1 value at that level
                            int insert;
                            #pragma omp atomic capture
                            {
                                // Add unexplored neighbors to new frontier
                                // nextFrontier.push_back(vOpp);
                                insert = levels[vOpp];
                                levels[vOpp] = currentLevel + 1;
                            }

                            // The thread that got -1 will add the unexplored vertex to new frontier
                            if (insert == -1) {
                                localNextFrontier.push_back(vOpp);
                            }
                        }
                    }

                    // Merge local next frontiers
                    #pragma omp critical
                    {
                        nextFrontier.insert(nextFrontier.end(), localNextFrontier.begin(), localNextFrontier.end());
                    }
                }
            }
        }

        // Move next frontier to current frontier
        frontier = nextFrontier;
        nextFrontier.clear();
        currentLevel++;
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
    // // Initialize visited vector
    // std::vector<bool> visited(graph.vertices.size(), false);
    // Initialize levels vector
    std::vector<int> levels(graph.vertices.size(), -1);

    // Iterate vertices of graph
    for (int i = 0; i < graph.vertices.size(); i++) {
        // Explore vertex if not visited
        if (levels[i] == -1) {
            // Traverse vertex until no more and add to components list
            parallelBFS(graph, i, levels);
            connectedComponentsList.push_back(graph.vertices[i]);
        }
    }

    return connectedComponentsList;
}

// /**
//  * @brief Gets the connected components of the graph
//  * 
//  * @param graph the graph to compute the algorithm on
//  * @return std::vector<Vertex*> the vertices to each connected component
//  */
// std::vector<Vertex*> getConnectedComponents(Graph& graph) {
//     // This marks the current set of connected components
//     int c = 0;
//     // This keeps track of the start vertex for each connected component
//     std::vector<Vertex*> connectedComponentsList;
//     // We iterate through every vertex in the graph
//     for (int i = 0; i < graph.vertices.size(); i++) {

//         // If we find a vertex that is no accounted for in a connected componet set, we run BFS
//         // and mark all the vertexes that we find
//         if (graph.vertices[i]->mark == -1) {

//             // We define a frontier of nodes to explorer starting with the first node
//             std::vector<Vertex*> frontier;
//             graph.vertices[i]->mark = c;
//             frontier.push_back(graph.vertices[i]);

//             //We go through each node in the frontier and add its children to the next frontier
//             while (frontier.size() > 0) {
//                 std::vector<Vertex*> next_frontier{};

//                 //We now break into out parallel processes
//                 #pragma omp parallel
//                 {   

//                     //Each thread gets its on frontier and ID
//                     std::vector<Vertex*> local_frontier{};
//                     int threadID = omp_get_thread_num();
//                     int threadNUM = omp_get_num_threads();

//                     //Each thread is responsible for looking at 1/threadNUM nodes
//                     for (int f = threadID; f < frontier.size(); f += threadNUM) {

//                         //We go through the incident edges of a frontier node when generating a new frontier
//                         for(int incidentEdge = 0; incidentEdge < frontier[f]->incidentEdges.size(); incidentEdge++) {

//                             //We grab the vertex opposite the one we had in the frontier
//                             Vertex* vertexToAdd = getOpposite(*frontier[f], *frontier[f]->incidentEdges[incidentEdge], graph);


//                             //If this new vertex has not been acounted for, do so and add it to the local frontier
//                             if (vertexToAdd->mark == -1) {
//                                 int insert;

//                                 // This is to ensure we don't accidently add the same node twice if two threads 
//                                 // happen to be looking at the same node at the same time.
//                                 #pragma omp critical
//                                 {
//                                     insert = vertexToAdd->mark;
//                                     vertexToAdd->mark = c;
//                                 }
                                
//                                 if (insert > -1)
//                                     local_frontier.push_back(vertexToAdd);
//                             }
//                         }
//                     }

//                     //Ensures that each thread takes turns with merging there discovered frontier together
//                     #pragma omp critical
//                     {
//                         if (local_frontier.size() > 0)
//                             next_frontier.insert(next_frontier.end(), local_frontier.begin(), local_frontier.end());
//                     }
//                 }
//                 //The frontier is replaced with a new frontier
//                 frontier = next_frontier;
//             }
//             //We at this point would have found all nodes connected to a given connected set and can increment
//             //to start looking for any new connected sets.
//             c++;
//             connectedComponentsList.push_back(graph.vertices[i]);
//         }
//     }
//     return connectedComponentsList;
// }
