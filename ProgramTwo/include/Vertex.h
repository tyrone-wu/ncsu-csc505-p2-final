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

class Vertex {
public:

    // The vertex unique ID
    unsigned int id;
    // x coordinate (optional)
    int x;
    // y coordinate (optional)
    int y;
    // List of incident edges
    std::vector<Edge*> incidentEdges;

    /**
     * @brief Construct a new Vertex object with the given data.
     * 
     * @param id the unique id of the vertex
     * @param x the x coordinate of the vertex
     * @param y the y coordinate of the vertex
     */
    Vertex(unsigned int id, int x, int y) {
        this->id = id;
        this->x = x;
        this->y = y;
    }

    /**
     * @brief Adds an incident edge to the vertex.
     * 
     * @param source the source vertex index
     * @param destination the destination vertex index
     * @param weight the edge weight
     */
    void addEdge(unsigned int source, unsigned int destination, int weight);

    /**
     * @brief Adds an incident edge to the vertex.
     * 
     * @param edge the edge to add
     */
    void addEdge(Edge* edge);
};

#endif // VERTEX_H
