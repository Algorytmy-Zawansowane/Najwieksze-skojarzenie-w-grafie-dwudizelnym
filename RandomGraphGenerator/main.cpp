#include <iostream>
#include "Graph.h"
#include <string>
#include <fstream>
#include <sstream>


// path, wierzcho³ki, min, max, density = 0.5,  ziarno = opcjonalnie
int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		std::cout << "Za ma³o danych";
		return -1;
	}

	std::string path = argv[1];
	int n = std::stoi(argv[2]);
	float min = std::stof(argv[3]);
	float max = std::stof(argv[4]);
	float density = 0.5f;
	if (argc >= 6)
	{
		density = std::stof(argv[5]);
	}

	if (argc >= 7) {
		srand(std::stoi(argv[6]));
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
			if (rand() / (float)RAND_MAX <= density) {
				g.AddEdge(i, j, (rand() / (float)RAND_MAX) * range + min);
			}
		}
	}

	std::ofstream file(path);
	file << n << std::endl;
	file << g;
	file.close();

	return 0;
}