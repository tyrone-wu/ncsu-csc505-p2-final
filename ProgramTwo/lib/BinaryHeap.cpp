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
 * @brief Finds the left child and returns its index
 * 
 * @param i The index of the parent's whose left child you're trying to find
*/
unsigned int BinaryHeap::lChild(unsigned int i) {
    return 2 * i + 1;
}

/** 
 * @brief Finds the right child and returns its index
 * 
 * @param i The index of the parent's whose right child you're trying to find
*/
unsigned int BinaryHeap::rChild(unsigned int i) {
    return 2 * i + 2;
}

/** 
 * @brief Finds the parent of the current node
 * 
 * @param i The index of the of the current node
*/
unsigned int BinaryHeap::parent(unsigned int i) {
    return (i - 1) / 2;
}

/** 
 * @brief Returns if the current node is a Leaf
 * 
 * @param i The index of the of the current node
*/
bool BinaryHeap::isLeaf(unsigned int i) {
    return i >= (heapList.size() / 2);
}

/**
 * @brief Swaps a node with its smallest child and continues the operation with the child of the current node if the child is smaller than the parent.
 * 
 * @param i The index of the node you are trying to hepify
 * @param size the size of the heap to operate on
 */
void BinaryHeap::minHeapify(unsigned int i, unsigned int size) {
    // Track min index to swap
    unsigned int min = i;

    // Set min to left if left is smaller
    unsigned int left = this->lChild(i);
    if ((left < size) && this->heapList.at(left)->weight < this->heapList.at(min)->weight) {
        min = left;
    }

    // Set min to right if right is smaller
    unsigned int right = this->rChild(i);
    if ((right < size) && (this->heapList.at(right)->weight < this->heapList.at(min)->weight)) {
        min = right;
    }

    // Recursively swap until no swap is needed
    if (i != min) {
        // Swap the current node with the min child
        std::swap(this->heapList[i], this->heapList[min]);
        minHeapify(min, size);
    }
}

/**
 * @brief Swaps a node with its largest child and continues the operation with the child of the current node if the child is smaller than the parent.
 * 
 * @param i The index of the node you are trying to hepify
 * @param size the size of the heap to operate on
 */
void BinaryHeap::maxHeapify(unsigned int i, unsigned int size) {
    // Track min index to swap
    unsigned int max = i;

    // Set min to left if left is smaller
    unsigned int left = this->lChild(i);
    if ((left < size) && this->heapList.at(left)->weight > this->heapList.at(max)->weight) {
        max = left;
    }

    // Set min to right if right is smaller
    unsigned int right = this->rChild(i);
    if ((right < size) && (this->heapList.at(right)->weight > this->heapList.at(max)->weight)) {
        max = right;
    }

    // Recursively swap until no swap is needed
    if (i != max) {
        // Swap the current node with the min child
        std::swap(this->heapList[i], this->heapList[max]);
        minHeapify(max, size);
    }
}

/**
 * @brief Builds a min heap given the list of edges.
 * 
 */
void BinaryHeap::buildMinHeap() {
    // Min Heapify edges
    for (int i = this->heapList.size() / 2 - 1; i >= 0; i--) {
        this->minHeapify(i, this->heapList.size());
    }
}

/**
 * @brief Builds a max heap given the list of edges.
 * 
 */
void BinaryHeap::buildMaxHeap() {
    // Max Heapify edges
    for (int i = this->heapList.size() / 2 - 1; i >= 0; i--) {
        this->maxHeapify(i, this->heapList.size());
    }
}

/**
 * @brief Removes the root of the heap, sorts the list, and returns the Edge
 * 
*/
void BinaryHeap::heapsort() {
    // Build max heap so it results in ascending order
    this->buildMaxHeap();

    // Recursively call heapsort on the root after swapping with the last unsorted node
    for (int i = this->heapList.size() - 1; i > 0; i--) {
        // Swap last unsorted node with the root node
        std::swap(this->heapList[0], this->heapList[i]);
        this->maxHeapify(0, i);
    }

    // Reverse the list since min heap produces a descending ordered list; only needed if using a min heap
    // std::reverse(this->heapList.begin(), this->heapList.end());
}

/**
 * @brief Adds and Edge to the heap
 * 
 * @param e The edge to add
*/
void BinaryHeap::addEdge(Edge* e){
    heapList.push_back(e);
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