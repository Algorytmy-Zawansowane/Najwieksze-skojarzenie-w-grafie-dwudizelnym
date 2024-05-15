#include "HungarianAlgorithm.h"
namespace HungarianAlgorithm{
	resultInfo HungarianAlgorithm::Solve(const Graph& g)
	{
		return resultInfo();
	}

	resultInfo SolveWithoutWages(const Graph& g, Matching& matching)
	{
		if (matching.GraphSize() != g.Size()) {
			matching = Matching(g.Size());
		}

		std::stack<int> S, T;
		while (EnlargePath(g, matching, S, T)) {
			if (matching.Size() >= g.Size()) {
				resultInfo ri;
				ri.findPerfect = true;
				ri.S = S;
				ri.T = T;
				ri.M = matching;
				return ri;
			}
		}

		resultInfo ri;
		ri.findPerfect = false;
		ri.S = S;
		ri.T = T;
		ri.M = matching;
		return ri;
	}

	bool EnlargePath(const Graph& g, Matching& matchingEdges, std::stack<int>& S, std::stack<int>& T)
	{
		S = std::stack<int>();
		T = std::stack<int>();
		bool *l_visited = new bool[g.Size()] {false};
		bool *containedInT = new bool[g.Size()] {false};
		Tree D{ g.Size() };

		for(int i = 0; i < g.Size(); i++)
			if (! matchingEdges.IsSaturated_l(i) ) {
				S.push(i);
				break;
			}

		while (!S.empty())
		{
			int l = -1;
			do {
				l = S.top();
				S.pop();
			} while (l_visited[l] && !S.empty()); // szuka do momentu znalezienie nieodwiedzionego lub opró¿nienia
			
			if (l == -1)
				break;

			if(!l_visited[l])
				l_visited[l] = true;

			auto edges = g.Edges_L(l);
			for (auto edge : edges) {
				if (containedInT[edge->p])
					continue;

				int p = edge->p;
				T.push(p);
				containedInT[p] = true;
				D.AddParrentToNodeFrom_P(l, p);
				//std::cout << *matchingEdges << std::endl;

				if (!matchingEdges.IsSaturated_p(p)) {
					D.Enlarge(matchingEdges, g ,l, p);
					return true;
				}
				else {
					Edge e;
					if (!matchingEdges.Edge_p(p, e))
					{
						/*std::cout << "\n\n ERROR \n\n";
						std::cout << *matchingEdges << std::endl;
						std::cout << g << std::endl;*/
						throw "sta³o siê coœ dziwnego";
					}
					S.push(e.l);
					D.AddParrentToNodeFrom_L(p, e.l);
					l_visited[e.l] = false;
				}
			}
		}

		// dodaje z powrotem wierzcho³ki odwiedzionê do stacka 
		for (int i = 0; i < g.Size(); i++) {
			if (l_visited[i])
				S.push(i);
		}

		return false;
	}

	resultInfo::resultInfo(const resultInfo& a): G_out{ a.G_out }, M{ a.M }
	{
		this->findPerfect = a.findPerfect;
		this->findPerfect = a.findPerfect;
		this->S = a.S;
		this->T = a.T;
		this->sumOfWages = a.sumOfWages;
	}

	resultInfo::resultInfo() :G_out{ 0 }, M{ 0 } {
		findPerfect = false;
		sumOfWages = 0;
	}
}
