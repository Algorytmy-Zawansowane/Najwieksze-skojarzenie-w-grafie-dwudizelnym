#pragma once
#include "Graph.h"
#include "iostream"
#include "filesystem"
#include "Matching.h"

class Tester {
public:
	void Test() {
		Graph g{ 4 };
		g.AddEdge(0, 0, 10);
		g.AddEdge(0, 1, 10);
		std::cout << g;
		g.ModyfiyEdge(0, 0, 1);
		std::cout << g;
		FileController::Save(g, true, 10, "..\\testy\\cos.txt");

		g.ModyfiyEdge(0, 0, 1);
		std::cout << g;
		Edge e;
		g.TakeEdge(0, 0, e);
		std::cout << e;

		std::cout << "test czytania\n";
		Graph graph_fromFile = FileController::ConvertInputFile("..\\testy\\kupa.txt");
		std::cout << graph_fromFile;
	}

	void TestFile(std::string fileName) {
		Graph graph_fromFile = FileController::ConvertInputFile("..\\testy\\InputTest\\" + fileName);
		HungarianAlgorithm::Matching m{ graph_fromFile.Size() };

		HungarianAlgorithm::SolveWithoutWages(graph_fromFile, m);
		Graph solution = (Graph)m;
		std::cout << "\nStartowy graf\n" << graph_fromFile << "\n";
		std::cout << "\nznalezione rozwiazanie\n" <<  solution << std::endl;
		Graph trueSolution = FileController::ConvertInputFile("..\\testy\\Solutions\\" + fileName);
		std::cout << "\nprawdziwe rozwiazanie\n" << trueSolution << std::endl;
		std::cout << "Czy rozwiazanie jest wlasciwe: " << (solution == trueSolution) << std::endl;
	}
};