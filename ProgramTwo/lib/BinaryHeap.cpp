/**
 * @file BinaryHeap.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The binary heap data structure class.
 * 
 */

#include <iostream>
using namespace std;
#include "../include/BinaryHeap.h"
#include <vector>

std::vector<Edge> heapList;

/**
 * @brief Construct an empty graph with the given capacities.
 * 
 * @param head The initial edge to be added to the binary heap
 */
BinaryHeap::BinaryHeap(Edge head) {\
    //The first 1 is a dummy value to make child, parent, and leaf calculations easier
    heapList.push_back(head);
    heapList.push_back(head);
}

/** 
 * @brief Finds the left child and returns its index
 * 
 * @param i The index of the parent's whose left child you're trying to find
*/
int BinaryHeap::lChild(int i) {
    return 2*i;
}

/** 
 * @brief Finds the right child and returns its index
 * 
 * @param i The index of the parent's whose right child you're trying to find
*/
int BinaryHeap::rChild(int i) {
    return 2*i + 1;
}

/** 
 * @brief Finds the parent of the current node
 * 
 * @param i The index of the of the current node
*/
int BinaryHeap::parent(int i) {
    return i/2;
}

/** 
 * @brief Returns if the current node is a Leaf
 * 
 * @param i The index of the of the current node
*/
bool BinaryHeap::isLeaf(int i){
    return (i*2 > (heapList.size()-1));
}

/**
 * @brief Swaps a node with its smallest child and continues the operation with the child of the current node if the child is smaller than the parent.
 * 
 * @param i The index of the node you are trying to hepify
 */
void BinaryHeap::heapify(int i){
    if(!isLeaf(i)){
        int mChild = lChild(i);
        //We need to check if there is a right child
        if(2*i + 1 <= heapList.size()-1){
            if(heapList[rChild(i)].weight < heapList[mChild].weight)
                mChild = rChild(i);
        }  
        if(heapList[mChild].weight < heapList[i].weight){
            Edge temp = heapList[i];
            heapList[i] = heapList[mChild];
            heapList[mChild] = temp;

            heapify(mChild);
        }
    }
}

/**
 * @brief Runs Heapify on all nodes in the heap from bottom to top, right to left
 */
void BinaryHeap::buildHeap(){
    for(int i = heapList.size(); i > 0; i--){
        heapify(i);
    }
}

/**
 * @brief Removes the root of the heap, sorts the list, and returns the Edge
 * 
 * @return The root of the heap
*/
Edge BinaryHeap::heapsort(){
    buildHeap();
    Edge r = heapList[1];
    Edge newRoot = heapList.back();
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
void BinaryHeap::addEdge(Edge e){
    heapList.push_back(e);
}

/**
 * @brief Prints out the heap
*/
void BinaryHeap::printHeap(){
    for(int i = 1; i < heapList.size(); i++){
        cout << heapList[i].weight << ", ";
    }
}