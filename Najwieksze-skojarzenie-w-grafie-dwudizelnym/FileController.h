#pragma once
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

namespace FileController
{
	Graph ConvertInputFile(std::string fileName, bool outputFile = false, int* sumOfWages = nullptr);
	void Save(const Graph& graphToSave, bool hasBeenSolved, double sumOfWages, std::string fileName);

    template<typename T>
    static T ReadOne(std::ifstream& file) {
        std::string line;  // Zmienna do przechowywania ka¿dej linii
        std::getline(file, line);
        std::istringstream iss(line);

        T number;
        iss >> number;

        if (!iss.eof() && iss.fail()) {
            std::cerr << "B³¹d podczas odczytu liczb z linii: " << line << std::endl;
        }

        return number;
    }


    template<typename T>
    static  std::vector<T> ReadLines(int n, std::ifstream& file) {
        std::vector<T> numbers;

        std::string line;
        for (int i = 0; i < n && std::getline(file, line); i++) {
            std::istringstream iss(line);
            T number;

            while (iss >> number) {
                numbers.push_back(number);
            }

            if (!iss.eof() && iss.fail()) {
                std::cerr << "B³¹d podczas odczytu liczb z linii: " << line << std::endl;
                continue;
            }
        }

        return numbers;
    }
};

