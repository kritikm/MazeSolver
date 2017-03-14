#include"CImg.h"
#include <vector>
#include<algorithm>
#include <unordered_map>
#include <iostream>
#include "dhananjay.h"

using namespace cimg_library;
using namespace std;

int main() {
	CImg<unsigned char> image("images/tiny.bmp");
	Node *start, *end;
	setupNodes(image, start, end);
	cout << "Start " << start->x << " " << start->y << "\n";
	cout << "End " << end->x << " " << end->y << "\n";

	vector<pair<int, int>> path = dfs(start, end);
	const char* outputPath = "output.bmp";
	printPathToImage(image, path, outputPath);
	return 0;
}



void setupNodes(const CImg<unsigned char> &image, Node* &start, Node* &end) {
	unordered_map<unsigned int, Node*> nodes;

	const auto rows = image.height();
	const auto column = image.width();
	Node *temp,*previous = nullptr;
	auto iterator = nodes.cend();

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < column; j++) {
			if ((image(j, i, 0, 0) == 255)) {
				temp = new Node;
				temp->x = j;
				temp->y = i;
				temp->visited = false;
				temp->top = temp->bottom = temp->left = temp->right = temp->previous = nullptr;

				iterator = nodes.find((i - 1) * column + j);
				if (iterator != nodes.end()) {
					temp->top = iterator->second;
					temp->top->bottom = temp;
				}

				if (j != 0) {
					temp->left = previous;
					if (previous) {
						previous->right = temp;
					}
				}
				else {
					previous->right = temp;
				}

				nodes.insert(make_pair(i*column + j, temp));
				previous = temp;
			}
			else {
				previous = nullptr;
			}
		}
	}



	for (int i = 0; i < column; i++) {
		iterator = nodes.find(i);
		if (iterator != nodes.end()) {
			start = iterator->second;
			break;
		}


	}

	for (int i = 0; i < column; i++) {
		iterator = nodes.find((rows - 1) * column + i);
		if (iterator != nodes.end()) {
			end = iterator->second;
			break;
		}
	}
}


void printPathToImage(const cimg_library::CImg<unsigned char> &image, const std::vector<std::pair<int, int>> &path, const char * outputPath) {
	cimg_library::CImg<unsigned char> outputImage = image;
	for (int i = 0; i < path.size(); i++) {
		outputImage(path[i].first, path[i].second, 0, 0) = 255;  //Set Red component to 255
		outputImage(path[i].first, path[i].second, 0, 1)
			= outputImage(path[i].first, path[i].second, 0, 2) = 0; //Set Blue and Green component to 0
	}

	outputImage.save(outputPath);
}



