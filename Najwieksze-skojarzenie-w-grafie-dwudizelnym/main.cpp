#include <iostream>
#include "Graph.h"
#include "FileController.h"
#include "HungarianAlgorithm.h"
#include "Tester.h"

int main(int argc, char* argv[])
{
 //   Tester t;
 //   for (int i = 1; i <= 6; i++) {
 //       try {
 //           t.TestFile(std::to_string(i) + ".txt");
 //       }
 //       catch (std::exception e) {
 //           // print to stderr
 //           std::cerr << e.what();
 //           return -1;
	//	}
	//}

    for (int i = 1; i < argc; i++) {
        Graph g = FileController::ConvertInputFile(argv[i]);
        HungarianAlgorithm::resultInfo result = HungarianAlgorithm::Solve(g);
        std::string filePath = std::string(argv[i]);
        FileController::Save(result.G_out.value(), result.perfectFound, result.M.SumOfWages(), filePath.substr(0, filePath.find_last_of(".")) + "_out.txt");
    }
}