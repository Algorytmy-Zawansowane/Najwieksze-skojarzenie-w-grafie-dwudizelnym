#include <iostream>
#include "Graph.h"
#include <string>
#include <fstream>
#include <sstream>


// path, wierzcho�ki, min, max, ziarno = opcjonalnie
int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		std::cout << "Za ma�o danych";
		return -1;
	}

	std::string path = argv[1];
	int n = std::stoi(argv[2]);
	float min = std::stof(argv[3]);
	float max = std::stof(argv[4]);
	if (argc == 6) {
		srand(std::stoi(argv[5]));
	}
	else
	{
		srand(time(NULL));
	}

	if (min > max) {
		printf("min{%.3f} nie moze byc wieksze od max {%.3f}\n", min, max);
		return -1;
	}

	float range = max - min;
	Graph g{ n };

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (rand() % 2 == 0) {
				g.AddEdge(i, j, (rand() / (float)RAND_MAX) * range + min);
			}
		}
	}

	std::cout << "Wygenerowany graf:\n";
	std::cout << n << std::endl;
	std::cout << g << std::endl;

	std::ofstream file(path);
	file << n << std::endl;
	file << g;
	file.close();

	return 0;
}