/**
 * @file BinaryHeap.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The binary heap data structure class.
 * 
 */

#include <iostream>
#include <vector>
#include "../include/BinaryHeap.h"

/**
 * @brief Construct a new Binary Heap object of the given list of edges.
 * 
 * @param edges the list of edges to create a binary heap from
 */
BinaryHeap::BinaryHeap(std::vector<Edge*>& edges) {
    // Copy the list of initial edges into the heap
    this->heapList.reserve(edges.size());
    this->heapList = edges;

    this->buildHeap();
}

/**
 * @brief Construct a new empty Binary Heap object with the capacity
 * 
 * @param capacity the capacity to set
 */
BinaryHeap::BinaryHeap(int capacity) {
    this->heapList.reserve(capacity);
}

/** 
 * @brief Finds the left child and returns its index
 * 
 * @param i The index of the parent's whose left child you're trying to find
*/
int BinaryHeap::lChild(int i) {
    return 2 * i + 1;
}

/** 
 * @brief Finds the right child and returns its index
 * 
 * @param i The index of the parent's whose right child you're trying to find
*/
int BinaryHeap::rChild(int i) {
    return 2 * i + 2;
}

/** 
 * @brief Finds the parent of the current node
 * 
 * @param i The index of the of the current node
*/
int BinaryHeap::parent(int i) {
    return (i - 1) / 2;
}

/** 
 * @brief Returns if the current node is a Leaf
 * 
 * @param i The index of the of the current node
*/
bool BinaryHeap::isLeaf(int i) {
    return i >= (heapList.size() / 2);
}

/**
 * @brief Swaps a node with its smallest child and continues the operation with the child of the current node if the child is smaller than the parent.
 * 
 * @param i The index of the node you are trying to hepify
 */
void BinaryHeap::heapify(int i) {
    // Base case return if i is leaf node
    if (isLeaf(i)) {
        return;
    }

    // Track min index to swap
    int min = i;

    // Set min to left if left is smaller
    int left = this->lChild(i);
    if ((left < this->heapList.size()) && (this->heapList.at(left)->weight < this->heapList.at(min)->weight)) {
        min = left;
    }

    // Set min to right if right is smaller
    int right = this->rChild(i);
    if ((right < this->heapList.size()) && (this->heapList.at(right)->weight < this->heapList.at(min)->weight)) {
        min = right;
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
void BinaryHeap::buildHeap() {
    // Min Heapify edges
    for (int i = this->heapList.size() / 2 - 1; i >= 0; i--) {
        this->heapify(i);
    }
}

/**
 * @brief Removes the root of the heap, sorts the list, and returns the Edge
 * 
 * @return The root of the heap
 */
Edge* BinaryHeap::removeMin() {
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
void BinaryHeap::addEdge(Edge* e) {
    // Append edge to back of the heap
    this->heapList.push_back(e);
    // Percolate edge until no more swap is made
    int idx = this->heapList.size() - 1;
    while (idx != 0 && this->heapList[idx]->weight < this->heapList[parent(idx)]->weight) {
        std::swap(this->heapList[idx], this->heapList[parent(idx)]);
        idx = parent(idx);
    }
}

/**
 * @brief Prints out the heap
 */
void BinaryHeap::printHeap(){
    for(int i = 0; i < heapList.size(); i++){
        std::cout << heapList.at(i)->weight << ", ";
    }
    std::cout << std::endl;
}