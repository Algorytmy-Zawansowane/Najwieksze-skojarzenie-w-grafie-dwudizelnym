#pragma once
#include <vector>
#include <ostream>

struct Edge {
	int l, p;
	float wage;
	Edge() {
		this->l = this->p = -1;
		this->wage = -1;
	}
	Edge(int l, int p, float wage) {
		this->l = l;
		this->p = p;
		this->wage = wage;
	}


	friend std::ostream& operator <<(std::ostream& os, const Edge& g);
	friend bool operator==(const Edge& a, const Edge& b);
	friend bool operator!=(const Edge& a, const Edge& b);
};

class Graph
{
	int size;
	std::vector<std::vector<std::shared_ptr<Edge>>> L, P, EdgeMatrixRef;
public:
	Graph(int size);
	Graph(const Graph& g);

	void AddEdge(int l, int p, float wage);
	const std::vector<std::shared_ptr<Edge>>& Edges_L(int l) const;
	const std::vector<std::shared_ptr<Edge>>& Edges_P(int p) const;
	bool ModyfiyEdge(int l, int p, float w);
	bool GetEdge(int l, int p, Edge& Edge) const;
	bool HasEdge(int l, int p) const;
	int Size() const;

	void InvertWages();

	friend std::ostream& operator <<(std::ostream& os, const Graph& g);
	friend bool operator ==(const Graph& a, const Graph& b);
};

