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
 * @param graph the graph to compute the MST on
 * @return std::vector<Edge*> the edges of the MST
 */
std::vector<Edge*> computeMST(Graph* graph);

#endif // MST_H