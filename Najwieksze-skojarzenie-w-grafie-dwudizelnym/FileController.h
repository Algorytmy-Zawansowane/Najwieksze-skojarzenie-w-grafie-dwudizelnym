#pragma once
#include <string>
#include "Graph.h"
namespace FileController
{
	Graph ConvertInputFile(std::string fileName);
	void Save(Graph toSave, bool hasBeenSolved, double sumOfWages, std::string fileName);
};

