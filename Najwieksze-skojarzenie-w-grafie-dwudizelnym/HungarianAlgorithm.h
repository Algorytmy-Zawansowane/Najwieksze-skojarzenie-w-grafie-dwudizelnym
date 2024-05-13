#pragma once
#include "Graph.h"
#include "stack"
namespace HungarianAlgorithm
{
	struct resultInfo {
		Graph G_out;
		Matching M; 
		bool findPerfect;
		std::stack<int> S;
		std::stack<int> T;

	public:
		resultInfo() :G_out{0}, M{ 0 } {
			findPerfect = false;
		}

		resultInfo& operator=(const resultInfo& a);
	};

	class Matching {
		int size;
		int* l_p_matching; // po³¹czenia L - P
		float* wages;		// wagi po³¹czeñ z L - P
		float sumOfWages;
		int numberOfMatching = 0;

		int* p_l_matching; // po³¹czanie P - L
	public:
		int Size() {
			return size;
		}

		int NumberOfMatching() {
			return numberOfMatching;
		}

		Matching(int n) {
			size = n;
			l_p_matching = new int[size] {-1};
			p_l_matching = new int[size] {-1};
			wages = new float[size] {0};
			sumOfWages = 0;
		}

		bool IsSaturated_l(int l) {
			return l_p_matching[l] >= 0;
		}

		bool IsSaturated_p(int p) {
			return l_p_matching[p] >= 0;
		}

		void Add(Edge e) {
			if (l_p_matching[e.l] < 0)
				numberOfMatching++;

			l_p_matching[e.l] = e.p;
			sumOfWages -= wages[e.l];
			sumOfWages += e.wage;
			wages[e.l] = e.wage;

			p_l_matching[e.p] = e.l;
		}

		bool Edge_l(int l, Edge& edge) {
			if (l_p_matching[l] < 0)
				return false;
			edge.l = l;
			edge.p = l_p_matching[l];
			edge.wage = wages[l];
		}

		bool Edge_p(int p, Edge& edge) {
			if (p_l_matching[p] < 0)
				return false;
			edge.l = p_l_matching[p];
			edge.p = p;
			edge.wage = wages[edge.l];
		}
	};

	class tree {
	public:
		void Add(int parent, int child) {

		}

		void Enlarge(Matching& m, int start, int end) {

		}
	};

	resultInfo Solve(Graph g);
	resultInfo SolveWithoutWages(Graph g, Matching* matchingEdges = nullptr);
	bool EnlargePath(Graph g, Matching* matchingEdges, std::stack<int>& S, std::stack<int>& T);
};

