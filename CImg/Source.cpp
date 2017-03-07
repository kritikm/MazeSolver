#include"CImg.h"
#include"Maze.h"

#include<iostream>

using namespace cimg_library;

void showRelevantNodes(std::vector<Node>);


void printMatrix(int ** mat,int width,int height) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			std::cout << mat[i][j];
		}
		std::cout << "\n";
	}
}

int main()
{
	CImg<unsigned char> image("tiny.bmp");

	auto height = image.height();
	auto width = image.width();

	auto mat = new int*[width];

	for (int i = 0; i < width; i++)
	{
		mat[i] = new int[height];
		for (int j = 0; j < height; j++)
			mat[i][j] = image(j, i, 0, 0) / 255;
	}

	//printMatrix(mat, width, height);

	Maze maze(mat, width, height);

	maze.makeRelevantNodes();

	int ** graph = maze.getGraph();
	int graphSize = maze.getNodes().size();

	for (int i = 0; i < graphSize; i++)
	{
		for (int j = 0; j < graphSize; j++)
			std::cout << graph[i][j] << " ";
		std::cout << std::endl;
	}
	//std::vector<Node> relevantNodes = maze.getNodes();

	return 0;
}

void showRelevantNodes(std::vector<Node> nodes)
{
	for (auto node = nodes.begin(); node != nodes.end(); node++)
		std::cout << (*node).getX() << " " << (*node).getY() << " ENDPOINT:" << (*node).isEnd() << std::endl;
} 
