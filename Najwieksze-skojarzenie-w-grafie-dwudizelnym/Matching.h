#pragma once
#include "Graph.h"
#include <iostream>

namespace HungarianAlgorithm {
	class Matching {
		int graphSize;
		int* l_p_matching; // po³¹czenia L - P
		int* p_l_matching; // po³¹czenia P - L
		float* wages;		// wagi po³¹czeñ z L - P
		float sumOfWages;
		int size = 0;
	public:

		explicit operator Graph() const {
			Graph result{ graphSize };
			for (int i = 0; i < graphSize; i++) {
				if (l_p_matching[i] >= 0)
					result.AddEdge(i, l_p_matching[i], wages[i]);
			}
			return result;
		}

		float SumOfWages() const {
			return sumOfWages;
		}

		int GraphSize() const {
			return graphSize;
		}

		int Size() const {
			return size;
		}

		Matching(int n) {
			graphSize = n;
			l_p_matching = new int[graphSize] {-1};
			p_l_matching = new int[graphSize] {-1};
			for (int i = 0; i < graphSize; i++) {
				l_p_matching[i] = p_l_matching[i] = -1;
			}

			wages = new float[graphSize] {0};
			sumOfWages = 0;
		}

		Matching& operator=(const Matching& m) {
			graphSize = m.graphSize;
			l_p_matching = new int[graphSize];
			p_l_matching = new int[graphSize];
			wages = new float[graphSize];
			for (int i = 0; i < graphSize; i++) {
				l_p_matching[i] = m.l_p_matching[i];
				p_l_matching[i] = m.p_l_matching[i];
				wages[i] = m.wages[i];
			}

			sumOfWages = m.sumOfWages;

			return *this;
		}

		~Matching() {
			delete[] l_p_matching;
			delete[] p_l_matching;
			delete[] wages;
		}

		bool IsSaturated_l(int l) {
			return l_p_matching[l] >= 0;
		}

		bool IsSaturated_p(int p) {
			return p_l_matching[p] >= 0;
		}

		void Add(Edge e) {
			if (l_p_matching[e.l] < 0)
				size++;

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
			size--;
			return true;
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
			for (int i = 0; i < m.graphSize; i++) {
				os << Edge(i, m.l_p_matching[i], m.wages[i]) << std::endl;
			}
			return os;
		}
	};

}