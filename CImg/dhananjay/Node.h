#pragma once

class Node {
public:
	Node* top;
	Node* bottom;
	Node* left;
	Node* right;
	Node* previous;
	int  x, y, heuristic;
	bool visited;

	Node::Node(unsigned int x, unsigned int y) {
		this->x = x;
		this->y = y;
		this->visited = false;
		top = bottom = left = right = previous = nullptr;
	}
};