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

// Global counter for number of comparison operators performed.
extern unsigned long long compares;

// The possible comparison operators
enum Operator {
    LESS,
    LESS_EQUALS,
    EQUALS, 
    GREATER,
    GREATER_EQUALS,
    NOT_EQUALS
};

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

    /**
     * @brief Prints the edge in the format: e source target weight
     * 
     */
    void printEdge() {
        std::cout << "e " << (this->source + 1) << " " << (this->destination + 1) << " " << this->weight << std::endl;
    }

    /**
     * @brief Compares the two edges weight.
     * 
     * @param op the operator to use
     * @param lhs the left hand side's edge
     * @param rhs the right hand side's edge
     * @return int -1 if lhs edge weight is less than rhs edge weight; 0 if edges weights are equal; 1 if lhs edge weight is greater than rhs edge weight
     */
    static bool cmp(Edge* lhs, Operator op, Edge* rhs) {
        // Increment compares
        compares++;

        switch (op) {
            case LESS:
                return lhs->weight < rhs->weight;
            case LESS_EQUALS:
                return lhs->weight <= rhs->weight;
            case EQUALS:
                return lhs->weight == rhs->weight;
            case GREATER:
                return lhs->weight > rhs->weight;
            case GREATER_EQUALS:
                return lhs->weight >= rhs->weight;
            case NOT_EQUALS:
                return lhs->weight != rhs->weight;
        }
    }
};

#endif // EDGE_H
