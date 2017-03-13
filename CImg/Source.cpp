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

//int main(int * argCount, char * args[])
int main()
{
	//CImg<unsigned char> image(args[1]);

	CImg<unsigned char> image("tiny.png");

	auto height = image.height();
	auto width = image.width();

	auto mat = new int*[width];

	for (int i = 0; i < width; i++)
	{
		mat[i] = new int[height];
		for (int j = 0; j < height; j++)
			mat[i][j] = image(j, i, 0, 0) / 255;
	}

	std::cout << "got image\n";


	//printMatrix(mat, width, height);

	Maze maze(mat, width, height);

	maze.makeRelevantNodes();

	std::cout << "got relevant\n";

	auto graph = maze.getGraph();
	int graphSize = maze.getNodes().size();
	auto heur = maze.getHeuristic();


	for (int i = 0; i < graphSize; i++)
	{
		for (int j = 0; j < graphSize; j++)
			std::cout << graph[i][j] << " ";
		std::cout << std::endl;
	}
	for (auto it = heur.begin(); it != heur.end(); it++)
		std::cout << *it << std::endl;

	//std::vector<Node> relevantNodes = maze.getNodes();
	//showRelevantNodes(relevantNodes);

	//auto path = maze.getPath();

	//std::cout << "got path\n";

	//showRelevantNodes(path);

	return 0;
}

void showRelevantNodes(std::vector<Node> nodes)
{
	int i = 0;
	for (auto node = nodes.begin(); node != nodes.end(); node++, i++)
		std::cout << (*node).getX() << " " << (*node).getY() << " ENDPOINT:" << (*node).isEnd() << std::endl;
} 
