/**
 * @file Vertex.h
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief Classes that defines the vertex data structure.
 * 
 */

#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "./Edge.h"
#include <string>

class Vertex {
public:

    // The vertex unique ID
    unsigned int id;
    // List of incident edges which are indices to the vertex
    std::vector<unsigned int> incidentEdges;
    // The Vertex's lablel
    int label;

    /**
     * @brief Construct a new Vertex object with the given data.
     * 
     * @param id the unique id of the vertex
     * @param x the x coordinate of the vertex
     * @param y the y coordinate of the vertex
     */
    Vertex(unsigned int id);

    /**
     * @brief Adds an incident edge to the vertex.
     * 
     * @param source the source vertex index
     * @param destination the destination vertex index
     */
    void addEdge(unsigned int source, unsigned int destination);
};

#endif // VERTEX_H
