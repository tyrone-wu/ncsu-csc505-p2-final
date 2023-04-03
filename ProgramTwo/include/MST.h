/**
 * @file MST.h
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * 
 * @brief Class for bringing in the Minimum Spanning Tree functionality to main.
 * 
 */

#ifndef MST_H
#define MST_H

#include <iostream>
#include <vector>
#include "./Edge.h"
#include "./Graph.h"

/**
 * @brief Computes the Minimum Spanning Tree on the given graph
 * 
 * @param capacity 
 * @return std::vector<Edge*> 
 */
std::vector<Edge*> mst(Graph* graph);

/**
 * @brief Prints the edges of the minimum spanning tree
 * 
 * @param edges the edges of the MST
 */
void printMST(Graph* graph, std::vector<Edge*> edges) {
    // g line
    std::cout << "g " << graph->vertices.size() << " " << graph->edges.size() << std::endl;

    // e lines
    for (auto e : edges) {
        e->printEdge();
    }
}

#endif // MST_H