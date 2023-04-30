/**
 * @file BFS.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * 
 * @brief Class for bringing in the connected components algorithm using BFS.
 * 
 */

#include <vector>
#include <set>
#include <omp.h>
#include "../include/GraphComponents.h"

// Generate sequentially filled vector of size length
std::vector<unsigned int> generateLabels(int length) {
    std::vector<unsigned int> ret;
    ret.resize(length);
    for (int i = 0; i < length; i++) {
        ret[i] = i;
    }

    return ret;
}

/**
 * @brief Gets the connected components of the graph
 * 
 * @param graph the graph to compute the algorithm on
 * @param threads number of threads to spawn
 * @return std::vector<Vertex*> the vertices to each connected component
 */
std::vector<Vertex*> getConnectedComponents(Graph& graph, const unsigned int threads) {
    // This keeps track of the start vertex for each connected component
    std::vector<Vertex*> connectedComponentsList;

    // The list of labels for all of the vertexes
    std::vector<unsigned int> labels = generateLabels(graph.vertices.size());
    // We keep track of if there was a change
    bool change;

    // We iterate through every vertex and set its label to match the majority of its neiighbors
    // until there are no updates
    do {
        // Track if further change/propagation is needed
        change = false;

        // Propagate label
        #pragma omp parallel for num_threads(threads)
        for (int i = 0; i < graph.vertices.size(); i++) {
            Vertex v = *graph.vertices[i];
            std::vector<unsigned int> incidentEdges = v.incidentEdges;

            unsigned int min = labels[v.id];
            // Here we find the minimum label between a given vertex and it's neighbors 
            for (int edge = 0; edge < incidentEdges.size(); edge++) {
                int neighborID = incidentEdges[edge];
                if (labels[neighborID] < min)
                    min = labels[neighborID];
            }

            if (labels[v.id] != min) {
                labels[v.id] = min;
                change = true;
            }

            //Set all the neighbors to equal the new min value
            for (int edge = 0; edge < incidentEdges.size(); edge++) {
                int neighborID = incidentEdges[edge];
                if (labels[neighborID] > min) {
                    labels[neighborID] = min;
                    change = true;
                }
            }

        }
    } while (change);

    // Now we collect the unique labels as those make up our connected components list
    std::set<unsigned int> ccLabels;
    for (int i = 0; i < labels.size(); i++) {
        if (!ccLabels.contains(labels[i])) {
            ccLabels.insert(labels[i]);
            connectedComponentsList.push_back(graph.vertices[i]);
        }
    }

    return connectedComponentsList;
}