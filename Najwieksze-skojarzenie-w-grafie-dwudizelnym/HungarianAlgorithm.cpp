#include "HungarianAlgorithm.h"
namespace HungarianAlgorithm{
	resultInfo HungarianAlgorithm::Solve(const Graph& g)
	{
		int n = g.Size();
		Matching matching(n);
		resultInfo ri;
		ri = SolveWithoutWages(g, matching);
		if (!ri.perfectFound) {
			return ri;
		}

		Graph G(g);		// G = -g
		G.InvertWages();
		std::vector<float> I(2 * n, 0); // I(l), I(n+p)
		for (int l = 0; l < n; l++) {
			I[l] = (*std::max_element(G.Edges_L(l).begin(), G.Edges_L(l).end(), [](const std::shared_ptr<Edge> a, const std::shared_ptr<Edge> b) {return a->wage < b->wage;}))->wage;
		}
		Matching M(n);

		while (M.Size() < n) {
			Graph G_I(n);
			for (int l = 0; l < n; l++) {
				for (auto edge : G.Edges_L(l)) {
					int p = edge->p;
					if (edge->wage == I[l] + I[n + p]) {
						G_I.AddEdge(l, p, edge->wage);
					}
				}
			}
			auto ri = SolveWithoutWages(G_I, M);
			if (ri.perfectFound) {
				ri.G_out = std::make_optional<Graph>(n);
				// add all edges in M
				for (int l = 0; l < n; l++) {
					Edge e;
					if (M.Edge_l(l, e)) {
						ri.G_out->AddEdge(e.l, e.p, -e.wage);
					}
				}
				return ri;
			}
			else {
				float q = std::numeric_limits<float>::infinity();
				// construct the set P-T and convert S, T to vectors
				std::vector<bool> T_complement(n, true);
				std::vector<int> T, S;
				while (!ri.T.empty()) {
					T_complement[ri.T.top()] = false;
					T.push_back(ri.T.top());
					ri.T.pop();
				}
				while (!ri.S.empty()) {
					S.push_back(ri.S.top());
					ri.S.pop();
				}

				for (int l : S) {
					for (auto edge : G.Edges_L(l)) {
						int p = edge->p;
						if (T_complement[p]) {
							q = std::min(q, I[l] + I[n + p] - edge->wage);
						}
					}
				}

				for (int l : S) {
					I[l] -= q;
				}
				for (int p : T) {
					I[n + p] += q;
				}
			}
		}

		return ri;
	}

	resultInfo SolveWithoutWages(const Graph& g, Matching& matching)
	{
		if (matching.GraphSize() != g.Size()) {
			matching = Matching(g.Size());
		}

		std::stack<int> S, T;
		while (EnlargePath(g, matching, S, T)) {
			if (matching.Size() == g.Size()) {
				resultInfo ri;
				ri.perfectFound = true;
				ri.S = S;
				ri.T = T;
				ri.M = matching;
				return ri;
			}
		}

		resultInfo ri;
		ri.perfectFound = false;
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

	resultInfo::resultInfo(const resultInfo& a): M{ a.M }
	{
		this->perfectFound = a.perfectFound;
		this->perfectFound = a.perfectFound;
		this->S = a.S;
		this->T = a.T;
		this->sumOfWages = a.sumOfWages;
		if (a.G_out.has_value()) {
			this->G_out = std::make_optional<Graph>(*a.G_out);
		}
		else {
			this->G_out = std::nullopt;
		}
	}

	resultInfo::resultInfo() : M{ 0 } {
		perfectFound = false;
		sumOfWages = 0;
	}
}
