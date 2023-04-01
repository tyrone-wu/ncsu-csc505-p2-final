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
#include "./Edge.h"

class BinaryHeap {
public:

    // List to store the binary heap data
    std::vector<Edge*> heapList;

    /**
     * @brief Construct a new Binary Heap object of the given list of edges.
     * 
     * @param edges the list of edges to create a binary heap from
     */
    BinaryHeap(std::vector<Edge*>& edges) {
        // Copy the list of initial edges into the heap
        this->heapList.reserve(edges.size());
        this->heapList = edges;

        this->buildMinHeap();
    }

    /** 
     * @brief Finds the left child and returns its index
     * 
     * @param i The index of the parent's whose left child you're trying to find
    */
    unsigned int lChild(unsigned int i);

    /** 
     * @brief Finds the right child and returns its index
     * 
     * @param i The index of the parent's whose right child you're trying to find
    */
    unsigned int rChild(unsigned int i);

    /** 
     * @brief Finds the parent of the current node
     * 
     * @param i The index of the of the current node
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
     * @param size the size of the heap to operate on
     */
    void minHeapify(unsigned int i, unsigned int size);

    /**
     * @brief Swaps a node with its largest child and continues the operation with the child of the current node if the child is smaller than the parent.
     * 
     * @param i The index of the node you are trying to hepify
     * @param size the size of the heap to operate on
     */
    void maxHeapify(unsigned int i, unsigned int size);

    /**
     * @brief Builds a min heap given the list of edges.
     * 
     * @param edges the list of edges to convert
     */
    void buildMinHeap();

    /**
     * @brief Builds a max heap given the list of edges.
     * 
     * @param edges the list of edges to convert
     */
    void buildMaxHeap();

    /**
     * @brief Removes the root of the heap, sorts the list, and returns the Edge
     * 
     * @return The root of the heap
    */
    void heapsort();

    
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

#endif // BINARYHEAP_H
