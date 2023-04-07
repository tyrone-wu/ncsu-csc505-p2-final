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
#include <limits>

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

    // Heap Location for Prims
    unsigned int idHeap;
    // Edge used in the minheap for Prims
    Edge* edge = nullptr;
    // Distance for Prims
    int distance = std::numeric_limits<int>::max();
    // Used to mark a vertex
    bool marked = false;

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
        this->idHeap = id;
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

    /**
     * @brief Compares the two vertices.
     * 
     * @param op the operator to use
     * @param lhs the left hand side's vertex
     * @param rhs the right hand side's vertex
     * @return true if the operator evaluates to true; otherwise, false
     */
    static bool cmp(Vertex* lhs, Operator op, Vertex* rhs) {
        // Increment compares
        compares++;

        switch (op) {
            case LESS:
                return lhs->distance < rhs->distance;
            case LESS_EQUALS:
                return lhs->distance <= rhs->distance;
            case EQUALS:
                return lhs->distance == rhs->distance;
            case GREATER:
                return lhs->distance > rhs->distance;
            case GREATER_EQUALS:
                return lhs->distance >= rhs->distance;
            case NOT_EQUALS:
                return lhs->distance != rhs->distance;
        }
    }
};

#endif // VERTEX_H
