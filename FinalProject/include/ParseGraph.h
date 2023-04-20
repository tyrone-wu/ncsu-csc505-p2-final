/**
 * @file ParseGraph.h
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief Classes that parses gph file format.
 * 
 */

#ifndef PARSEGRAPH_H
#define PARSEGRAPH_H

#include <vector>
#include <sstream>
#include "./Graph.h"
#include "./Vertex.h"
#include "./Edge.h"

/**
 * @brief Parse the line into a vector of tokens
 * 
 * @param line the line to parse
 * @param tokens the vector to place the tokens in
 */
void parseTokens(std::string &line, std::vector<std::string> &tokens) {
    std::istringstream iss(line);
    std::string token;
    while (getline(iss, token, ' ')) {
        std::stringstream ss(token);
        while(std::getline(ss, token, '\t')){
            tokens.push_back(token);
        }
    }
}

/**
 * @brief Parse the line to return a graph object.
 * 
 * @param line the line to parse
 * @return Graph* the graph with the parsed line data
 */
Graph* parseGraph(std::string &line) {
    // Parse line into vector of tokens
    std::vector<std::string> tokens;
    parseTokens(line, tokens);

    return new Graph(stoi(tokens[1]), stoi(tokens[2]));
}

/**
 * @brief Parse the node line
 * 
 * @param graph the graph to store in
 * @param line the line to parse
 */
void parseNode(Graph* graph, std::string &line) {
    // Parse line into vector of tokens
    std::vector<std::string> tokens;
    parseTokens(line, tokens);

    graph->addVertex(stoi(tokens[1]) - 1);
}

/**
 * @brief Parse the edge line
 * 
 * @param graph the graph to store in
 * @param line the line to parse
 */
void parseEdge(Graph* graph, std::string &line) {
    // Parse line into vector of tokens
    std::vector<std::string> tokens;
    parseTokens(line, tokens);

    graph->addEdge(stoi(tokens[1]) - 1, stoi(tokens[2]) - 1);
}

#endif // PARSEGRAPH_H
