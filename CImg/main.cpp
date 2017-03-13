#include"CImg.h"
#include <vector>
#include<iostream>
#include "SaveToFile.h"
#include "dhananjay.h"

using namespace cimg_library;
using namespace std;


int main() {
	CImg<unsigned char> image("normal.bmp");
	vector<vector<Node*>> nodes;
	Node* start = nullptr;
	Node* end = nullptr;
	setupNodes(image, nodes, start, end);
	vector<pair<int, int>> path = dfs(start, end);
	printPathToImage(image, path);
	return 0;
}
