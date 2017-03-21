#pragma once
#include <limits>

class Node {
public:
	Node* top;
	Node* bottom;
	Node* left;
	Node* right;
	Node* previous;
	int  x, y, h, g;
	bool visited;
	int tcost, bcost, lcost, rcost;

	Node::Node(unsigned int x, unsigned int y) {
		this->x = x;
		this->y = y;
		this->visited = false;
		top = bottom = left = right = previous = nullptr;
		g = std::numeric_limits<int>::max();
	}
};