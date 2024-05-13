#include "HungarianAlgorithm.h"
namespace HungarianAlgorithm{
	resultInfo HungarianAlgorithm::Solve(Graph g)
	{
		return resultInfo();
	}
	resultInfo SolveWithoutWages(Graph g, Matching* matchingEdges)
	{
		if (matchingEdges == nullptr) {
			*matchingEdges = Matching(g.Size());
		}

		std::stack<int> S, T;
		while (EnlargePath(g, matchingEdges, S, T)) {
			if (matchingEdges->NumberOfMatching() >= g.Size()) {
				resultInfo ri;
				ri.findPerfect = true;
				ri.S = S;
				ri.T = T;
				ri.M = *matchingEdges;
				return ri;
			}
		}

		resultInfo ri;
		ri.findPerfect = false;
		ri.S = S;
		ri.T = T;
		ri.M = *matchingEdges;
		return ri;
	}
	bool EnlargePath(Graph g, Matching* matchingEdges, std::stack<int>& S, std::stack<int>& T)
	{
		S = std::stack<int>();
		T= std::stack<int>();
		bool *l_visited = new bool[g.Size()] {false};
		bool *containedInT = new bool[g.Size()] {false};
		tree D;

		for(int i = 0; i < g.Size(); i++)
			if (! matchingEdges->IsSaturated_l(i) ) {
				S.push(i);
				l_visited = false;
				break;
			}

		while (!S.empty())
		{
			int l;
			do {
				l = S.top();
				S.pop();
			} while (l_visited[l] && !S.empty());
			l_visited[l] = true;

			auto edges = g.Edges_L(l);
			for (auto edge : edges) {
				if (containedInT[edge->p])
					continue;

				int p = edge->p;
				T.push(p);
				containedInT[p] = true;
				D.Add(l, p);

				if (!matchingEdges->IsSaturated_p(p)) {
					D.Enlarge(*matchingEdges ,l, p);
					return true;
				}
				else {
					Edge e;
					if (!matchingEdges->Edge_p(p, e))
						throw "sta³o siê coœ dziwnego";
					S.push(e.l);
					l_visited[e.l] = false;
				}
			}

		}
		return false;
	}
	resultInfo& resultInfo::operator=(const resultInfo& a)
	{
		this->findPerfect = a.findPerfect;
		this->G_out = a.G_out;
		this->M = a.M;  
		this->findPerfect = a.findPerfect;
		this->S = a.S;
		this->T = a.T;
	}
}
