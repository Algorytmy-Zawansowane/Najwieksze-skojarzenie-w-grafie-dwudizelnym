#include <iostream>
#include "Graph.h"
#include "FileController.h"
#include "HungarianAlgorithm.h"
#include "Tester.h"

int main(int argc, char* argv[])
{
    Tester t;
    for (int i = 1; i <= 6; i++) {
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