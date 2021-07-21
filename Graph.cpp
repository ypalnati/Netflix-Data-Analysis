#include "Graph.h"

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<int>[V];
}

void Graph::addEdge(int node1, int node2)
{
    adj[node1].push_back(node2);
    adj[node2].push_back(node1);
}
void Graph::printGraph(ofstream& outfile)
{
    for (int v = 0; v < V; ++v)
    {
        outfile << "\n Adjacency list of vertex "<< v << "\n head ";
        for (auto x : adj[v])
            outfile << "-> " << x;
        printf("\n");
    }
}
