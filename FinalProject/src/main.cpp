/**
 * @file main.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The main class that parses the input and calls a MST function.
 * 
 */

#include <iostream>
#include <iomanip>
#include "../include/ParseGraph.h"
#include "../include/Graph.h"
#include "../include/Edge.h"
#include "../include/Time.h"

using namespace std;

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

    // Path to graph file
    string path = argv[1];

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

    // Perform benchmark on the MST
    Timer timer;

    // Benchmark mst
    timer.start();
    // algorithm goes here
    timer.stop();

    // Print number of connected components

    // Print the benchmark to standard error
    // cerr << "weight      " << /* connected components */ << endl;
    cerr << "runtime     " << fixed << setprecision(2) << timer.getTotalTime() << endl;

    return 0;
}
