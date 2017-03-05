#pragma once
#include<vector>
#include"Node.h"

class Maze
{
private:
	int ** maze, ** graph;
	int width, height;
	std::vector<Node> nodes;
	
public:
	Maze(int **, int, int);
	int ** getMaze();
	int ** getGraph();
	int getMazeWidth();
	int getMazeHeight();
	std::vector<Node> getNodes();

	void makeRelevantNodes();
	void makeConnections();
	int isNode(int, int);
	Node getNodeWithXY(int, int);
};

