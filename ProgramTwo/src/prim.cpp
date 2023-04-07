/**
 * @file prim.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The Prim's MST implementation. 
 * 
 */

#include <vector>
#include "../include/MST.h"
#include "../include/Graph.h"
#include "../include/Edge.h"
#include "../include/Vertex.h"
#include "../include/PrimDHeapPQ.h"

/**
 * @brief Computes the Minimum Spanning Tree using Prim's algorithm
 * 
 * @param graph the graph to compute the MST on
 * @param k the node size to set; d = 2^k
 * @return std::vector<Edge*> the edges of the MST
 */
std::vector<Edge*> computeMST(Graph* graph, unsigned int k) {
    // Allocate memory for number of edges in the MST
    std::vector<Edge*> mst;
    mst.reserve(graph->vertices.size() - 1);

    // We pick a start vertex
    Vertex* startV = graph->vertices.at(0);
    // Look at the edges incident to the start vertex and put them in the min heap priority queue: Q
    PrimDHeapPQ Q = PrimDHeapPQ(graph->vertices, graph->vertices.size(), k);

    // While there are still edges in Q...
    while(Q.heapList.size() > 0){
        // Remove the minimum edge
        Vertex* miniumVertex = Q.removeMin();
        if(miniumVertex->edge != nullptr){
            mst.push_back(miniumVertex->edge);
        }

        // Find the incident edges to this new vertex
        std::vector<Edge*> newEdges = miniumVertex->incidentEdges;

        // For all of these incident edges...
        for(int i = 0; i < newEdges.size(); i++){
            // Find the end point of the edge that is not the recently marked vertex
            Vertex* newEdgeDest = graph->vertices.at(newEdges.at(i)->source);
            if(newEdgeDest->id == miniumVertex->id)
                newEdgeDest = graph->vertices.at(newEdges.at(i)->destination);

            // Increment compare here since comparing different fields
            compares++; 
            // If this new edge can't get to the node with less cost, update the distance.
            if (newEdges.at(i)->weight < newEdgeDest->distance){
                newEdgeDest->distance = newEdges.at(i)->weight;
                newEdgeDest->edge = newEdges.at(i);
                Q.decreaseKey(newEdgeDest->idHeap, newEdges.at(i)->weight);
            }
        }
    }

    return mst;
}