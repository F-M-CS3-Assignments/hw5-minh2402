// Author: Minh Pham
// Date: 2025-15-04

#include "Dijkstra.h"
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <map>
#include <set>

using namespace std;

int dijkstra(nodekey_t start, nodekey_t end, const Graph *g){
    int answer_final = -1;
    map<nodekey_t, int> distances; // Maps each node to its current shortest distance from the start node.
    set <nodekey_t> nodes = g->GetNodes(); // Get all nodes in the graph.
    BetterPriorityQueue bpq; // Priority queue to keep track of nodes to visit, ordered by shortest distance.
    
    BPQNode startNode;
    startNode.gnode = start;
    startNode.pri = 0;
    bpq.push(startNode); // Initialize priority queue with the start node.

    // Initialize distances for all nodes to infinity, except the start node which is set to 0.
    for (nodekey_t node : nodes){
        distances[node] = INT_MAX; // Set all values to a very large number.
    }
    distances[start] = 0; // Set the distance of the starting node to 0.

    while (!bpq.empty()){
        BPQNode curr_node = bpq.top(); // Retrieve the node with the smallest priority (shortest distance).
        bpq.pop(); // Remove the top node from the queue.

        // If the current node is the destination, we have found the shortest path to the end node.
        if (curr_node.gnode == end){ 
            answer_final = distances[end]; // The accumulated distance from start to end.
            break;
        }

        // Retrieve all outward edges from the current node.
        set<const GraphEdge*> neighbors = g->GetOutwardEdgesFrom(curr_node.gnode);
        for (const GraphEdge* edge : neighbors){ // Loop through all neighboring nodes (edges).
            nodekey_t neighbor = edge->to; // The neighboring node is the destination of the current edge.
            int dist = distances[curr_node.gnode] + edge->weight; // Calculate the tentative distance to the neighboring node.

            // If the calculated distance to the neighbor is smaller than the current known distance, update it.
            if (dist < distances[neighbor]){
                distances[neighbor] = dist;

                BPQNode next_node;
                next_node.gnode = neighbor; 
                next_node.pri = dist; // Set the priority (distance) for the neighbor node.

                // If the node is already in the priority queue, update its priority; otherwise, add it.
                if (bpq.Contains(next_node)){
                    bpq.Update(next_node); // Update the node in the priority queue with the new distance.
                }
                else{
                    bpq.push(next_node); // Add the neighbor to the priority queue if it's not already present.
                }
            }
        }
    }
    return answer_final; // Return the final shortest distance from start to end, or -1 if no path exists.
}

/*
 * Time complexity of Dijkstra's algorithm:
 * The time complexity is O(E log V), where:
 *   - E is the number of edges in the graph
 *   - V is the number of vertices in the graph
 *
 * For each node, we do a "pop" operation from the priority queue, which takes O(log V) time.
 * For each edge, we potentially "push" or "update" a node in the priority queue, which also takes O(log V) time.
 * Therefore, the total time complexity is O(E log V).
 */

