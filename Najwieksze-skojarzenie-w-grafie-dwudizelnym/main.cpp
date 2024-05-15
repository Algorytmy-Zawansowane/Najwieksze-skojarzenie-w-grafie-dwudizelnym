// Najwieksze-skojarzenie-w-grafie-dwudizelnym.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Graph.h"
#include "FileController.h"
#include "HungarianAlgorithm.h"
#include "Tester.h"

int main(int argc, char* argv[])
{
    Tester t;
    for (int i = 1; i < 4; i++) {
        try {
            t.TestFile(std::to_string(i) + ".txt");
        }
        catch (std::exception e) {
            // print to stderr
            std::cerr << e.what();
            return -1;
		}
	}

    std::cout << "Hello World!\n";
    std::cout << "here is your input:\n";
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i]<<std::endl;

        Graph g = FileController::ConvertInputFile(argv[i]);
        HungarianAlgorithm::resultInfo result = HungarianAlgorithm::Solve(g);
        FileController::Save(result.G_out.value(), result.perfectFound, result.M.SumOfWages(), std::string(argv[i]) + "out.txt");
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
