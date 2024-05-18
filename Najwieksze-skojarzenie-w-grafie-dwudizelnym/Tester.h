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
		g.GetEdge(0, 0, e);
		std::cout << e;

		std::cout << "test czytania\n";
		Graph graph_fromFile = FileController::ConvertInputFile("..\\testy\\test.txt");
		std::cout << graph_fromFile;
	}

	void TestFile(std::string fileName) {
		Graph graph_fromFile = FileController::ConvertInputFile("..\\testy\\InputTest\\" + fileName);
		auto ri = HungarianAlgorithm::Solve(graph_fromFile);
		Graph solution = (Graph)ri.M;

		std::cout << "\nStartowy graf\n" << graph_fromFile << "\n";
		
		std::cout << "\nZnalezione rozwiazanie\n" <<  solution << std::endl;
		std::cout << "\nZnaleziona suma wag\n" << ri.sumOfWages << std::endl;
		int* sumOfWages = new int;
		Graph trueSolution = FileController::ConvertInputFile("..\\testy\\Solutions\\" + fileName, true, sumOfWages);
		std::cout << "\nPrawdziwe rozwiazanie\n" << trueSolution << std::endl;
		std::cout << "\nPrawdziwa suma wag\n" << *sumOfWages << std::endl;
		std::cout << "Czy rozwiazanie jest wlasciwe: " << (solution == trueSolution && *sumOfWages == ri.sumOfWages) << std::endl;
		delete sumOfWages;

		if (!ri.perfectFound) {
			throw std::exception("Nie znaleziono rozwiazania");
		}
	}
};