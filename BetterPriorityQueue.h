// Author: Minh Pham
// Date: 2025-15-04

#ifndef BETTERPRIORITYQUEUE_h
#define BETTERPRIORITYQUEUE_h

#include <queue>
#include <vector>
#include <sstream>
#include "Graph.h"

using namespace std; 

// BPQNode structure represents a node in the priority queue, including its priority and reference to the associated graph node.
struct BPQNode {
    unsigned long long pri = ULLONG_MAX;
    bool visited = false;
    nodekey_t gnode = INVALID_NODE_KEY;
    BPQNode* previousNode = nullptr; // Will use this to refer to the last node
    int distance = ULLONG_MAX; // Representing infinity in this context

    bool operator<(const BPQNode &other) const {
        return pri < other.pri;
    }

    bool operator>(const BPQNode &other) const {
        return pri > other.pri;
    }

    bool operator==(const BPQNode &other) const {
        return this->gnode == other.gnode;
    }
};


class BetterPriorityQueue: public priority_queue<BPQNode, vector<BPQNode>, greater<BPQNode>> {

public: 
    bool Contains(BPQNode node); // This method checks if a specific BPQNode is contained in the queue, returning true if found and false otherwise.

    bool Update(BPQNode node); // This method allows for updating the priority of an existing BPQNode in the queue, maintaining the heap property if an update occurs.

    string ToString(); // Converts the entire queue to a string format, which includes the details of all BPQNodes.

    static string BPQNodeToString(BPQNode node); // A static method that converts a BPQNode to its string representation.

};

#endif
