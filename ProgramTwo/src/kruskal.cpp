/**
 * @file kruskal.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The Kruskal's MST implementation. 
 * 
 */

#include <vector>
#include "../include/MST.h"
#include "../include/Graph.h"
#include "../include/Edge.h"
#include "../include/Vertex.h"

/**
 * @brief Computes the Minimum Spanning Tree using Kruskal's algorithm
 * 
 * @param graph the graph to compute the MST on
 * @return std::vector<Edge*> the edges of the MST
 */
std::vector<Edge*> computeMST(Graph* graph) {
    // Allocate memory for number of edges in the MST
    std::vector<Edge*> mst;
    mst.reserve(graph->vertices.size() - 1);

    // implementation here
    

    return mst;
}