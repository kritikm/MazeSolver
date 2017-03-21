#include "Maze.h"
#include "Node.h"
#include<iostream>

using namespace std;

bool dfs(Maze &maze);
bool gbfs(Maze &maze);
bool astar(Maze &maze);


int main() {
	string inputFile = "images/perfect4k.bmp";
	string outputFile = "output.bmp";

	Maze m(inputFile);
	m.initialize();

	cout << "Start " << m.start->x << " " << m.start->y << "\n";
	cout << "End " << m.end->x << " " << m.end->y << "\n";


	bool pathFound;

	pathFound = astar(m);			// A-Star
	//pathFound = gbfs(m);			// Greedy Best First Search
	//pathFound = dfs(m);           // Depth First  Search

	if (pathFound) {
		m.printPathToImage(outputFile);
	}
	else {
		cout << "No Path \n";
	}


	return 0;
}
