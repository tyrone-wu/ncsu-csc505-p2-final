/**
 * @file Vertex.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The vertex data structure of a graph.
 * 
 */

#include "../include/Vertex.h"

/**
 * @brief Adds an incident edge to the vertex.
 * 
 * @param source the source vertex index
 * @param destination the destination vertex index
 * @param weight the edge weight
 */
void Vertex::addEdge(unsigned int source, unsigned int destination, int weight) {
    this->incidentEdges.push_back(new Edge(source, destination, weight));
}

/**
 * @brief Adds an incident edge to the vertex.
 * 
 * @param edge the edge to add
 */
void Vertex::addEdge(Edge* edge) {
    this->incidentEdges.push_back(edge);
}
