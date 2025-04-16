// Author: Minh Pham
// Date: 2025-15-04

#include "BetterPriorityQueue.h"

// A minimum-priority queue will always have the item with the smallest priority at the front.
bool BetterPriorityQueue::Contains(BPQNode node){ 
    for(auto& n : this->c){
        if(node == n){ 
            return true; // This function checks whether a node already exists in the priority queue by comparing each node's identifier.
        }
    }
    return false; // returns false otherwise. 
}

bool BetterPriorityQueue::Update(BPQNode node){ 
    bool isInQueue = false; 

    for(auto& n : this->c){  // Iterates through all nodes in the queue and updates the priority of the node if the new priority is smaller than the previous one.
        if(n.gnode == node.gnode){ // Will only update the value if the node is in the queue and if its priority is lower than before. 
            if(node.pri < n.pri){ 
                n.pri = node.pri; 
                isInQueue = true; 
                make_heap(this->c.begin(), this->c.end(), this->comp); // Reorganizes the heap afterward to maintain the heap property.
            }                                                          
        }
    }
    return isInQueue; 
}

string BetterPriorityQueue::ToString(){ 
    ostringstream output; // Creates an output stream to store string values in

    output << "["; // Starts the bracket for formatting

    for(int i = 0; i < this->c.size(); i++){ 
        if(i == this->c.size() - 1){ // Don't add comma to the last one, and include closing bracket. 
            output << BPQNodeToString(this->c.at(i)) << ']';
        }else{
            output << BPQNodeToString(this->c.at(i)) << ", "; // Adds a comma after each item
        }
    }
    return output.str(); // Returns the string version of the output stream 
}


string BetterPriorityQueue::BPQNodeToString(const BPQNode node){ 
    ostringstream output; // Creates an output stream to store string values in 
    output << "(" << node.gnode << ", pri: " << node.pri << ")";
    return output.str(); 
}
