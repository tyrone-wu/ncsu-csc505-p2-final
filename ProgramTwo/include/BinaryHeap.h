/**
 * @file BinaryHeap.h
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief Classes that defines the binary heap data structure.
 * 
 */

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <vector>
#include "./Vertex.h"
#include "./Edge.h"

class BinaryHeap {
public:

    /**
     * @brief Construct an empty graph with the given capacities.
     * 
     * @param head The initial edge to be added to the binary heap
     */
    BinaryHeap(Edge head);

    /** 
     * @brief Finds the left child and returns its index
     * 
     * @param i The index of the parent's whose left child you're trying to find
    */
    int lChild(int i);

    /** 
     * @brief Finds the right child and returns its index
     * 
     * @param i The index of the parent's whose right child you're trying to find
    */
    int rChild(int i);

    /** 
     * @brief Finds the parent of the current node
     * 
     * @param i The index of the of the current node
    */
    int parent(int i);

    /** 
     * @brief Returns if the current node is a Leaf
     * 
     * @param i The index of the of the current node
    */
    bool isLeaf(int i);

    /**
     * @brief Swaps a node with its smallest child and continues the operation with the child of the current node if the child is smaller than the parent.
     * 
     * @param i The index of the node you are trying to hepify
     */
    void heapify(int i);

    /**
     * @brief Runs Heapify on all nodes in the heap from bottom to top, right to left
     */
    void buildHeap();

    /**
     * @brief Removes the root of the heap, sorts the list, and returns the Edge
     * 
     * @return The root of the heap
    */
    Edge heapsort();

    
    /**
     * @brief Adds and Edge to the heap
     * 
     * @param e The edge to add
    */
    void addEdge(Edge e);

    /**
     * @brief Prints out the heap
    */
    void printHeap();
};

#endif // BINARYHEAP_H
