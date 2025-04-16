// Author: Minh Pham
// Date: 2025-15-04

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"

// Function that implements Dijkstra's algorithm to find the shortest path between two nodes in a graph.
int dijkstra(nodekey_t start, nodekey_t end, const Graph *g);

#endif
