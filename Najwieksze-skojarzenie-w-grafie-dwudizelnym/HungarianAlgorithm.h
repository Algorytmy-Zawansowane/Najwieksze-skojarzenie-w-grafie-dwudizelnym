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
	};

	resultInfo Solve(Graph g);
};

