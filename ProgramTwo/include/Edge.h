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

class Edge {
public:

    // The index of the source vertex
    unsigned int source;
    // The index of the destination vertex
    unsigned int destination;
    // The weight of the edge
    int weight;

    /**
     * @brief Construct a new Edge object with the given data.
     * 
     * @param source the source vertex index
     * @param destination the destination vertex index
     * @param weight the edge weight
     */
    Edge(unsigned int source, unsigned int destination, int weight) {
        this->source = source;
        this->destination = destination;
        this->weight = weight;
    }
};

#endif // EDGE_H
