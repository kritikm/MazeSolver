#include "dhananjay.h"

#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <cmath>

using namespace cimg_library;
using namespace std;

int main() {
	Node *start, *end;

	string inputFile = "images/perfect4k.bmp";
	string outputFile = "output.bmp";
	setupNodes(inputFile, start, end);

	cout << "Start " << start->x << " " << start->y << "\n";
	cout << "End " << end->x << " " << end->y << "\n";

	vector<pair<int, int>> path;

	//path = gbfs(start, end);			// Greedy Best First Search
	path = dfs(start, end);           // Depth First  Search


	printPathToImage(inputFile, path, outputFile);
	return 0;
}



void findStartEnd(CImg<unsigned char> &image, Node* &start, Node* &end) {
	auto rows = image.height();
	auto column = image.width();
	start = end = nullptr;


	for (int i = 0; i < column; i++) {
		if (!start && (image(i, 0, 0, 0) == 255)) {
			start = new Node(i, 0);
		}

		if (!end && (image(i, rows - 1, 0, 0) == 255)) {
			end = new Node(i, rows - 1);
		}
	}
}


void setupNodes(string inputFile, Node* &start, Node* &end) {

	CImg<unsigned char> image(inputFile.c_str());
	auto rows = image.height();
	auto columns = image.width();
	Node *temp, *previous = nullptr;
	unordered_map<unsigned int, Node*> currentRow(columns/3), previousRow(columns / 3);
	auto iterator = previousRow.cend();

	start = end = nullptr;
	/* Find start and end node*/
	findStartEnd(image, start, end);


	previousRow[start->x] = start;

	unsigned int count = 0;

	/*
		*Initialize top and left of current node
		*Initialize bottom of top of current node
		*Initialize right of previous node
		*Insert node into nodes table
		*Note that the loop doesn't run for boundry rows and columns
	*/
	for (int i = 1; i < rows - 1; i++) {
		previous = nullptr;
		for (int j = 1; j < columns - 1; j++) {
			if ((image(j, i, 0, 0) == 255)) {
				temp = new Node(j, i);
				temp->heuristic = std::abs(end->x - temp->x) + std::abs(end->y - temp->y);
				iterator = previousRow.find((i - 1) * columns + j);
				if (iterator != previousRow.end()) {
					temp->top = iterator->second;
					temp->top->bottom = temp;
				}

				temp->left = previous;
				if (previous) {
					previous->right = temp;
				}

				currentRow[i*columns + j] = temp;
				previous = temp;
				count++;
			}
			else {
				previous = nullptr;
			}
		}
		previousRow.clear();
		previousRow.swap(currentRow);
		currentRow.reserve(columns / 3);
	}

	cout << "Total Nodes: " << count;


	/* Initialize top of end and bottom of top of end*/
	iterator = previousRow.find((end->y - 1) * columns + end->x);
	if (iterator != previousRow.end()) {
		end->top = iterator->second;
		end->top->bottom = end;
	}


	/* Set heuristics of start and end node*/
	start->heuristic = std::abs(end->x - start->x) + std::abs(end->y - start->y);
	end->heuristic = 0;

}


void printPathToImage(string inputFile, const std::vector<std::pair<int, int>> &path, string outputFile) {
	CImg<unsigned char> outputImage(inputFile.c_str());

	for (int i = 0; i < path.size(); i++) {
		outputImage(path[i].first, path[i].second, 0, 0) = 255;  //Set Red component to 255
		outputImage(path[i].first, path[i].second, 0, 1)
			= outputImage(path[i].first, path[i].second, 0, 2) = 0; //Set Blue and Green component to 0
	}

	outputImage.save(outputFile.c_str());
}

vector<pair<int, int>> backtrack(Node* start) {
	vector<pair<int, int>> path;

	Node* current = start;
	while (current) {
		//cout << current->x << " " << current->y << "\n";
		path.push_back(make_pair(current->x, current->y));
		current = current->previous;
	}
	reverse(path.begin(), path.end());
	return path;
}



