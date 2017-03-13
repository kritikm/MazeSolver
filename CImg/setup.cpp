#include"CImg.h"
#include <vector>
#include<algorithm>
#include "dhananjay.h"

using namespace cimg_library;
using namespace std;



void setupNodes(const CImg<unsigned char> &image,vector<vector<Node*>> &nodes,Node* &start,Node* &end) {

	auto width = image.width();
	auto height = image.height();
	Node *temp;

	nodes.resize(width);
	for (int i = 0; i < width; i++){
		nodes[i].resize(height);
		for (int j = 0; j < height; j++) {
			if ((image(j, i, 0, 0) == 255)) {
				temp = new Node;
				temp->x = j;
				temp->y = i;
				temp->visited = false;
				temp->previous = nullptr;
			}
			else {
				temp = nullptr;
			}
			nodes[i][j] = temp;
		}
	}


	for (int i = 0; i < nodes[0].size(); i++) {
		if (nodes[0][i]) {
			nodes[0][i]->top = nodes[0][i]->left = nodes[0][i]->right = nullptr;
			nodes[0][i]->bottom = nodes[1][i];
			start = nodes[0][i];
			break;
		}
	}

	for (int i = 0; i < nodes[0].size(); i++) {
		if (nodes.back()[i]) {
			nodes.back()[i]->bottom = nodes.back()[i]->left = nodes.back()[i]->right = nullptr;
			nodes.back()[i]->top = nodes[1][i];
			end = nodes.back()[i];
			break;
		}
	}

	
	for (int i = 1; i < nodes.size() - 1; i++) {
		for (int j = 1; j < nodes[i].size() - 1; j++) {
			if (nodes[i][j]) {
				nodes[i][j]->top = nodes[i - 1][j];
				nodes[i][j]->bottom = nodes[i + 1][j];
				nodes[i][j]->left = nodes[i][j - 1];
				nodes[i][j]->right = nodes[i][j + 1];
			}
		}
	}



	

}

