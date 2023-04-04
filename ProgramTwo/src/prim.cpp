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
#include "../include/BinaryHeap.h"

/**
 * @brief Computes the Minimum Spanning Tree using Prim's algorithm
 * 
 * @param graph the graph to compute the MST on
 * @return std::vector<Edge*> the edges of the MST
 */
std::vector<Edge*> computeMST(Graph* graph) {
    // Allocate memory for number of edges in the MST

    std::vector<Edge*> mst;

    mst.reserve(graph->vertices.size() - 1);

    // We pick a start vertex
    Vertex* startV = graph->vertices.at(0);
    // Look at the edges incident to the start vertex and put them in the min heap priority queue: Q
    BinaryHeap Q = BinaryHeap(startV->incidentEdges);
    // Mark the start vertex as in the mst
    graph->vertices.at(0)->marked = true;
    // While there are still edges in Q...
    while(Q.heapList.size() > 0){
        // Remove the minimum edge
        Edge* minimumEdge = Q.removeMin();
        // Ensure that the edge points to a vertex not in the mst
        Vertex* minimumEdgeDest = nullptr;
        if(!graph->vertices.at(minimumEdge->source-1)->marked){
            minimumEdgeDest = graph->vertices.at(minimumEdge->source-1);
        } else if (!graph->vertices.at(minimumEdge->destination-1)->marked){
            minimumEdgeDest = graph->vertices.at(minimumEdge->destination-1);
        }
        // If the edge points to a vertex no in the mst...
        if(minimumEdgeDest != nullptr){
            // Add the edge to the mst
            mst.push_back(minimumEdge);
            // Mark the vertex as in the mst
            graph->vertices.at(minimumEdgeDest->id-1)->marked = true;
            // Find the incident edges to this new vertex
            std::vector<Edge*> newEdges = minimumEdgeDest->incidentEdges;
            // For all of these incident edges...
            for(int i = 0; i < newEdges.size(); i++){
                // Find the end point of the edge that is not the recently marked vertex
                Vertex* newEdgeDest = graph->vertices.at(newEdges.at(i)->source-1);
                if(newEdgeDest->id == minimumEdgeDest->id)
                    newEdgeDest = graph->vertices.at(newEdges.at(i)->destination-1);
                // If this vertex is not marked, add the edge to Q
                if (!newEdgeDest->marked)
                    Q.addEdge(newEdges.at(i));
            }
        }
    }

    return mst;
}