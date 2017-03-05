#pragma once
#include"Link.h"

class Node
{
	int x, y;
	bool end;
	Link * top, *bottom, *left, *right;

public:
	//Constructor
	Node(int, int, bool);
	int getX();
	int getY();
	bool isEnd();
	void setTop(Node *, int);
	void setBottom(Node *, int);
	void setLeft(Node *, int);
	void setRight(Node *, int);
};

