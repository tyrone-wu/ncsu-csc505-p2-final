/**
 * @file Edge.h
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief Classes that defines the edge data structure.
 * 
 */

#include <iostream>
#include "../include/Edge.h"

/**
 * @brief Construct a new Edge object with the given data.
 * 
 * @param source the source vertex index
 * @param destination the destination vertex index
 */
Edge::Edge(unsigned int source, unsigned int destination) {
    this->source = source;
    this->destination = destination;
}

/**
 * @brief Prints the edge in the format: e source target weight
 * 
 */
void Edge::printEdge() {
    std::cout << "e " << (this->source + 1) << " " << (this->destination + 1) << " " << 1 << std::endl;
}
