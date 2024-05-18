#include "Graph.h"
#include <iostream>

Graph::Graph(int size) : size{ size } {
	L = std::vector<std::vector<std::shared_ptr<Edge>>>(size, std::vector<std::shared_ptr<Edge>>());
	P = std::vector<std::vector<std::shared_ptr<Edge>>>(size, std::vector<std::shared_ptr<Edge>>());
	EdgeMatrixRef = std::vector<std::vector<std::shared_ptr<Edge>>>(size, std::vector<std::shared_ptr<Edge>>(size));
}

void Graph::AddEdge(int l, int p, float wage)
{
	auto e = std::make_shared<Edge>(l, p, wage);
	L[l].push_back(e);
	P[p].push_back(e);
	EdgeMatrixRef[l][p] = e;
}

const std::vector<std::shared_ptr<Edge>>& Graph::Edges_L(int l) const
{
	return L[l];
}

const std::vector<std::shared_ptr<Edge>>& Graph::Edges_P(int p) const
{
	return P[p];
}

bool Graph::ModyfiyEdge(int l, int p, float w)
{
	if (!HasEdge(l, p)) 
		return false;
	EdgeMatrixRef[l][p]->wage = w;
	return true;
}

bool Graph::GetEdge(int l, int p, Edge& Edge) const
{
	if (!HasEdge(l, p))
		return false;
	Edge = *EdgeMatrixRef[l][p];
	return true;
}

bool Graph::HasEdge(int l, int p) const
{
	return EdgeMatrixRef[l][p] != nullptr;
}

int Graph::Size() const
{
	return size;
}

void Graph::InvertWages()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (EdgeMatrixRef[i][j] != nullptr)
				EdgeMatrixRef[i][j]->wage = -EdgeMatrixRef[i][j]->wage;
		}
	}
}

Graph::Graph(const Graph& g)
{
	size = g.size;
	L = std::vector<std::vector<std::shared_ptr<Edge>>>(size, std::vector<std::shared_ptr<Edge>>());
	P = std::vector<std::vector<std::shared_ptr<Edge>>>(size, std::vector<std::shared_ptr<Edge>>());
	EdgeMatrixRef = std::vector<std::vector<std::shared_ptr<Edge>>>(size, std::vector<std::shared_ptr<Edge>>(size));
	for (int l = 0; l < size; l++) {
		for (auto& e : g.Edges_L(l)) {
			AddEdge(e->l, e->p, e->wage);
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Edge& e)
{
	os << "L" << e.l << "--" << e.wage << "--" << "P" << e.p;
	return os;
}

bool operator==(const Edge& a, const Edge& b)
{
	return a.l == b.l && a.p == b.p && a.wage == b.wage;
}

bool operator!=(const Edge& a, const Edge& b)
{
	return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Graph& g)
{
	for (int i = 0; i < g.size; i++) {
		if (i != 0) os << std::endl;
		for (int j = 0; j < g.size; j++) {
			if (g.EdgeMatrixRef[i][j] != nullptr)
			{
				auto a = *g.EdgeMatrixRef[i][j];
				os << g.EdgeMatrixRef[i][j]->wage << " ";
			}
			else
				os << "n" << " ";
		}
	}

	return os;
}

bool operator==(const Graph& a, const Graph& b)
{
	if (a.size != b.size)
		return false;

	const int size = a.size;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			if (a.EdgeMatrixRef[i][j] != nullptr && b.EdgeMatrixRef[i][j] != nullptr) {
				if (*a.EdgeMatrixRef[i][j] != *b.EdgeMatrixRef[i][j]) {
					return false;
				}
			}
			else if (a.EdgeMatrixRef[i][j] != nullptr || b.EdgeMatrixRef[i][j] != nullptr)
			{
				return false;
			}
		}
	}

	return true;
}
