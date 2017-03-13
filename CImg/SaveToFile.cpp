#include"CImg.h"
#include"Maze.h"

#include<iostream>

using namespace cimg_library;

void printPathToImage(const CImg<unsigned char> &image, const std::vector<std::vector<bool>> &path) {
	CImg<unsigned char> outputImage = image;
	for (int i = 0; i < path.size(); i++) {
		for (int j = 0; j < path[i].size(); j++) {
			if (path[i][j]) {
				outputImage(j, i, 0, 0) = 255;  //Set Red component to 255
				outputImage(j, i, 0, 1) = outputImage(j, i, 0, 2) = 0; //Set Blue and Green component to 0
			}
		}
	}
	outputImage.save("test.bmp");
}


int test()
{
	CImg<unsigned char> image("normal.bmp");
	std::vector<std::vector<bool>> path = {
			{ false, true, true, false, false, false },
			{ false, true, true, false, false, false },
			{ false,true },
			{ false, true, true, true, true, true,true,true,true }
	};

	printPathToImage(image, path);


	return 0;
}


