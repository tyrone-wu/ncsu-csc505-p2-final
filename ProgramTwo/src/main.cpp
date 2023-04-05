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
#include "../include/Edge.h"
#include "../include/BinaryHeap.h"
#include "../include/MST.h"
#include "../include/Time.h"

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

    graph->addVertex(stoi(tokens[1]) - 1, stoi(tokens[2]), stoi(tokens[3]));
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

    graph->addEdge(stoi(tokens[1]) - 1, stoi(tokens[2]) - 1, stoi(tokens[3]));
}

/**
 * @brief Prints the edges of the minimum spanning tree
 * 
 * @param edges the edges of the MST
 */
void printMST(Graph* graph, std::vector<Edge*> edges) {
    // g line
    cout << "g " << graph->vertices.size() << " " << edges.size() << endl;

    // e lines
    for (auto e : edges) {
        e->printEdge();
    }
}

/**
 * @brief Calculates the total weight of the MST
 * 
 * @param edges the edges of the MST
 * @return long the total weight of the MST
 */
long long totalWeight(vector<Edge*> edges) {
    long long sum = 0;
    for (auto e : edges) {
        sum += e->weight;
    }
    return sum;
}

/**
 * @brief The main driver of the program.
 * 
 * @param argc the number of arguments
 * @param argv the list of arguments
 * @return int the return status of the program
 */
int main(int argc, char* argv[]) {
    // Exit error if no arguments passed
    if (argc != 2) {
        cerr << "Invalid arguments" << endl;
        return 1;
    }

    // Set k value for DHeap. k = 1 for binary heap
    unsigned int k = stoi(argv[1]);

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

    // Initialize comparison counter
    compares = 0;
    // Perform benchmark on the MST
    Timer timer;

    // Benchmark mst
    timer.start();
    vector<Edge*> mst = computeMST(graph, k);
    timer.stop();

    // Exit with error if graph is not connected
    if (graph->vertices.size() - 1 != mst.size()) {
        cerr << "Error: Graph is not connected." << endl;
        return 1;
    }

    // Print edges of mst to standard output
    printMST(graph, mst);

    // Print the benchmark to standard error
    cerr << "weight      " << totalWeight(mst) << endl;
    cerr << "runtime     " << timer.getTotalTime() << endl;
    cerr << "comparisons " << compares << endl;

    return 0;
}
