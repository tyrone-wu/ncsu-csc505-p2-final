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
     * @brief Construct a new add Capacity object
     * 
     * @param numVerticies the number of vertices to expect
     * @param numEdges the number of edges to expect
     */
    void addCapacity(unsigned int numVerticies, unsigned int numEdges);

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
     */
    void addEdge(unsigned int source, unsigned int destination);

    /**
     * @brief Prints the graph for debugging purposes.
     * 
     */
    void printGraph();

    /**
     * @brief Reads file to graph object
     * 
     * @param graph the graph to store in
     * @param filePath the gph file to read
     */
    void readFile(Graph* graph, std::string filePath);

    /**
     * @brief Frees the memory of the graph.
     * 
     */
    void freeMemory();
};

#endif // GRAPH_H
