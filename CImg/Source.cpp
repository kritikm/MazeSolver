#include"CImg.h"
#include"Maze.h"
#include<string>

#include<iostream>

void showRelevantNodes(std::vector<Node>);
void printPathToImage(const cimg_library::CImg<unsigned char> &, std::vector<Node> &, const std::string);


int main()
{
	std::string inputPath = "tiny.bmp";
	std::string outputPath = "tinySol.bmp";
	cimg_library::CImg<unsigned char> image(inputPath.c_str());

	auto height = image.height();
	auto width = image.width();

	auto mat = new int*[width];

	for (int i = 0; i < width; i++)
	{
		mat[i] = new int[height];
		for (int j = 0; j < height; j++)
			mat[i][j] = image(j, i, 0, 0) / 255;
	}

	Maze maze(mat, width, height);

	maze.makeRelevantNodes();

	auto path = maze.getPath();

	printPathToImage(image, path, outputPath);
	 
	return 0;
}

void showRelevantNodes(std::vector<Node> nodes)
{
	int i = 0;
	for (auto node = nodes.begin(); node != nodes.end(); node++, i++)
		std::cout << (*node).getX() << " " << (*node).getY() << " ENDPOINT:" << (*node).isEnd() << std::endl;
} 

void printPathToImage(const cimg_library::CImg<unsigned char> &image, std::vector<Node> &path, const std::string outputPath)
{
	cimg_library::CImg<unsigned char> outputImage = image;
	for (int i = 0; i < path.size() - 1; i++)
	{
		int column = path.at(i).getX();
		int row = path.at(i).getY();

		if (path.at(i).getX() == path.at(i + 1).getX())
		{
			while (row != path.at(i + 1).getY())
			{
				outputImage(row, column, 0, 0) = 255;
				outputImage(row, column, 0, 1) = outputImage(row, column, 0, 2) = 0;
				if (row > path.at(i + 1).getY())
					row--;
				else
					row++;
			}
		}
		else
		{
			while (column != path.at(i + 1).getX())
			{
				outputImage(row, column, 0, 0) = 255;
				outputImage(row, column, 0, 1) = outputImage(row, column, 0, 2) = 0;
				if (column > path.at(i + 1).getX())
					column--;
				else
					column++;
			}
		}
		outputImage(row, column, 0, 0) = 255;
		outputImage(row, column, 0, 1) = outputImage(row, column, 0, 2) = 0;
	}
	outputImage.save(outputPath.c_str());
}