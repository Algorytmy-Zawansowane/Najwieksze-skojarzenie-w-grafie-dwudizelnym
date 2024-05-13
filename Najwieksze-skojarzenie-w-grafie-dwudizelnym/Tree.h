#pragma once
#include "Graph.h"
#include "Matching.h"
#include <iostream>

namespace HungarianAlgorithm {


	class Tree {
		int size;
		int* parents_l;
		int* parents_p;
	public:
		Tree(int size) {
			parents_l = new int[size] {-1};
			parents_p = new int[size] {-1};
			this->size = size;
		}

		void AddParrentToNodeFrom_P(int parent_l, int child_p) {
			parents_p[child_p] = parent_l;
		}

		void AddParrentToNodeFrom_L(int parent_p, int child_l) {
			parents_l[child_l] = parent_p;
		}

		void Enlarge(Matching* m, const Graph& g, int start, int end) {
			int current_p = end;
			int current_l = -1;
			Edge e;

			while (current_l != start)
			{
				g.TakeEdge(parents_p[current_p], current_p, e);
				m->Add(e);
				current_l = parents_p[current_p];
				if (current_l != start) {
					g.TakeEdge(current_l, parents_l[current_l], e);
					m->DelateEdge(e);
					current_p = parents_l[current_l];
				}
			}
		}
	};
}