// Author: Minh Pham
// Date: 2025-15-04

#include "Graph.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// This function searches for an existing edge between two nodes in the adjacency list.
// If an edge is found, it is returned; otherwise, it returns nullptr.
const GraphEdge* findExistingEdge(nodekey_t gnFrom, nodekey_t gnTo, vector<vector<GraphEdge *>> adjList)
{
    if(adjList.size() == 0)
    {
        return nullptr;
    }

    for(size_t rowIDX = 0; rowIDX < adjList.size(); rowIDX++)
    {
        vector<GraphEdge*> row = adjList.at(rowIDX);
        for(size_t i = 0; i < row.size(); i++)
        {
            GraphEdge *cur = row.at(i);

            // It might make sense for there to be an == operator overload in the GraphEdge struct
            // but adding methods to a struct feels so _wrong_ to me!
            if(cur->from == gnFrom && cur->to == gnTo)
            {
                return cur;
            }
        }
    } 

    return nullptr;
}

// Returns a string representation of a graph edge, detailing the source, destination, and weight.
string GraphEdgeToString(const GraphEdge* e)
{
    return "((" + to_string(e->from) + ")->(" + to_string(e->to) + ") w:" + to_string(e->weight) + ")";
}

void Graph::AddNode(nodekey_t key)
{
    if(this->IsPresent(key))
    {
        throw invalid_argument("Duplicate node cannot be added: " + to_string(key));
    }

    nodes.push_back(key);
    vector <GraphEdge*> *newRow = new vector<GraphEdge*>;
    adjList.push_back(*newRow);
    delete newRow; // ?
}

// Adds a new edge from the source to the destination node and ensures that no duplicate edge exists.
const GraphEdge *Graph::AddEdge(nodekey_t gnFrom, nodekey_t gnTo, unsigned int w)
{
    const GraphEdge* dup = findExistingEdge(gnFrom, gnTo, this->adjList);
    if(dup != nullptr)
    {
        throw invalid_argument("Duplicate edge cannot be added: " + GraphEdgeToString(dup));
    }

    if(!this->IsPresent(gnFrom))
    {
        throw invalid_argument("No such node: " + to_string(gnFrom));
    }

    if(!this->IsPresent(gnTo))
    {
        throw invalid_argument("No such node: " + to_string(gnTo));
    }

    GraphEdge *ge = new GraphEdge;
    ge->from = gnFrom;
    ge->to = gnTo;
    ge->weight = w;

    for(size_t i = 0; i < this->nodes.size(); i++)
    {
        if(this->nodes.at(i) == gnFrom)
        {
            adjList.at(i).push_back(ge);
        }
    }

    const GraphEdge *response = ge; // This helps the compiler go
    return response;
}

bool Graph::IsPresent(nodekey_t key) const
{
    // Iterate through this->nodes and look for one that matches the key
    for(long long unsigned int  i = 0; i < this->nodes.size(); i++)
    {
        if(this->nodes.at(i) == key)
        {
            return true;
        }
    }
    return false;
}

set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t node) const 
{
    size_t idx = 0;
    while(idx < this->nodes.size() && (this->nodes.at(idx) != node))
    {
        idx++;
    }
    if(idx == this->nodes.size())
    {
        throw invalid_argument("No such node: " + to_string(node));
    }

    set<const GraphEdge*> result = set<const GraphEdge*>();
    // Iterate over this->adjList.at(idx); and find edges going out from the given node.
    for(long long unsigned int i = 0; i < this->adjList.at(idx).size(); i++)
    {
        if(this->adjList.at(idx).at(i)->from == node)
        {
            result.insert(this->adjList.at(idx).at(i));
        }
    }

    return result;
}

set<nodekey_t> Graph::GetNodes() const 
{
    set<nodekey_t> outcome;
    for(long long unsigned int i = 0; i < this->nodes.size(); i++)
    {
        outcome.insert(this->nodes.at(i));
    }
    return outcome;
}

size_t Graph::Order() const 
{
    return nodes.size();
}

size_t Graph::Size() const 
{
    size_t total = 0;
    for(size_t i = 0; i < adjList.size(); i++)
    {
        vector<GraphEdge*> row = adjList.at(i);
        for(size_t j = 0; j < row.size(); j++)
        {
            total++;
        }
    }

    return total;
}

string Graph::NodesToString() const 
{
    if(nodes.size() == 0)
    {
        return "[]";
    }

    string str = "[";
    for(size_t i = 0; i < (nodes.size() - 1); i++)
    {
        str = str + "(" + to_string(nodes.at(i)) + "), ";
    }

    str = str + "(" + to_string(nodes.at(nodes.size()-1)) + ")]";
    return str;
}

string Graph::EdgesToString() const 
{
    if(this->adjList.size() == 0)
    {
        return "[]";
    }

    size_t count = 0;
    string str = "[";
    for(size_t rowIDX = 0; rowIDX < this->adjList.size(); rowIDX++)
    {
        vector<GraphEdge*> row = this->adjList.at(rowIDX);
        for(size_t i = 0; i < row.size(); i++)
        {
            GraphEdge *cur = row.at(i);
            str = str + GraphEdgeToString(cur);

            if(count < (this->Size() - 1))
            {
                 str = str + ", ";
            }
            count++;
        }
    } 

    str = str +  "]";
    return str;
}

Graph::~Graph() {
    // Right now the memory leaks are bad, I need to implement something here to fix it
    
    for(size_t rowIDX = 0; rowIDX < adjList.size(); rowIDX++)
    {
        vector<GraphEdge*> row = adjList.at(rowIDX);
        for(size_t i = 0; i < row.size(); i++)
        {
            delete row.at(i);
        }
    }
}
