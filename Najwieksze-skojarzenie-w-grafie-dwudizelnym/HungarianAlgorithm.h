#pragma once
#include "Graph.h"
#include "stack"
#include "Matching.h"
#include "Tree.h"
#include <optional>

namespace HungarianAlgorithm
{
	struct resultInfo {
		std::optional<Graph> G_out = std::nullopt;
		Matching M; 
		float sumOfWages;
		bool perfectFound;
		std::stack<int> S;
		std::stack<int> T;

	public:
		resultInfo(const resultInfo& a);
		resultInfo();
		void invertWages();

		//resultInfo& operator=(const resultInfo& a);
	};

	resultInfo Solve(const Graph& g);
	resultInfo SolveWithoutWages(const Graph& g, Matching& matchingEdges);
	bool EnlargePath(const Graph& g, Matching& matchingEdges, std::stack<int>& S, std::stack<int>& T);
};

