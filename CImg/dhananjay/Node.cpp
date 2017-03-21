#include "Node.h"

Node::Node(unsigned int x, unsigned int y) {
	this->x = x;
	this->y = y;
	this->visited = false;
	top = bottom = left = right = previous = nullptr;
}