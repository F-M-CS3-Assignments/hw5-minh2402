// Author: Minh Pham
// Date: 2025-15-04

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <climits>
#include <vector>

using namespace std;

// Defines nodekey_t as an unsigned long long int for node identification
#define nodekey_t unsigned long long int
#define INVALID_NODE_KEY ULLONG_MAX

// Structure representing a graph edge with its source node, destination node, and weight
struct GraphEdge {
    nodekey_t from;
    nodekey_t to;
    unsigned int weight;
};

class Graph{
    
    public:
        ~Graph(); // Destructor to clean up dynamically allocated memory

        void AddNode(nodekey_t key = 0); // Adds a new node to the graph if it does not already exist
        const GraphEdge* AddEdge(nodekey_t fromNodeKey, nodekey_t toNodeKey, unsigned int weight = 0); // Adds a new edge between two nodes, checking for duplicates

        bool IsPresent(nodekey_t key) const; // Checks if a given node exists in the graph

        string NodesToString() const; // Returns a string representation of all the nodes in the graph
        string EdgesToString() const; // Returns a string representation of all edges in the graph

        set<const GraphEdge*> GetOutwardEdgesFrom(nodekey_t nodeKey) const; // Retrieves all outward edges from a given node
        set<nodekey_t> GetNodes() const; // Retrieves all the nodes present in the graph

        size_t Size() const; // Returns the total number of edges in the graph
        size_t Order() const; // Returns the total number of nodes in the graph
    
    private:
        vector<nodekey_t> nodes; // Stores the nodes of the graph
        vector<vector <GraphEdge*>> adjList; // Adjacency list to store edges between nodes
};

#endif
