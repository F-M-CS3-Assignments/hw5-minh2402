// Author: Minh Pham
// Date: 2025-15-04

#include "Graph.h"
#include "BetterPriorityQueue.h"
#include "Dijkstra.h"

#include <iostream>
#include <cassert>

using namespace std;

int DijkstraTest(){
    cout << "Testing Dijkstra Algorithm..." << endl;

    Graph *g = new Graph();
    
    // Creating a graph with 6 nodes and adding edges between them
    g->AddNode(1);
    g->AddNode(2);
    g->AddNode(3);
    g->AddNode(4);
    g->AddNode(5);
    g->AddNode(6);
    
    g->AddEdge(1, 2, 7);
    g->AddEdge(2, 1, 7);
    g->AddEdge(1, 3, 9);
    g->AddEdge(3, 1, 9);
    g->AddEdge(1, 6, 14);
    g->AddEdge(6, 1, 14);
    
    g->AddEdge(2, 3, 10);
    g->AddEdge(3, 2, 10);
    g->AddEdge(2, 4, 15);
    g->AddEdge(4, 2, 15);
    
    g->AddEdge(3, 6, 2);
    g->AddEdge(6, 3, 2);
    g->AddEdge(3, 4, 11);
    g->AddEdge(4, 3, 11);
    
    g->AddEdge(6, 5, 9);
    g->AddEdge(5, 6, 9);
    
    g->AddEdge(4, 5, 6);
    g->AddEdge(5, 4, 6);
    
    cout <<  "---Graph---" << endl;
    cout << "\tnodes: " << g->NodesToString() << endl;
    cout << "\tedges: " << g->EdgesToString() << endl;
    cout << "---Graph---" << endl << endl;

    nodekey_t start = 1;
    nodekey_t end = 5;

    cout << "start: " << to_string(start) << "  goal: " << to_string(end) << endl;
    
    int ans = dijkstra(start, end, g);
    cout << "Output from Dijkstra(" << to_string(start) << ", " << to_string(end) << ") => " << ans << endl;
    assert(ans == 20);

    delete g;
    
    cout << "DONE Testing Dijkstra Algorithm" << endl;

    return ans;
}

void MoreDijkstraTests(){
    cout << "Deep Testing Dijkstra Algorithm..." << endl;
    // More in-depth tests can be added here for edge cases, larger graphs, etc.
    cout << "DONE Deep Testing Dijkstra Algorithm" << endl;
}

int main(){

    DijkstraTest(); // This tests the graph setup and the Dijkstra's algorithm implementation.
    MoreDijkstraTests();

    cout << "ALL TESTS PASSED!" << endl;

    return 0;
}
