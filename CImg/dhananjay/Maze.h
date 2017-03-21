#pragma once

#include <vector>
#include <string>
#include "../CImg.h"
#include "Node.h"

class Maze {
public:
	Node *start, *end;
	cimg_library::CImg<unsigned char> image;
	std::vector<Node*> path;
	int rows, columns;
	int *list;

	Maze(std::string inputFile);
	~Maze();

	void initialize();
	void setupNodes();
	void findStartEnd();
	void printPathToImage(std::string outputFile);

private:
	void backtrackToGetPath();
	void paintRed(cimg_library::CImg<unsigned char> &image, int x, int y);


};
