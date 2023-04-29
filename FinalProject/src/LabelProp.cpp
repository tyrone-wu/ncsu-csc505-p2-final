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
#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <random>
#include <algorithm>
#include "omp.h"
#include "../include/GraphComponents.h"

using namespace std;

//This just grabs the node opposite of vertex v through Edge e in Graph g
int getOpposite(Vertex* v, Edge* e, Graph graph){
    Vertex* r = graph.vertices[e->destination];
    // std::cout << "Vertex ID: " << r->id << std::endl;
    if(r->id == v->id)
        return graph.vertices[e->source]->id;
    return r->id;
}

std::vector<int> generateLabels(int length)
{
    std::vector<int> ret = std::vector<int>();
    ret.resize(length);

    for (int i = 0; i < length; i++)
    {
      ret.at(i) = i;
    }

    return ret;
}

/**
 * @brief Gets the connected components of the graph
 * 
 * @param graph the graph to compute the algorithm on
 * @return std::vector<Vertex*> the vertices to each connected component
 */
vector<Vertex*> getConnectedComponents(Graph& graph, const unsigned int threads){
    // This marks the current set of connected components
    int c = 0;
    // This keeps track of the start vertex for each connected component
    vector<Vertex*> connectedComponentsList;

    // The list of labels for all of the vertexes
    std::vector<int> labels = generateLabels(graph.vertices.size());
    

    //We keep track of if there was a change
    bool change;

    // We iterate through every vertex and set its label to match the majority of its neiighbors
    // until there are no updates
    do {
        change = false;
        // Process current frontier
        #pragma omp parallel num_threads(threads)
        #pragma omp for
        for (int i = 0; i < graph.vertices.size(); i++) {
            Vertex* v = graph.vertices[i];

            unsigned int min = labels[v->id];
            //Here we find the minimum label between a given vertex and it's neighbors 
            for (int edge = 0; edge < v->incidentEdges.size(); edge++) {
                int neighborID = v->incidentEdges[edge];
                if (labels[neighborID] < min)
                    min = labels[neighborID];
            }

            if (labels[v->id] != min) {
                    labels[v->id] = min;
                    change = true;
            }

            //Set all the neighbors to equal the new min value
            for (int edge = 0; edge < v->incidentEdges.size(); edge++) {
                int neighborID = v->incidentEdges[edge];
                if (labels[neighborID] > min){
                    labels[neighborID] = min;
                    change = true;
                }
            }

        }
    } while (change);

    //Now we collect the unique labels as those make up our connected components list
    connectedComponentsList.push_back(graph.vertices[0]);
   
    for (int i = 1; i < graph.vertices.size(); i++) {

        int label = labels[i];
        bool inList = false;
        for (int comp = 0; comp < connectedComponentsList.size(); comp++) {
            if (label == labels[connectedComponentsList[comp]->id])
                inList = true;
        }

        if (!inList)
        {
            connectedComponentsList.push_back(graph.vertices[i]);
        }
    }

    return connectedComponentsList;
}