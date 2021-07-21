 #include "graph_simulator.h"

int main()
{
    bool* visited = new bool[14];
    for (int i = 0; i < 14; i++)
        visited[i] = false;
    int cycleVertices[14];
    for (int i = 0; i < 14; i++)
        cycleVertices[i] = -1;
    Graph g(14);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 6);
    g.addEdge(4, 7);
    g.addEdge(5, 6);
    g.addEdge(3, 5);
    g.addEdge(7, 8);
    g.addEdge(6, 10);
    g.addEdge(5, 9);
    g.addEdge(10, 11);
    g.addEdge(11, 12);
    g.addEdge(11, 13);
    g.addEdge(12, 13);

    std::ofstream outfile;
    outfile.open("D:\\SimulatedTestResults.txt", std::ios_base::app);
    int noOfVertices;
    cout << "enter the size of graph needed to test" << endl;
    scanf("%d", &noOfVertices);

    if (!outfile.is_open())
    {
        outfile << "\n ----------------------------error opening out put file---------------- \n";
    }
    g.printGraph(outfile);
    outfile << "\n -------------------------------------------- \n";
    outfile << "\n Following are connected components \n";
    g.connectedComponents(outfile);
    outfile << "\n -------------------------------------------- \n";
    outfile << "\n finding cycle\n";
    g.one_cycle(outfile);
    outfile << "\n --------------shortest path------------------------------ \n";

    int start = 1;
    g.DijkstraSP(start, outfile);

    outfile << "\n --------------testing simulator functions------------------------------ \n";
    outfile << "\n --------------testing with n cycle------------------------------ \n";
    generateNcycleGraph(noOfVertices, outfile);
    outfile << "\n --------------testing with connected graph------------------------------ \n";
    generateConnectedGraph(noOfVertices,outfile);
    outfile << "\n --------------testing with empty graph------------------------------ \n";
    generateEmptyGraph(noOfVertices, outfile);
    outfile << "\n --------------testing with heap ----------------------------- \n";
    generateHeap(11,outfile);

    outfile << "\n --------------testing with truncated heap ----------------------------- \n";
    generateTruncatedHeap(noOfVertices, 4,outfile);

    outfile << "\n --------------testing with EquivalenceModKGraph ----------------------------- \n";
    generateEquivalenceModKGraph(noOfVertices, 4, outfile);
    return 0;
}

