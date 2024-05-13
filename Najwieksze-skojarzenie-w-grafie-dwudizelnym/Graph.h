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
};

class Graph
{
	int size;
	std::vector<Edge*> *L;
	std::vector<Edge*> *P;
	Edge ***EdgeMatrixRef;
public:
	Graph(int size);
	Graph(const Graph& g);

	void AddEdge(int l, int p, float wage);
	const std::vector<Edge*> Edges_L(int l) const;
	const std::vector<Edge*> Edges_P(int p) const;
	bool ModyfiyEdge(int l, int p, float w);
	bool TakeEdge(int l, int p, Edge& Edge) const;
	bool HaveEdge(int l, int p) const;
	int Size() const;

	friend std::ostream& operator <<(std::ostream& os, const Graph& g);
	friend bool operator ==(const Graph& a, const Graph& b);

	~Graph();
	// zwracanie listy krawêdzi
	// wierzcho³ki 
};

