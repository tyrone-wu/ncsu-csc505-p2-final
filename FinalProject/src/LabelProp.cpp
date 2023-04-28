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
Vertex* getOpposite(Vertex& v, Edge& e, Graph& graph){
    Vertex* r = graph.vertices[e.destination];
    // std::cout << "Vertex ID: " << r->id << std::endl;
    if(r->id == v.id)
        return graph.vertices[e.source];
    return r;
}

std::vector<int> fillUnique(int length, int min, int max)
{
    std::cout << "Length: " << length << " Min: " << min << " Max: " << max << std::endl;
    std::vector<int> ret = std::vector<int>();
    ret.resize(length);

    // Store each random number generated
    int new_random;

    // Helps to verify whether the random number generated is unique
    bool unique;
    
    for (int i = 0; i < length; i++)
    {
      do
      {
        new_random = (rand() % (max - min + 1)) + min;

        unique = true;
        for (int j = 0; j < i; j++)
          if (ret.at(j) == new_random) unique = false;
      }
      while (!unique);
      ret.at(i) = new_random;
    }

    return ret;
}

/**
 * @brief Gets the connected components of the graph
 * 
 * @param graph the graph to compute the algorithm on
 * @return std::vector<Vertex*> the vertices to each connected component
 */
vector<Vertex*> getConnectedComponents(Graph& graph){
    // This marks the current set of connected components
    int c = 0;
    // This keeps track of the start vertex for each connected component
    vector<Vertex*> connectedComponentsList;

    //We keep track of if there was a change
    bool change;

    // Counter to curb the runtime
    int maxIterations = 100;

    // We iterate through every vertex and set its label to match the majority of its neiighbors
    // until there are no updates
    do {
        change = false;
        std::vector<int> randomizedVertices = fillUnique(graph.vertices.size(), 0, graph.vertices.at(graph.vertices.size() - 1)->id);
        for (int i = 0; i < randomizedVertices.size(); i++) {
            Vertex* v = graph.vertices[randomizedVertices.at(i)];
            std::cout << "ID of the current Vertex: " << v->id << std::endl;
            // std::cout << "Label of the vertex: " << v->label << std::endl;
            std::map<int, int> counter;
            // vector<Edge*> incidentEdges = v->incidentEdges;

            //Here we are seeing what all the neighbors are labled as
            for (int edge = 0; edge < v->incidentEdges.size(); edge++) {
                // int oppositeVertex = graph.edges[edge].;
                counter[getOpposite(*v, *graph.edges[edge], graph)->label]++;
            }

            //Here we see what the which lable appears the most
            std::map<int,int>::iterator max = counter.begin();
            for (std::map<int,int>::iterator it = ++(counter.begin()); it != counter.end(); ++it) {
                std::cout << "Current max: " << max->first << " Check against: " << it->first << " " << it->second << std::endl;
                if (it->second > max->second)
                    max = it;
                // If we have the same amount of two labels, the smaller label value is chosen
                if (it->second == max->second)
                {
                    if (it->first < max->first)
                    {
                        max = it;
                    }
                }
            }

            // We update the label if it does not match the majority of its neighbors
            if (v->label == max->first) {
                change = true;
                v->label = max->first;
            }
        }
        maxIterations--;
        if (maxIterations == 0)
        {
            change = false;
        }
    } while (change);

    std::cout << "Finished the vertex updating" << std::endl;

    //Now we collect the unique labels as those make up our connected components list
    connectedComponentsList.push_back(graph.vertices[0]);
    std::cout << graph.vertices[0]->label << std::endl;
    for (int i = 1; i < graph.vertices.size(); i++) {
        int label = graph.vertices[i]->label;
        std::cout << "Label of the Vertex: " << label << " Vertex ID: " << graph.vertices[i]->id << std::endl;
        bool inList = false;
        for (int comp = 0; comp < connectedComponentsList.size(); comp++) {
            if (label == connectedComponentsList[comp]->label)
                inList = true;
        }

        if (!inList)
        {
            connectedComponentsList.push_back(graph.vertices[i]);
        }
    }

    return connectedComponentsList;
}