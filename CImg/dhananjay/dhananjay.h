#pragma once

#include"../CImg.h"
#include <vector>
#include <string>

struct Node {
	Node* top;
	Node* bottom;
	Node* left;
	Node* right;
	Node* previous;
	int heuristic;
	//int ctop, cbottom, cleft, cright;
	int  x, y;
	bool visited;
	Node(unsigned int x1, unsigned int y1 ) {
		x = x1;
		y = y1;
		visited = false;
		top = bottom = left = right = previous = nullptr;
	}
};

typedef struct Node Node;


//setup.cpp
void setupNodes(std::string inputFile, Node* &start, Node* &end);

std::vector<std::pair<int, int>> backtrack(Node* start);

void printPathToImage(std::string inputFile, const std::vector<std::pair<int, int>> &path, std::string outputFile);


//dfs.cpp
std::vector<std::pair<int, int>> dfs(Node * start, Node* end);

//dgbfs.cpp
std::vector<std::pair<int, int>> gbfs(Node * start, Node* end);
