/**
 * @file Edge.h
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief Classes that defines the edge data structure.
 * 
 */

#ifndef EDGE_H
#define EDGE_H

#include <iostream>

class Edge {
public:

    // The index of the source vertex
    unsigned int source;
    // The index of the destination vertex
    unsigned int destination;

    /**
     * @brief Construct a new Edge object with the given data.
     * 
     * @param source the source vertex index
     * @param destination the destination vertex index
     */
    Edge(unsigned int source, unsigned int destination);

    /**
     * @brief Prints the edge in the format: e source target weight
     * 
     */
    void printEdge();
};

#endif // EDGE_H
