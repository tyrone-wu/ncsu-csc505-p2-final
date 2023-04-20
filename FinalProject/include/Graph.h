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
    Graph(unsigned int numVerticies, unsigned int numEdges);

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
     * @param filePath the gph file to read
     */
    void readFile(std::string filePath);
};

#endif // GRAPH_H
