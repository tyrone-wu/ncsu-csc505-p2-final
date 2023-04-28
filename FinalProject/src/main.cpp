/**
 * @file main.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The main class that parses the input and calls a MST function.
 * 
 */

#include <iostream>
#include <filesystem>
#include <iomanip>
#include "../include/Graph.h"
#include "../include/Edge.h"
#include "../include/Time.h"
#include "../include/GraphComponents.h"

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
    if (argc != 3) {
        cerr << "Invalid arguments" << endl;
        return 1;
    }

    // Path to graph file
    string path = argv[1];
    const unsigned int threads = stoi(argv[2]);

    // The graph data structure
    Graph graph;
    // Parse files into graph
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        graph.readFile(&graph, entry.path().string());
    }

    // Perform benchmark
    Timer timer;
    timer.start();
    vector<Vertex*> components = getConnectedComponents(graph, threads);
    timer.stop();

    // Print number of components to standard output
    cout << components.size() << endl;

    // Print the benchmark to standard error
    cerr << "num components " << components.size() << endl;
    cerr << "threads        " << threads << endl;
    cerr << "runtime        " << fixed << setprecision(2) << timer.getTotalTime() << endl;

    // Free memory
    graph.freeMemory();

    return 0;
}
