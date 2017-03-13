#include"CImg.h"
#include"Maze.h"

#include<iostream>

using namespace cimg_library;

void showRelevantNodes(std::vector<Node>);

void printPathToImage(const cimg_library::CImg<unsigned char> &image, std::vector<Node> &path, const char * outputPath) 
{
	cimg_library::CImg<unsigned char> outputImage = image;
	for (int i = 0; i < path.size(); i++) 
	{
		std::cout << "Color at " << path.at(i).getX() << " " << path.at(i).getY() << std::endl;
		outputImage(path.at(i).getX(), path.at(i).getY(), 0, 0) = 255;  //Set Red component to 255
		outputImage(path.at(i).getX(), path.at(i).getY(), 0, 1)
			= outputImage(path.at(i).getX() , path.at(i).getY(), 0, 2)
			= 0; //Set Blue and Green component to 0
	}

	outputImage.save(outputPath);
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

	auto path = maze.getPath();

	//std::cout << "got path\n";

	//showRelevantNodes(path);

	printPathToImage(image, path, "tinySolution.bmp");

	return 0;
}

void showRelevantNodes(std::vector<Node> nodes)
{
	int i = 0;
	for (auto node = nodes.begin(); node != nodes.end(); node++, i++)
		std::cout << (*node).getX() << " " << (*node).getY() << " ENDPOINT:" << (*node).isEnd() << std::endl;
} 
