/**
 * @file Graph.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The graph data structure.
 * 
 */

#include <iostream>
#include <sstream>
#include "../include/Graph.h"

/**
 * @brief Construct an empty graph with the given capacities.
 * 
 * @param numVerticies the number of vertices to expect
 * @param numEdges the number of edges to expect
 */
Graph::Graph(unsigned int numVerticies, unsigned int numEdges) {
    this->vertices = std::vector<Vertex*>(numVerticies, nullptr);
    this->edges.reserve(numEdges);
}

/**
 * @brief Adds a vertex to the graph with the id.
 * 
 * @param id the index of the vertex
 */
Vertex* Graph::addVertex(unsigned int id) {
    return this->addVertex(id);
}

/**
 * @brief Adds an edge to the graph as well as the incident edge to the node
 * 
 * @param source the source vertex
 * @param destination the destination vertex
 */
void Graph::addEdge(unsigned int source, unsigned int destination) {
    Vertex* srcVertex = this->addVertex(source);
    Vertex* dstVertex = this->addVertex(destination);

    Edge* edge = new Edge(source, destination);
    srcVertex->addEdge(edge);
    dstVertex->addEdge(edge);
    this->edges.push_back(edge);
}

/**
 * @brief Prints the graph for debugging purposes.
 * 
 */
void Graph::printGraph() {
    // Prints the vertices
    for (Vertex* v : this->vertices) {
        std::cout << "v - " << v->id << std::endl;
        for (Edge* e : v->incidentEdges) {
            std::cout << "src: " << e->source  << ", dst: " << e->destination << std::endl;
        }
        std::cout << std::endl;
    }

    // Prints the edges
    for (Edge* e : this->edges) {
        std::cout << "e - src: " << e->source << ", dst: " << e->destination << std::endl;
    }
}

/**
 * @brief Reads file to graph object
 * 
 * @param filePath the gph file to read
 */
void Graph::readFile(std::string filePath) {
    
}
