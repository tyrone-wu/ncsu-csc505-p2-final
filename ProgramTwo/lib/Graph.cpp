/**
 * @file Graph.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The graph data structure.
 * 
 */

#include <iostream>
#include "../include/Graph.h"

/**
 * @brief Adds a vertex to the graph with the id, x, and y value.
 * 
 * @param id the id of the vertex
 * @param x the x coordinate
 * @param y the y coordinate
 */
Vertex* Graph::addVertex(unsigned int id, int x, int y) {
    if (this->vertices[id - 1] == nullptr) {
        this->vertices[id - 1] = new Vertex(id, x, y);
    }
    return this->vertices[id - 1];
}

/**
 * @brief Adds a vertex to the graph with the id.
 * 
 * @param id the id of the vertex
 */
Vertex* Graph::addVertex(unsigned int id) {
    return this->addVertex(id, 0, 0);
}

/**
 * @brief Adds an edge to the graph as well as the incident edge to the node
 * 
 * @param source the source vertex
 * @param destination the destination vertex
 * @param weight the edge weight
 */
void Graph::addEdge(unsigned int source, unsigned int destination, int weight) {
    Vertex* srcVertex = this->addVertex(source);
    Vertex* dstVertex = this->addVertex(destination);

    Edge* to = new Edge(source, destination, weight);
    srcVertex->addEdge(to);
    // srcVertex->addEdge(source, destination, weight);
    this->edges.push_back(to);

    Edge* from = new Edge(destination, source, weight);
    dstVertex->addEdge(from);
    // dstVertex->addEdge(destination, source, weight);
    this->edges.push_back(from);
}

/**
 * @brief Prints the graph for debugging purposes.
 * 
 */
void Graph::printGraph() {
    // Prints the vertices
    for (Vertex* v : this->vertices) {
        std::cout << "v - " << v->id << ", x: " << v->x << ", y: " << v->y << std::endl;
        for (Edge* e : v->incidentEdges) {
            std::cout << "src: " << e->source  << ", dst: " << e->destination << ", w: " << e->weight << std::endl;
        }
        std::cout << std::endl;
    }

    // Prints the edges
    for (Edge* e : this->edges) {
        std::cout << "e - src: " << e->source << ", dst: " << e->destination << ", w: " << e->weight << std::endl;
    }
}
