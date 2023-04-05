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

class DHeap {
public:

    // k value to compute the node size d = 2^k
    unsigned int k;
    // Size of the node d = 2^k
    unsigned int d;

    // List to store the d-ary heap data
    std::vector<Edge*> heapList;

    /**
     * @brief Construct a new d-ary Heap object of the given list of edges.
     * 
     * @param edges the list of edges to create a d-ary heap from
     * @param k the k value to compute the node size d = 2^k
     */
    DHeap(std::vector<Edge*>& edges, unsigned int k);

    /**
     * @brief Construct a new empty d-ary Heap object with the capacity
     * 
     * @param capacity the capacity to set
     * @param k the k value to compute the node size d = 2^k
     */
    DHeap(int capacity, unsigned int k);

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
     * @brief Runs Heapify on all nodes in the heap from bottom to top, right to left
     */
    void buildHeap();

    /**
     * @brief Removes the root of the heap, sorts the list, and returns the Edge
     * 
     * @return The root of the heap
    */
    Edge* removeMin();
    
    /**
     * @brief Adds and Edge to the heap
     * 
     * @param e The edge to add
    */
    void addEdge(Edge* e);

    /**
     * @brief Prints out the heap
    */
    void printHeap();
};

#endif // DHEAP_H
