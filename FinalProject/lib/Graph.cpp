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
#include <fstream>
#include "../include/ParseGraph.h"
#include "../include/Graph.h"

/**
 * @brief Construct an empty graph.
 * 
 */
Graph::Graph() {}

/**
 * @brief Construct an empty graph with the given capacities.
 * 
 * @param numVerticies the number of vertices to expect
 * @param numEdges the number of edges to expect
 */
void Graph::addCapacity(unsigned int numVerticies, unsigned int numEdges) {
    // this->vertices = std::vector<Vertex*>(numVerticies, nullptr);
    this->vertices.resize(this->vertices.size() + numVerticies, nullptr);
    this->edges.reserve(this->edges.capacity() + numEdges);
}

/**
 * @brief Adds a vertex to the graph with the id.
 * 
 * @param id the index of the vertex
 */
Vertex* Graph::addVertex(unsigned int id) {
    if (this->vertices[id] == nullptr) {
        this->vertices[id] = new Vertex(id);
    }
    return this->vertices[id];
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
        std::cout << "v " << (v->id + 1) << std::endl;
        for (Edge* e : v->incidentEdges) {
            e->printEdge();
        }
        std::cout << std::endl;
    }

    // Prints the edges
    for (Edge* e : this->edges) {
        e->printEdge();
    }
}

/**
 * @brief Reads file to graph object
 * 
 * @param filePath the gph file to read
 */
void Graph::readFile(Graph* graph, std::string filePath) {
    // Offset for a new graph
    unsigned int offset = this->vertices.size();

    // Parse input into the graph object
    std::string line;
    std::ifstream infile(filePath);

    while (std::getline(infile, line)) {
        switch(line[0]) {
            case 'g':
                parseGraph(*graph, line);
                break;
            case 'n':
                parseNode(*graph, line, offset - 1);
                break;
            case 'e':
                parseEdge(*graph, line, offset - 1);
                break;
            default:
                continue;
        }
    }

    infile.close();
}

/**
 * @brief Frees the memory of the graph.
 * 
 */
void Graph::freeMemory() {
    // Free edges
    for (Edge* e : this->edges) {
        delete e;
    }
    this->edges.clear();

    // Free vertices
    for (Vertex* v : this->vertices) {
        v->incidentEdges.clear();
        delete v;
    }
    this->vertices.clear();
}
