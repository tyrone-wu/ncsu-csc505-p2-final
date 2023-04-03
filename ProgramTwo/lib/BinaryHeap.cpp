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
    if(!isLeaf(i)){
        int mChild = lChild(i);
        //We need to check if there is a right child
        if(2*i + 1 <= heapList.size()-1){
            if(heapList[rChild(i)]->weight < heapList[mChild]->weight)
                mChild = rChild(i);
        }  
        if(heapList[mChild]->weight < heapList[i]->weight){
            Edge* temp = heapList[i];
            heapList[i] = heapList[mChild];
            heapList[mChild] = temp;

            heapify(mChild);
        }
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
Edge* BinaryHeap::removeMin(){
    buildHeap();
    Edge* r = heapList[1];
    Edge* newRoot = heapList.back();
    heapList.pop_back();
    heapList[1] = newRoot;
    heapify(1);
    return r;
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