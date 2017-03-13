#include"CImg.h"
#include"Maze.h"


void printPathToImage(const cimg_library::CImg<unsigned char> &image, const std::vector<std::pair<int, int>> &path, const char * outputPath) {
	cimg_library::CImg<unsigned char> outputImage = image;
	for (int i = 0; i < path.size(); i++) {
		outputImage(path[i].first, path[i].second, 0, 0) = 255;  //Set Red component to 255
		outputImage(path[i].first, path[i].second, 0, 1)
			= outputImage(path[i].first, path[i].second, 0, 2) = 0; //Set Blue and Green component to 0
	}

	outputImage.save(outputPath);
}



