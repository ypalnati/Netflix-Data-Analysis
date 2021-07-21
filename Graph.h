#pragma once
#include<iostream>
using namespace std;
#include<cstdlib>
#include <list>
#include <set>
#define INF 0x3f3f3f3f 
#include <vector> 
#include <queue>
#include <fstream>
class Graph
{
    int V;
    vector <int>* adj;
    void DFSConnectedComponentsUtil(int v, bool visited[], ofstream& outfile);
    bool DFSCycleUtil(int v, int par, vector<bool>& visited, vector<int>& parent, int* cycle_start, int* cycle_end);
    void printDijkstraPathUtil(vector<int> parent, int j, ofstream& outfile);
    void printDijkstraShortestPath(vector<int>& dist, int& start, vector<int> parent, ofstream& outfile);
    void DFSConnectedComponentsUtilCount(int v, bool visited[], ofstream& outfile, int* count);
public:
    Graph(int V);
    void addEdge(int v, int w);
    void printGraph(ofstream& outfile);
    void connectedComponents(ofstream& outfile);
    void find_cycle(ofstream& outfile);
    vector<int> DijkstraSP(int& start, ofstream& outfile);
    void connectedComponentsCount(ofstream& outfile)

};