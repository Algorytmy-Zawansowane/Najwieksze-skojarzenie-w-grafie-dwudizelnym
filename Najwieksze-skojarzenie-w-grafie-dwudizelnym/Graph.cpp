#include "Graph.h"
#include <iostream>

Graph::Graph(int size) {
	this->size = size;
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

const std::vector<Edge*> Graph::Edges_L(int l)
{
	return L[l];
}

const std::vector<Edge*> Graph::Edges_P(int p)
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

bool Graph::TakeEdge(int l, int p, Edge& Edge)
{
	if (!HaveEdge(l, p))
		return false;
	Edge = *EdgeMatrixRef[l][p];
	return true;
}

bool Graph::HaveEdge(int l, int p)
{
	return EdgeMatrixRef[l][p] != nullptr;
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
