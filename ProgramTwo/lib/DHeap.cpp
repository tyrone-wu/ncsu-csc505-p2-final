/**
 * @file DHeap.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The d-ary heap data structure class.
 * 
 */

#include <iostream>
#include <vector>
#include "../include/DHeap.h"

/**
 * @brief Construct a new d-ary Heap object of the given list of edges.
 * 
 * @param edges the list of edges to create a d-ary heap from
 */
DHeap::DHeap(std::vector<Edge*>& edges, unsigned int capacity, unsigned int k) {
    // Set k and d value for node size
    this->k = k;
    this->d = 1 << k;

    // Copy the list of initial edges into the heap
    this->heapList.reserve(capacity);
    this->heapList.assign(edges.begin(), edges.end());

    this->buildHeap();
}

/** 
 * @brief Finds the left-most child and returns its index
 * 
 * @param i The index of the parent's whose left-most child you're trying to find
 */
unsigned int DHeap::lChild(unsigned int i) {
    return (i << this->k) + 1;
}

/** 
 * @brief Finds the right-most child and returns its index
 * 
 * @param i The index of the parent's whose right-most child you're trying to find
 */
unsigned int DHeap::rChild(unsigned int i) {
    return (i << this->k) + this->d;
}

/** 
 * @brief Finds the parent of the current node
 * 
 * @param i The index of the of the current node
 */
unsigned int DHeap::parent(unsigned int i) {
    return (i - 1) >> this->k;
}

/** 
 * @brief Returns if the current node is a Leaf
 * 
 * @param i The index of the of the current node
 */
bool DHeap::isLeaf(unsigned int i) {
    return this->lChild(i) >= this->heapList.size();
}

/**
 * @brief Swaps a node with its smallest child and continues the operation with the child of the current node if the child is smaller than the parent.
 * 
 * @param i The index of the node you are trying to hepify
 */
void DHeap::heapify(unsigned int i) {
    // Base case return if i is leaf node
    if (isLeaf(i)) {
        return;
    }

    // Track min index to swap
    int min = i;

    // Iterate through the children of node i
    for (int j = this->lChild(i); j <= this->rChild(i); j++) {
        // Exit loop if no more children to iterate
        if (j >= this->heapList.size()) {
            break;
        }

        if (Edge::cmp(this->heapList.at(j), Operator::LESS, this->heapList.at(min))) {
            min = j;
        }
    }

    // Recursively swap until no swap is needed
    if (i != min) {
        // Swap the current node with the min child
        std::swap(this->heapList[i], this->heapList[min]);
        heapify(min);
    }
}

/**
 * @brief Builds a min heap given the list of edges.
 * 
 */
void DHeap::buildHeap() {
    // Min Heapify edges
    for (int i = (this->heapList.size() >> this->k); i >= 0; i--) {
        this->heapify(i);
    }
}

/**
 * @brief Removes the root of the heap, sorts the list, and returns the Edge
 * 
 * @return The root of the heap
 */
Edge* DHeap::removeMin() {
    // Swap root with the last item in the vector-based heap
    std::swap(this->heapList[0], this->heapList[this->heapList.size() - 1]);

    // Extract the min edge
    Edge* min = this->heapList[this->heapList.size() - 1];
    heapList.pop_back();

    // Re-heapify
    heapify(0);
    return min;
}

/**
 * @brief Adds and Edge to the heap
 * 
 * @param e The edge to add
 */
void DHeap::addEdge(Edge* e) {
    // Append edge to back of the heap
    this->heapList.push_back(e);

    // Percolate up edge until no more swap is made
    unsigned int idx = this->heapList.size() - 1;
    unsigned int parentIdx = this->parent(idx);
    while (idx != 0 && Edge::cmp(this->heapList.at(idx), Operator::LESS, this->heapList.at(parentIdx))) {
        std::swap(this->heapList[idx], this->heapList[parentIdx]);
        idx = parentIdx;
        parentIdx = this->parent(parentIdx);
    }
}

/**
 * @brief Prints out the heap
 */
void DHeap::printHeap(){
    for(int i = 0; i < heapList.size(); i++){
        std::cout << heapList.at(i)->weight << ", ";
    }
    std::cout << std::endl;
}