# Netflix-Data-Analysis
In this project we have created collection of general graph functions. Then, in the second part we have translated movie rating data from Netflix into graphs and analyzed the graphs with our implemented functions. We made a liberal use of the STL structures, like list, map, set, and vector.


In this project, we are implementing the functions in c++ language.
**Data structure for storing Graph:**
Graph.h file
Used adjacency list for implementation because it takes less space and comparatively with 
adjacency matrix there will be few less comparisons.
class Graph
{ 
 int V; //-> no of nodes(customers)
 vector <int>* adj; //used array of vectors
}; 
Graph.cpp
It contains the basic functions of graph like adding edges in graph, printing the graph. 
Graph_Operations.cpp
It contains the graph operations. 
void connectedComponents(ofstream& outfile); - Used DFS traversal and it passes through 
all the elements that are connected.
void one_cycle(ofstream& outfile); - While doing dfs if the node is visited previously ( 
or for the second time) we say it as found cycle and store this node as cyclestart and we 
will go back till to printcycle. 
vector<int> DijkstraSP(int& start, ofstream& outfile);- used dijkshtra algorithm with 
priority queues and calculated shortest path.
Graph_simulator.h && Graph_simulator.cpp
void generateConnectedGraph(int n, ofstream& outfile);
void generateEmptyGraph(int n, ofstream& outfile);
void generateHeap(int n, ofstream& outfile);
void generateTruncatedHeap(int n, int m, ofstream& outfile);
void generateEquivalenceModKGraph(int n, int k, ofstream& outfile);
void generateNcycleGraph(int n, ofstream& outfile);This file contains the 6 functions to generate the simulator graphs required to test the 
graph operations test cases. 
Used mathematical conditions to generate the graph.
Simulated_test.cpp
It has the main method to call the simulated graph functions:
For each type of graph, we called all the 3 operations, and the output is stored in 
SimulatesTestResults.txt included in zip file
  
**SUMMARY **
For simulated data: 
For n=100 it took 550ms and memory is 5kb
For n=1000 it took 2.58 mins and memory is 5010.5kb
For n=10000 it took 125 mins and memory is 2607341.18kb
Observed that heap is taking very less time 16 mins for n=10000 and other graphs are taking 0(n^2) 
time. All of them are n^2 loops adding edges with mathematical conditions.
For Netflix data : 
Each criteria took minimum of 240 mins and minimum memory of 5 mb for filtered data in memory.
Each criteria of ours takes o(n^3) time to process.


