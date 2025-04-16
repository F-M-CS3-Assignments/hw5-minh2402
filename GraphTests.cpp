// Author: Minh Pham
// Date: 2025-15-04

#include "Graph.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void TestAddNode(){
    cout << "Testing AddNode..." << endl;
    Graph g = Graph();

    g.AddNode(15);
    // Adds node 15 to the graph and verifies its presence by checking the node list.
    assert(g.NodesToString() == "[(15)]");

    g.AddNode(12);
    // Adds node 12 to the graph and verifies its presence by checking the node list.
    assert(g.NodesToString() == "[(15), (12)]");

    try
    {
        g.AddNode(12);
        // Attempts to add a duplicate node (12), which should throw an exception.
        assert(false);
    }
    catch( const invalid_argument& e ) { }

    cout << "PASSED!" << endl << endl;
}

void TestAddEdge(){
    cout << "Testing AddEdge..." << endl;
    Graph g = Graph();

    g.AddNode(15);
    g.AddNode(12);
    g.AddNode(9);
    // Verifying the nodes list after adding new nodes.
    assert(g.NodesToString() == "[(15), (12), (9)]");

    const GraphEdge *ge1 = g.AddEdge(15, 9, 2);
    // Adds an edge between node 15 and node 9 with weight 2, then checks the edge list.
    assert(g.NodesToString() == "[(15), (12), (9)]");
    assert(g.EdgesToString() == "[((15)->(9) w:2)]");
    assert(ge1->from == 15);
    assert(ge1->to == 9);
    assert(ge1->weight == 2);

    const GraphEdge *ge2 = g.AddEdge(9, 12); // Adds edge with default weight 0.
    assert(g.NodesToString() == "[(15), (12), (9)]");
    assert(g.EdgesToString() == "[((15)->(9) w:2), ((9)->(12) w:0)]");
    assert(ge2->from == 9);
    assert(ge2->to == 12);
    assert(ge2->weight == 0);

    try
    {
        const GraphEdge *ge3 = g.AddEdge(20, 12);
        // Attempts to add an edge with a non-existing node, which should throw an exception.
        assert(false);
    } catch (const invalid_argument& e) {}

    try
    {
        const GraphEdge *ge3 = g.AddEdge(15, 9, 7);
        // Attempts to add an edge that already exists (between 15 and 9), which should throw an exception.
        assert(false);
    } catch (const invalid_argument& e) {}

    cout << "PASSED!" << endl << endl;
}

void TestIsPresentSizeAndOrder() {
    cout << "Testing IsPresent, Size, and Order..." << endl;

    Graph g2 = Graph();
    assert(g2.Size() == 0);
    assert(g2.Order() == 0);
    assert(g2.IsPresent(17) == false);

    cout << "PASSED!" << endl << endl;
}

void TestGetOutwardEdgesFrom(){
    cout << "Testing GetOutwardEdgesFrom..." << endl;
    Graph g = Graph();
    g.AddNode(17);
    g.AddNode(18);
    g.AddNode(22);
    g.AddNode(34);

    const GraphEdge* ge1 = g.AddEdge(17, 18, 3);
    g.AddEdge(22, 18); // weight will be 0 of course
    const GraphEdge* ge3 = g.AddEdge(17, 34, 8);
    g.AddEdge(22, 17, 6); // note, 22 is not a neighbor of 17, but 17 is a neighbor of 22

    set<const GraphEdge*> soln;
    soln.insert(ge3);
    soln.insert(ge1);

    set<const GraphEdge*> result = g.GetOutwardEdgesFrom(17);
    // Verifying the outward edges from node 17.
    assert(result.size() == soln.size());
    assert(result == soln);

    cout << "PASSED!" << endl << endl;
}

void TestGetNodes(){
    cout << "Testing GetNodes..." << endl;

    Graph g = Graph();
    g.AddNode(51);
    g.AddNode(24);
    g.AddNode(73);

    set<nodekey_t> nodes = g.GetNodes();
    set<nodekey_t> soln = {24, 73, 51};
    assert(nodes.size() == soln.size());
    assert(nodes == soln);

    g = Graph();
    nodes = g.GetNodes();
    soln.clear();
    assert(nodes.size() == soln.size());
    assert(nodes == soln);

    cout << "PASSED!" << endl << endl;
}

void TestDestructor(){
    cout << "Testing Destructor..." << endl;
    Graph *g = new Graph();

    g->AddNode(3);
    g->AddNode(5);
    g->AddEdge(3, 5, 15);
    delete g;

    Graph *g2 = new Graph();
    g2->AddNode(12);
    g2->AddNode(11);
    delete g2;

    Graph *g3 = new Graph();
    delete g3;

    Graph g4 = Graph(); // Destructor is automatically called when this function ends.

    cout << "NO ERRORS.  Use valgrind to check!" << endl << endl;
}

int main(){

    TestAddNode();
    TestAddEdge();
    TestIsPresentSizeAndOrder();
    TestGetOutwardEdgesFrom();
    TestGetNodes();
    TestDestructor();

    cout << "ALL TESTS PASSED!" << endl;
    return 0;
}
