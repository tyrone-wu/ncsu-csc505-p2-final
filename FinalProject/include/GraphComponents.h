/**
 * @file GraphComponents.h
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * 
 * @brief Class for bringing in the connected components algorithm.
 * 
 */

#ifndef GRAPHCOMPONENTS_H
#define GRAPHCOMPONENTS_H

#include <vector>
#include "./Vertex.h"
#include "./Graph.h"

/**
 * @brief Gets the connected components of the graph
 * 
 * @param graph the graph to compute the algorithm on
 * @param threads number of threads to utilize
 * @return std::vector<Vertex*> the vertices to each connected component
 */
std::vector<Vertex*> getConnectedComponents(Graph& graph, const unsigned int threads);

#endif // GRAPHCOMPONENTS_H