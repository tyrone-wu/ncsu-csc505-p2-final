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

using namespace std;

// Global counter for number of comparison operators performed.
unsigned long long compares;

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

void parseNode(Graph* graph, string &line) {
    // Parse line into vector of tokens
    vector<string> tokens;
    parseTokens(line, tokens);

    graph->addVertex(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));
}

void parseEdge(Graph* graph, string &line) {
    // Parse line into vector of tokens
    vector<string> tokens;
    parseTokens(line, tokens);

    graph->addEdge(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));
}

int main(int argc, char* argv[]) {
    // The graph data structure
    Graph* graph;

    // Parse input line by line
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

    // for (Vertex* v : graph->vertices) {
    //     cout << "Vertex: " << v->id << " " << v->x << " " << v->y << endl;
    //     for (Edge* e : v->incidentEdges) {
    //         cout << e->source  << " " << e->destination << " " << e->weight << endl;
    //     }
    //     cout << endl;
    // }

    // for (Edge* e : graph->edges) {
    //     cout << "Edge: " << e->source << " " << e->destination << " " << e->weight << endl;
    // }

    return 0;
}
