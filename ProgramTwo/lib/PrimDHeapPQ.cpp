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
#include "../include/PrimDHeapPQ.h"
#include <limits>


/**
 * @brief Construct a new d-ary Heap object of the given list of edges.
 * 
 * @param edges the list of edges to create a d-ary heap from
 */
PrimDHeapPQ::PrimDHeapPQ(std::vector<Vertex*>& vertexes, unsigned int capacity, unsigned int k) {
    // Set k and d value for node size
    this->k = k;
    this->d = 1 << k;

    // Copy the list of initial edges into the heap
    this->heapList.reserve(capacity);
    this->heapList.assign(vertexes.begin(), vertexes.end());
}

/** 
 * @brief Finds the left-most child and returns its index
 * 
 * @param i The index of the parent's whose left-most child you're trying to find
 */
unsigned int PrimDHeapPQ::lChild(unsigned int i) {
    return (i << this->k) + 1;
}

/** 
 * @brief Finds the right-most child and returns its index
 * 
 * @param i The index of the parent's whose right-most child you're trying to find
 */
unsigned int PrimDHeapPQ::rChild(unsigned int i) {
    return (i << this->k) + this->d;
}

/** 
 * @brief Finds the parent of the current node
 * 
 * @param i The index of the of the current node
 */
unsigned int PrimDHeapPQ::parent(unsigned int i) {
    return (i - 1) >> this->k;
}

/** 
 * @brief Returns if the current node is a Leaf
 * 
 * @param i The index of the of the current node
 */
bool PrimDHeapPQ::isLeaf(unsigned int i) {
    return this->lChild(i) >= this->heapList.size();
}

/**
 * @brief Swaps a node with its smallest child and continues the operation with the child of the current node if the child is smaller than the parent.
 * 
 * @param i The index of the node you are trying to hepify
 */
void PrimDHeapPQ::heapify(unsigned int i) {
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

        if (this->heapList.at(j)->distance < this->heapList.at(min)->distance) {
            min = j;
        }
    }

    // Recursively swap until no swap is needed
    if (i != min) {
        // Swap the current node with the min child
        unsigned int idHeap = this->heapList[i]->idHeap;
        this->heapList[i]->idHeap = this->heapList[min]->idHeap;
        this->heapList[min]->idHeap = idHeap;
        std::swap(this->heapList[i], this->heapList[min]);
        heapify(min);
    }
}

/**
 * @brief Changes the distance value and reorders the heap
 * 
 * @param i The index of the node you arr trying yo change
 * @param dist The new distance value
 */
void PrimDHeapPQ::decreaseKey(unsigned int i, int dist){
   this->heapList[i]->distance = dist;
   
   // Percolate up edge until no more swap is made
    while (i != 0 && this->heapList.at(i) < this->heapList.at(parent(i))) {
        this->heapList[i]->idHeap = this->heapList[parent(i)]->idHeap;
        this->heapList[parent(i)]->idHeap = i;
        std::swap(this->heapList[i], this->heapList[parent(i)]);
        i = parent(i);
    }
}

/**
 * @brief Builds a min heap given the list of edges.
 * 
 */
void PrimDHeapPQ::buildHeap() {
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
Vertex* PrimDHeapPQ::removeMin() {
    // Swap root with the last item in the vector-based heap
    unsigned int idHeap = this->heapList[0]->idHeap;
    this->heapList[0]->idHeap = this->heapList[this->heapList.size() - 1]->idHeap;
    this->heapList[this->heapList.size() - 1]->idHeap = idHeap;

    std::swap(this->heapList[0], this->heapList[this->heapList.size() - 1]);

    // Extract the min edge
    Vertex* min = this->heapList[this->heapList.size() - 1];
    heapList.pop_back();

    // Re-heapify
    heapify(0);
    return min;
}

/**
 * @brief Prints out the heap
 */
void PrimDHeapPQ::printHeap(){
    for(int i = 0; i < heapList.size(); i++){
        std::cout << heapList.at(i)->distance << ", ";
    }
    std::cout << std::endl;
}