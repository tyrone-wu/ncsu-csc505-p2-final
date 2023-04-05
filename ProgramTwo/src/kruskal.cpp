/**
 * @file kruskal.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The Kruskal's MST implementation. 
 * 
 */

#include <vector>
#include "../include/MST.h"
#include "../include/Graph.h"
#include "../include/Edge.h"
#include "../include/Vertex.h"
#include "../include/DHeap.h"

struct DisjointSet
{
    int* parent;
    int* rank;
    Vertex* v;

    int n;

    DisjointSet(std::vector<Vertex*> vertices)
    {
        this->n = vertices.size();
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++)
        {
            rank[i] = 0;
            parent[i] = i;
            // v = vertices.at(i);
        }
    }

    int findParent(int child)
    {
        if (child != parent[child])
        {
            parent[child] = findParent(parent[child]);
        }

        return parent[child];
    }

    void mergeSets(int x, int y)
    {
        x = findParent(x);
        y = findParent(y);

        if (rank[x] > rank[y])
        {
            parent[y] = x;
        }
        else
        {
            parent[x] = y;
        }

        if (rank[x] == rank[y])
        {
            rank[y]++;
        }
    }
};

/**
 * @brief Computes the Minimum Spanning Tree using Kruskal's algorithm
 * 
 * @param graph the graph to compute the MST on
 * @param k the node size to set; d = 2^k
 * @return std::vector<Edge*> the edges of the MST
 */
std::vector<Edge*> computeMST(Graph* graph, unsigned int k) {
    // Allocate memory for number of edges in the MST
    std::vector<Edge*> mst;
    mst.reserve(graph->vertices.size() - 1);
    
    // Create a disjoint set for each vertex in the graph
    DisjointSet ds(graph->vertices);

    // Create a priority queue based on edge weight
    // Put all edges in the queue
    DHeap Q = DHeap(graph->edges, k);

    // Counter for the while loop
    int counter = 0;

    while(mst.size() < graph->vertices.size() - 1)
    {
        Edge* e = Q.removeMin();

        int u = ds.findParent(e->source);
        int v = ds.findParent(e->destination);

        if (u != v)
        {
            mst.push_back(e);
            ds.mergeSets(u, v);
        }
        counter++;
    }

    return mst;
}