#pragma once
#include "Graph.h"
namespace HungarianAlgorithm
{
	struct resultInfo {
		Graph G_out;
		int* matchingEdges;
		double* wages;
		double sumOfWages;
		bool findPerfect;
	public:
		resultInfo() :G_out{0} {
			G_out = Graph(0);
			matchingEdges = nullptr;
			wages = nullptr;
			sumOfWages = 0;
			findPerfect = false;
		}
	};

	resultInfo Solve(Graph g);

};

