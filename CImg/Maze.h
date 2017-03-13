#pragma once
#include<vector>
#include"Node.h"

class Maze
{
private:
	int ** maze, ** graph;
	int width, height;
	std::vector<Node> nodes;
	std::vector<int> heuristic;

public:
	Maze(int **, int, int);
	int ** getMaze();
	int ** getGraph();
	int getMazeWidth();
	int getMazeHeight();
	std::vector<Node> getNodes();

	std::vector<int> getHeuristic();
	std::vector<Node> getPath();
	void makeRelevantNodes();
	void makeConnections();
	void makeHeuristics();
	int isNode(int, int);
	Node getNodeWithXY(int, int);
};

