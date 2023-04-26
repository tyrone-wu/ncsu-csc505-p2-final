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
 * @brief Construct a new Vertex object with the given data.
 * 
 * @param id the unique id of the vertex
 */
Vertex::Vertex(unsigned int id) {
    this->id = id;
}

/**
 * @brief Adds an incident edge to the vertex.
 * 
 * @param source the source vertex index
 * @param destination the destination vertex index
 * @param weight the edge weight
 */
void Vertex::addEdge(unsigned int source, unsigned int destination) {
    if (this->id == source) {
        this->incidentEdges.push_back(destination);
    } else {
        this->incidentEdges.push_back(source);
    }
}
