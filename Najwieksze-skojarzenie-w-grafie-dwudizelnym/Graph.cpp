#include "Graph.h"
#include <iostream>

Graph::Graph(int size) : size{ size } {
	L = new std::vector<Edge*>[size];
	P = new std::vector<Edge*>[size];
	EdgeMatrixRef = new Edge**[size];
	for (int i = 0; i < size; i++) {
		EdgeMatrixRef[i] = new Edge * [size];
		for (int j = 0; j < size; j++) {
			EdgeMatrixRef[i][j] = nullptr;
		}
	}
}

void Graph::AddEdge(int l, int p, float wage)
{
	Edge* e = new Edge{l, p, wage};
	L[l].push_back(e);
	P[p].push_back(e);
	EdgeMatrixRef[l][p] = e;
	auto a = *EdgeMatrixRef[l][p];
}

const std::vector<Edge*> Graph::Edges_L(int l) const
{
	return L[l];
}

const std::vector<Edge*> Graph::Edges_P(int p) const
{
	return P[p];
}

bool Graph::ModyfiyEdge(int l, int p, float w)
{
	if (!HaveEdge(l, p)) 
		return false;
	EdgeMatrixRef[l][p]->wage = w;
	return true;
}

bool Graph::TakeEdge(int l, int p, Edge& Edge) const
{
	if (!HaveEdge(l, p))
		return false;
	Edge = *EdgeMatrixRef[l][p];
	return true;
}

bool Graph::HaveEdge(int l, int p) const
{
	return EdgeMatrixRef[l][p] != nullptr;
}

int Graph::Size() const
{
	return size;
}

Graph::Graph(const Graph& g)
{
	this->size = g.size;
	EdgeMatrixRef = new Edge * *[size];
	for (int i = 0; i < size; i++) {
		EdgeMatrixRef[i] = new Edge * [size];
		for (int j = 0; j < size; j++) {
			EdgeMatrixRef[i][j] = g.EdgeMatrixRef[i][j];
			if (EdgeMatrixRef[i][j] != nullptr) {
				L[i].push_back(EdgeMatrixRef[i][j]);
				P[i].push_back(EdgeMatrixRef[i][j]);

			}
		}
	}
}

Graph::~Graph()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (EdgeMatrixRef[i][j] != nullptr)
				delete EdgeMatrixRef[i][j];
		}
		delete EdgeMatrixRef[i];
	}
	delete EdgeMatrixRef;
}

std::ostream& operator<<(std::ostream& os, const Edge& e)
{
	os << "L"<<e.l << "--" << e.wage << "--" << "P"<<e.p;
	return os;
}

bool operator==(const Edge& a, const Edge& b)
{
	return a.l == b.l && a.p == b.p && a.wage == b.wage;
}

std::ostream& operator<<(std::ostream& os, const Graph& g)
{
	os << g.size;
	for (int i = 0; i < g.size; i++) {
		os << std::endl;
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
