/**
 * @file main.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The main class that parses the input and calls a MST function.
 * 
 */

#include <iostream>
#include <string>
#include <sstream>
#include "../include/Graph.h"
#include "../include/BinaryHeap.h"

using namespace std;

// Global counter for number of comparison operators performed.
unsigned long long compares;

/**
 * @brief Parse the line into a vector of tokens
 * 
 * @param line the line to parse
 * @param tokens the vector to place the tokens in
 */
void parseTokens(string &line, vector<string> &tokens) {
    istringstream iss(line);
    string token;
    while (getline(iss, token, ' ')) {
        tokens.push_back(token);
    }
}

/**
 * @brief Parse the line to return a graph object.
 * 
 * @param line the line to parse
 * @return Graph* the graph with the parsed line data
 */
Graph* parseGraph(string &line) {
    // Parse line into vector of tokens
    vector<string> tokens;
    parseTokens(line, tokens);

    return new Graph(stoi(tokens[1]), stoi(tokens[2]));
}

/**
 * @brief Parse the node line
 * 
 * @param graph the graph to store in
 * @param line the line to parse
 */
void parseNode(Graph* graph, string &line) {
    // Parse line into vector of tokens
    vector<string> tokens;
    parseTokens(line, tokens);

    graph->addVertex(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));
}

/**
 * @brief Parse the edge line
 * 
 * @param graph the graph to store in
 * @param line the line to parse
 */
void parseEdge(Graph* graph, string &line) {
    // Parse line into vector of tokens
    vector<string> tokens;
    parseTokens(line, tokens);

    graph->addEdge(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));
}

/**
 * @brief The main driver of the program.
 * 
 * @param argc the number of arguments
 * @param argv the list of arguments
 * @return int the return status of the program
 */
int main(int argc, char* argv[]) {
    // The graph data structure
    Graph* graph;

    // Parse input into the graph object
    string line;
    while (getline(cin, line)) {
        switch(line[0]) {
            case 'g':
                graph = parseGraph(line);
                break;
            case 'n':
                parseNode(graph, line);
                break;
            case 'e':
                parseEdge(graph, line);
                break;
            default:
                continue;
        }
    }

    graph->printGraph();

    BinaryHeap* heap = new BinaryHeap(graph->edges);
    heap->printHeap();

    // heap->heapsort();
    // heap->printHeap();

    return 0;
}
