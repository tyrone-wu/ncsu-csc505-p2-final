/**
 * @file DHeap.h
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief Classes that defines the d-ary heap data structure.
 * 
 */

#ifndef DHEAP_H
#define DHEAP_H

#include <vector>
#include "./Edge.h"
#include "./Vertex.h"
#include <limits>

class PrimDHeapPQ {
public:

    // k value to compute the node size d = 2^k
    unsigned int k;
    // Size of the node d = 2^k
    unsigned int d;

    // List to store the d-ary heap data
    std::vector<Vertex*> heapList;

    /**
     * @brief Construct a new d-ary Heap object of the given list of edges.
     * 
     * @param vertexes the initial list of vertexes to populate the heap
     * @param capacity the capacity of the heap
     * @param k the k value to compute the node size d = 2^k
     */
    PrimDHeapPQ(std::vector<Vertex*>& vertexes, unsigned int capacity, unsigned int k);

    /** 
     * @brief Finds the left-most child and returns its index
     * 
     * @param i The index of the parent's whose left-most child you're trying to find
     */
    unsigned int lChild(unsigned int i);

    /** 
     * @brief Finds the right-most child and returns its index
     * 
     * @param i The index of the parent's whose right-most child you're trying to find
     */
    unsigned int rChild(unsigned int i);

    /** 
     * @brief Finds the parent of the current node
     * 
     * @param i The index of the of the current node
     * 
     */
    unsigned int parent(unsigned int i);

    /** 
     * @brief Returns if the current node is a Leaf
     * 
     * @param i The index of the of the current node
    */
    bool isLeaf(unsigned int i);

    /**
     * @brief Swaps a node with its smallest child and continues the operation with the child of the current node if the child is smaller than the parent.
     * 
     * @param i The index of the node you are trying to hepify
     */
    void heapify(unsigned int i);

    /**
     * @brief Changes the distance value and reorders the heap
     * 
     * @param i The index of the node you arr trying yo change
     * @param dist The new distance value
     */
    void decreaseKey(unsigned int i, int dist);

    /**
     * @brief Runs Heapify on all nodes in the heap from bottom to top, right to left
     */
    void buildHeap();

    /**
     * @brief Removes the root of the heap, sorts the list, and returns the Edge
     * 
     * @return The root of the heap
    */
    Vertex* removeMin();
    
    /**
     * @brief Adds and Edge to the heap
     * 
     * @param e The edge to add
    */
    void addNode(Vertex vertex);

    /**
     * @brief Prints out the heap
    */
    void printHeap();
};

#endif // DHEAP_H
