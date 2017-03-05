#include"Node.h"

Node::Node(int x, int y, bool end)
{
	this->x = x;
	this->y = y;
	this->end = end;
	this->top = new Link;
	this->bottom = new Link;
	this->left = new Link;
	this->right = new Link;
}

int Node::getX() { return x; }
int Node::getY() { return y; }
bool Node::isEnd() { return end; }

void Node::setTop(Node * top, int cost)
{
	this->top->edge = top;
	this->top->cost = cost;
}

void Node::setBottom(Node * bottom, int cost)
{
	this->bottom->edge = bottom;
	this->bottom->cost = cost;
}

void Node::setLeft(Node * left, int cost)
{
	this->left->edge = left;
	this->left->cost = cost;
}

void Node::setRight(Node * right, int cost)
{
	this->right->edge = right;
	this->right->cost = cost;
}