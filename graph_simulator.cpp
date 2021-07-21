#include "Graph.h"

void generateConnectedGraph(int n, ofstream& outfile)
{
	Graph g1(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			g1.addEdge(i, j);
		}
	}
	g1.printGraph(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n Following are connected components \n";
	g1.connectedComponents(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n finding cycle\n";
	g1.one_cycle(outfile);
	outfile << "\n --------------shortest path------------------------------ \n";

	int start = 1;
	g1.DijkstraSP(start, outfile);
}
void generateEmptyGraph(int n, ofstream& outfile)
{
	Graph g1(n);

	g1.printGraph(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n Following are connected components \n";
	g1.connectedComponents(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n finding cycle\n";
	g1.one_cycle(outfile);
	outfile << "\n --------------shortest path------------------------------ \n";

	int start = 1;
	g1.DijkstraSP(start, outfile);
}
void generateHeap(int n, ofstream& outfile)
{
	Graph g1(n);
	for (int i = 0; i < n; i++)
	{
		int x;
		x = (i - 1) / 2;
		if (x >= 0 && x < n)
			g1.addEdge(i, x);
		x = ((2 * n) + 1) / 2;
		if (x >= 0 && x < n)
			g1.addEdge(i, x);
		x = ((2 * n) - 1) / 2;
		if (x >= 0 && x < n)
			g1.addEdge(i, x);

	}
	g1.printGraph(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n Following are connected components \n";
	g1.connectedComponents(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n finding cycle\n";
	g1.one_cycle(outfile);
	outfile << "\n --------------shortest path------------------------------ \n";

	int start = 1;
	g1.DijkstraSP(start, outfile);
}
void generateTruncatedHeap(int n, int m, ofstream& outfile)
{
	Graph g1(n);
	for (int i = m; i < n; i++)
	{
		int x;
		x = (i - 1) / 2;
		if (x >= m && x < n)
			g1.addEdge(i,x);
			x = ((2 * n) + 1) / 2;
		if (x >= m && x < n)
			g1.addEdge(i,x);
		x = ((2 * n) - 1) / 2;
		if (x >= m && x < n)
			g1.addEdge(i,x);

	}
	g1.printGraph(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n Following are connected components \n";
	g1.connectedComponents(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n finding cycle\n";
	g1.one_cycle(outfile);
	outfile << "\n --------------shortest path------------------------------ \n";

	int start = 6;
	g1.DijkstraSP(start, outfile);
}

void generateEquivalenceModKGraph(int n, int k, ofstream& outfile)
{
	Graph g1(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if ((i - j) % k == 0)
				g1.addEdge(i, j);
		}

	}
	g1.printGraph(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n Following are connected components \n";
	g1.connectedComponents(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n finding cycle\n";
	g1.one_cycle(outfile);
	outfile << "\n --------------shortest path------------------------------ \n";

	int start = 6;
	g1.DijkstraSP(start, outfile);
}
void generateNcycleGraph(int n, ofstream& outfile)
{
	Graph g1(n);

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (abs(i - j) ==1 || abs(i - j) == n - 1)
			{
				g1.addEdge(i, j);
			}
		}
	}
	g1.printGraph(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n Following are connected components \n";
	g1.connectedComponents(outfile);
	outfile << "\n -------------------------------------------- \n";
	outfile << "\n finding cycle\n";
	g1.one_cycle(outfile);
	outfile << "\n --------------shortest path------------------------------ \n";

	int start = 1;
	g1.DijkstraSP(start, outfile);
}