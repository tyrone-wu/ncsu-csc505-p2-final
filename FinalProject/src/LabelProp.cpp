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
#include "omp.h"
#include "../include/GraphComponents.h"

using namespace std;

//This just grabs the node opposite of vertex v through Edge e in Graph g
Vertex* getOpposite(Vertex* v, Edge* e, Graph* graph){
    Vertex* r = graph->vertices[e->destination];
    if(r->id == v->id)
        return graph->vertices[e->source];
    return r;
}

/**
 * @brief Gets the connected components of the graph
 * 
 * @param graph the graph to compute the algorithm on
 * @return std::vector<Vertex*> the vertices to each connected component
 */
vector<Vertex*> getConnectedComponents(Graph* graph){
    //This marks the current set of connected components
    int c = 0;
    //This keeps track of the start vertex for each connected component
    vector<Vertex*> connectedComponentsList;

    //We keep track of if there was a change
    bool change;

    //We iterate through every vertex and set its label to match the majority of its neiighbors
    //until there are no updates
    do{
        change = false;
        for(int i = 0; i <= graph->vertices.size(); i++){
            Vertex* v = graph->vertices[i];
            std::map<std::string,int> counter;
            vector<Edge*> incidentEdges = v->incidentEdges;

            //Here we are seeing what all the neighbors are labled as
            for(int edge = 0; edge <= incidentEdges.size(); edge++){
                counter[getOpposite(v, incidentEdges[edge], graph)->label]++;
            }

            //Here we see what the which lable appears the most
            std::map<string,int>::iterator max = counter.begin();
            for (std::map<string,int>::iterator it=++(counter.begin()); it!=counter.end(); ++it){
                if(it->second > max->second)
                    max = it;
            }

            //We update the label if it does not match the majority of its neighbors
            if(v->label.compare(max->first) == 0){
                change = true;
                v->label=max->first;
            }
        }
    }while(change);

    //Now we collect the unique labels as those make up our connected components list
    connectedComponentsList.push_back(graph->vertices[0]);
    for(int i = 1; i <= graph->vertices.size(); i++){
        string label = graph->vertices[i]->label;
        bool inList = false;
        for(int comp = 0; comp < connectedComponentsList.size(); comp++){
            if(label.compare(connectedComponentsList[comp]->label) == 0)
                connectedComponentsList.push_back(graph->vertices[i]);
        }
    }

    return connectedComponentsList;
}