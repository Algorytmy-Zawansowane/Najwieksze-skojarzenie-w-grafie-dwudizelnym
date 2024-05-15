#include "FileController.h"

namespace FileController
{
    Graph FileController::ConvertInputFile(std::string fileName, bool outputFile, int* sumOfWages)
    {
        std::ifstream file(fileName);

        if (!file.is_open()) {
            std::cerr << "Nie mo¿na otworzyæ pliku!" << std::endl;
            exit(1);
        }

        int n = ReadOne<int>(file);
        Graph g{ n };
        if (outputFile) {
            *sumOfWages = ReadOne<int>(file);
		}
        for (int i = 0; i < n; i++) {
            auto data = ReadLines<std::string>(1, file);
            int j = 0;
            for (std::string partOfData : data) {
                if (partOfData != "n") {
                    g.AddEdge(i, j, stof(partOfData));
                }
                j++;
            }
        }

        return g;
    }

    void FileController::Save(const Graph& graphToSave, bool hasBeenSolved, double sumOfWages, std::string fileName)
    {
        std::ofstream file;
        file.open(fileName);
        if (!hasBeenSolved)
            file << "nie znaleziono doskona³ego\n";
        file << sumOfWages << std::endl;
        file << graphToSave;

        file.close();
    }
}
