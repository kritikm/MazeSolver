#include"CImg.h"
#include"Maze.h"
#include<string>

#include<iostream>

void showRelevantNodes(std::vector<Node>);
cimg_library::CImg<unsigned char> getImageWithPath(const cimg_library::CImg<unsigned char> , std::vector<Node>);

cimg_library::CImg<unsigned char> image;

int main()
{
	std::string inputPath = "small.bmp";
	std::string outputPath = "test.bmp";

	image = cimg_library::CImg<unsigned char>(inputPath.c_str());

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

	cimg_library::CImg<unsigned char> output = getImageWithPath(image, path);

	output.save(outputPath.c_str());
	 
	return 0;
}

void showRelevantNodes(std::vector<Node> nodes)
{
	int i = 0;
	for (auto node = nodes.begin(); node != nodes.end(); node++, i++)
		std::cout << (*node).getX() << " " << (*node).getY() << " ENDPOINT:" << (*node).isEnd() << std::endl;
} 

cimg_library::CImg<unsigned char> getImageWithPath(const cimg_library::CImg<unsigned char> image, std::vector<Node> path)
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

	return outputImage;
}