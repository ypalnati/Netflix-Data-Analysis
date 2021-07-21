#include "Graph.h"


void Graph::DFSConnectedComponentsUtilCount(int v, bool visited[], ofstream& outfile, int* count)
{
    visited[v] = true;
    (*count)++;
    for (auto i : adj[v])
        if (!visited[i])
            DFSConnectedComponentsUtilCount(i, visited, outfile, count);
}

//prints the count of each connected components 
void Graph::connectedComponentsCount(ofstream& outfile)
{
    int count = 0;
    bool* visited = new bool[V];
    for (int v = 0; v < V; v++)
        visited[v] = false;

    for (int v = 0; v < V; v++) {
        if (visited[v] == false) {
            DFSConnectedComponentsUtilCount(v, visited, outfile, &count);
            outfile << count << "\n";
            count = 0;
        }
    }
    delete[] visited;
}

void Graph::DFSConnectedComponentsUtil(int v, bool visited[], ofstream& outfile)
{
    visited[v] = true;
    outfile << v << " ";
    for (auto i : adj[v])
        if (!visited[i])
            DFSConnectedComponentsUtil(i, visited, outfile);
}

//prints the connected componenets elements
void Graph::connectedComponents(ofstream& outfile)
{
    bool* visited = new bool[V];
    for (int v = 0; v < V; v++)
        visited[v] = false;

    for (int v = 0; v < V; v++) {
        if (visited[v] == false) {
            DFSConnectedComponentsUtil(v, visited, outfile);
            outfile << "\n";
        }
    }
    delete[] visited;
}

bool Graph::DFSCycleUtil(int v, int par, vector<bool>& visited, vector<int>& parent, int* cycle_start, int* cycle_end) { 
    visited[v] = true;
    for (int u : adj[v]) {
        if (u == par) continue;
        if (visited[u]) {
            *cycle_end = v;
            *cycle_start = u;
            return true;
        }
        parent[u] = v;
        if (DFSCycleUtil(u, parent[u], visited, parent, cycle_start, cycle_end))
            return true;
    }
    return false;
}

//prints one cycle elements if cycle is present else prints as Acyclic
void Graph::one_cycle(ofstream& outfile) {
    vector<bool> visited;
    vector<int> parent;
    int cycle_start, cycle_end;

    visited.assign(V, false);
    parent.assign(V, -1);
    cycle_start = -1;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && DFSCycleUtil(v, parent[v], visited, parent, &cycle_start, &cycle_end))
            break;
    }

    if (cycle_start == -1) {
        outfile << "Acyclic" << endl;
    }
    else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);


        outfile << "Cycle found: ";
        for (int v : cycle)
            outfile << v << " ";
        outfile << endl;
    }
}
void Graph::printDijkstraPathUtil(vector<int> parent, int j, ofstream& outfile)
{
    if (parent[j] == -1)
        return;
    printDijkstraPathUtil(parent, parent[j],outfile);
    outfile << "- " << j << " ";
}

void Graph::printDijkstraShortestPath(vector<int>& dist, int& start, vector<int> parent, ofstream& outfile)
{

    outfile << "\nPrinting the shortest paths for node " << start << ".\n";
    for (int i = 0; i < dist.size(); i++)
    {
        if (dist[i] == INF)
        {
            outfile << "There is no path from " << start << " to node " << i;
        }
        else
        {
            outfile << "The distance from node " << start << " to node " << i << " is: " << dist[i] << " and the path is " << start << " ";
            printDijkstraPathUtil(parent, i,outfile);
        }
        outfile << "\n";
    }

}
//find shortest path from start to all other nodes
vector<int> Graph::DijkstraSP(int& start, ofstream& outfile)
{
    outfile << "\nGetting the shortest path from " << start << " to all other nodes.\n";
    vector<int> dist;
    vector<int> parent;
    
    for (int i = 0; i < V; i++)
    {
        dist.push_back(INF);
        parent.push_back(-1);
    }

    priority_queue<pair<int, int>, vector< pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(start, 0));
    dist[start] = 0;
    while (pq.empty() == false)
    {
        int u = pq.top().first;
        pq.pop();
        for (auto d : adj[u])
        {if (dist[d] > dist[u] + 1)
            {
                parent[d] = u;
                dist[d] = dist[u] + 1;
                pq.push(make_pair(d, dist[d]));
            }
        }
    }
    printDijkstraShortestPath(dist, start, parent, outfile);
    return dist;
}