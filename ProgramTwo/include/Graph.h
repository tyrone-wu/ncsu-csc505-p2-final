/**
 * @file Graph.h
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief Classes that defines the graph data structure.
 * 
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "./Vertex.h"
#include "./Edge.h"

class Graph {
public:

    // List of pointers to the vertices
    std::vector<Vertex*> vertices;
    // List of pointers to the edges
    std::vector<Edge*> edges;

    /**
     * @brief Construct an empty graph with the given capacities.
     * 
     * @param numVerticies the number of vertices to expect
     * @param numEdges the number of edges to expect
     */
    Graph(unsigned int numVerticies, unsigned int numEdges) {
        this->vertices = std::vector<Vertex*>(numVerticies, nullptr);
        this->edges.reserve(numEdges * 2);
    }

    /**
     * @brief Adds a vertex to the graph with the id, x, and y value.
     * 
     * @param id the id of the vertex
     * @param x the x coordinate
     * @param y the y coordinate
     * @return Vertex* the added vertex
     */
    Vertex* addVertex(unsigned int id, int x, int y);

    /**
     * @brief Adds a vertex to the graph with the id.
     * 
     * @param id the id of the vertex
     * @return Vertex* the added vertex
     */
    Vertex* addVertex(unsigned int id);

    /**
     * @brief Adds an edge to the graph as well as the incident edge to the node
     * 
     * @param source the source vertex
     * @param destination the destination vertex
     * @param weight the edge weight
     */
    void addEdge(unsigned int source, unsigned int destination, int weight);
};

#endif // GRAPH_H
