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
#include "omp.h"
#include "../include/Graph.h"
#include "../include/Vertex.h"
#include <iostream>

using namespace std;

//This just grabs the node opposite of vertex v through Edge e in Graph g
Vertex* getOpposite(Vertex* v, Edge* e, Graph* graph){
    Vertex* r = graph->vertices[e->destination];
    if(r->id == v->id)
        return graph->vertices[e->destination];
    return r;
}

/**
 * @brief Gets the connected components of the graph
 * 
 * @param graph the graph to compute the algorithm on
 * @return std::vector<Vertex*> the vertices to each connected component
 */
vector<Vertex*> BFS(Graph* graph){
    //This marks the current set of connected components
    int c = 0;
    //This keeps track of the start vertex for each connected component
    vector<Vertex*> connectedComponentsList;
    //We iterate through every vertex in the graph
    for(int i = 0; i <= graph->vertices.size(); i++){

        //If we find a vertex that is no accounted for in a connected componet set, we run BFS
        //and mark all the vertexes that we find
        if(graph->vertices[i]->mark == -1){

            //We define a frontier of nodes to explorer starting with the first node
            vector<Vertex*> frontier;
            graph->vertices[i]->mark = c;
            frontier.push_back(graph->vertices[i]);

            //We go through each node in the frontier and add its children to the next frontier
            while(frontier.size() > 0){
                vector<Vertex*> next_frontier{};

                //We now break into out parallel processes
                #pragma omp parallel
                {   

                    //Each thread gets its on frontier and ID
                    vector<Vertex*> local_frontier{};
                    int threadID = omp_get_thread_num();
                    int threadNUM = omp_get_num_threads();

                    //Each thread is responsible for looking at 1/threadNUM nodes
                    for(int f = threadID; f < frontier.size(); f+=threadNUM){

                        //We go through the incident edges of a frontier node when generating a new frontier
                        for(int incidentEdge = 0; incidentEdge <= frontier[f]->incidentEdges.size(); incidentEdge++){

                            //We grab the vertex opposite the one we had in the frontier
                            Vertex* vertexToAdd = getOpposite(frontier[f], frontier[f]->incidentEdges[incidentEdge], graph);


                            //If this new vertex has not been acounted for, do so and add it to the local frontier
                            if(vertexToAdd->mark == -1){
                                int insert;
                                //This is to ensure we don't accidently add the same node twice if two threads 
                                //happen to be looking at the same node at the same time.
                                #pragma omp atomic capture
                                {
                                    insert = vertexToAdd->mark;
                                    vertexToAdd->mark = c;
                                }if (insert > -1)
                                    local_frontier.push_back(vertexToAdd);
                            }
                        }
                    }

                    //Ensures that each thread takes turns with merging there discovered frontier together
                    #pragma omp critical
                    {
                        next_frontier.insert(next_frontier.end(), local_frontier.begin(), local_frontier.end());
                    }
                }
                //The frontier is replaced with a new frontier
                frontier=next_frontier;
            }
            //We at this point would have found all nodes connected to a given connected set and can increment
            //to start looking for any new connected sets.
            c++;
            connectedComponentsList.push_back(graph->vertices[i]);
        }
    }
    return connectedComponentsList;
}