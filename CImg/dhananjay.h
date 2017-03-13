#pragma once

#include"CImg.h"
#include <vector>

struct Node {
	Node* top;
	Node* bottom;
	Node* left;
	Node* right;
	Node* previous;

	int ctop, cbottom, cleft, cright;
	int x, y;
	bool visited;

};

typedef struct Node Node;


//setup.cpp
void setupNodes(const cimg_library::CImg<unsigned char> &image, std::vector<std::vector<Node*>> &nodes, Node* &start, Node* &end);




//dfs.cpp
std::vector<std::pair<int, int>> dfs(Node * start, Node* end);