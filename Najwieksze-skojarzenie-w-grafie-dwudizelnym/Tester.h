#pragma once
#include "Graph.h"
#include "iostream"
class Tester {
public:
	void Test() {
		Graph g{ 4 };
		g.AddEdge(0, 0, 10);
		g.AddEdge(0, 1, 10);
		std::cout << g;
		g.ModyfiyEdge(0, 0, 1);
		std::cout << g;
		FileController::Save(g, true, 10, "C:\\Users\\user\\source\\repos\\Algorytmy Zawansowane\\najwieksze-skojarzenie\\testy\\cos.txt");

		g.ModyfiyEdge(0, 0, 1);
		std::cout << g;
		Edge e;
		g.TakeEdge(0, 0, e);
		std::cout << e;

		std::cout << "test czytania\n";
		Graph graph_fromFile = FileController::ConvertInputFile("C:\\Users\\user\\source\\repos\\Algorytmy Zawansowane\\najwieksze-skojarzenie\\testy\\kupa.txt");
		std::cout << graph_fromFile;
	}
};