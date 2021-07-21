#pragma once
#include "Graph.h"

void generateConnectedGraph(int n, ofstream& outfile);
void generateEmptyGraph(int n, ofstream& outfile);
void generateHeap(int n, ofstream& outfile);
void generateTruncatedHeap(int n, int m, ofstream& outfile);
void generateEquivalenceModKGraph(int n, int k, ofstream& outfile);
void generateNcycleGraph(int n, ofstream& outfile);

