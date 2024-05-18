#include "FileController.h"

namespace FileController
{
    Graph FileController::ConvertInputFile(std::string fileName, bool outputFile, float* sumOfWages)
    {
        std::ifstream file(fileName);

        if (!file.is_open()) {
            std::cerr << "Nie mo¿na otworzyæ pliku!" << std::endl;
            exit(1);
        }

        int n = ReadOne<int>(file);
        Graph g{ n };
        if (outputFile) {
            *sumOfWages = ReadOne<float>(file);
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

    void FileController::Save(std::optional<Graph> graphToSave, bool hasBeenSolved, float sumOfWages, std::string fileName)
    {
        std::ofstream file;
        file.open(fileName);
        if (!hasBeenSolved)
            file << "nie znaleziono doskona³ego\n";
        if (graphToSave.has_value()) {
            auto& g = graphToSave.value();
            file << g.Size() << std::endl;
            file << sumOfWages << std::endl;
            file << g;
		}

        file.close();
    }
}
