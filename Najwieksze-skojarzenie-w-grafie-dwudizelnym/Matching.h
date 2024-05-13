#pragma once
#include "Graph.h"
#include <iostream>

namespace HungarianAlgorithm {
	class Matching {
		int size;
		int* l_p_matching; // po³¹czenia L - P
		float* wages;		// wagi po³¹czeñ z L - P
		float sumOfWages;
		int numberOfMatching = 0;

		int* p_l_matching; // po³¹czanie P - L
	public:

		explicit operator Graph() const {
			Graph result{ size };
			for (int i = 0; i < size; i++) {
				if (l_p_matching[i] >= 0)
					result.AddEdge(i, l_p_matching[i], wages[i]);
			}
			return result;
		}

		float SumOfWages() {
			return sumOfWages;
		}

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
			for (int i = 0; i < size; i++) {
				l_p_matching[i] = p_l_matching[i] = -1;
			}

			wages = new float[size] {0};
			sumOfWages = 0;
		}

		bool IsSaturated_l(int l) {
			return l_p_matching[l] >= 0;
		}

		bool IsSaturated_p(int p) {
			return p_l_matching[p] >= 0;
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

		bool DelateEdge(Edge e) {
			if (l_p_matching[e.l] < 0 || p_l_matching[e.p] < 0)
				return false;

			l_p_matching[e.l] = -1;
			p_l_matching[e.p] = -1;
			sumOfWages -= wages[e.l];
			wages[e.l] = 0;
			numberOfMatching--;
		}

		bool Edge_l(int l, Edge& edge) {
			if (l_p_matching[l] < 0)
				return false;
			edge.l = l;
			edge.p = l_p_matching[l];
			edge.wage = wages[l];
			return true;
		}

		bool Edge_p(int p, Edge& edge) {
			if (p_l_matching[p] < 0)
				return false;
			edge.l = p_l_matching[p];
			edge.p = p;
			edge.wage = wages[edge.l];
			return true;
		}

		friend std::ostream& operator <<(std::ostream& os, const Matching& m) {
			for (int i = 0; i < m.size; i++) {
				os << Edge(i, m.l_p_matching[i], m.wages[i]) << std::endl;
			}
			return os;
		}
	};

}