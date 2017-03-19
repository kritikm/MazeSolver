#include "dhananjay.h"

#include<algorithm>
#include <unordered_map>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {
	CImg<unsigned char> image("images/combo6k.bmp");
	Node *start, *end;
	setupNodes(image, start, end);

	cout << "Start " << start->x << " " << start->y << "\n";
	cout << "End " << end->x << " " << end->y << "\n";

	vector<pair<int, int>> path;
	//path = gbfs(start, end);			// Greedy Best First Search
	path = dfs(start, end);           // Depth First  Search


	const char* outputPath = "output.bmp";
	printPathToImage(image, path, outputPath);
	return 0;
}


/* Create adjacency list*/
void setupNodes(const CImg<unsigned char> &image, Node* &start, Node* &end) {
	unordered_map<unsigned int, Node*> nodes;  //Hash Table is used because 

	const auto rows = image.height();
	const auto column = image.width();
	Node *temp, *previous = nullptr;
	auto iterator = nodes.cend();

	/* Find start node*/
	for (int i = 0; i < column; i++) {
		if ((image(i, 0, 0, 0) == 255)) {
			temp = new Node;
			temp->x = i;
			temp->y = 0;
			temp->visited = false;
			temp->top = temp->bottom = temp->left = temp->right = temp->previous = nullptr;
			nodes.insert(make_pair(i, temp));

			start = temp;

			break;
		}


	}

	/* Find end node*/
	for (int i = 0; i < column; i++) {
		if ((image(i, rows - 1, 0, 0) == 255)) {
			temp = new Node;
			temp->x = i;
			temp->y = rows - 1;
			temp->visited = false;
			temp->top = temp->bottom = temp->left = temp->right = temp->previous = nullptr;
			nodes.insert(make_pair((rows - 1) * column + i, temp));
		
			end = temp;


			break;
		}
	}

	/* 
		*Initialize top and left of current node
		*Initialize bottom of top of current node
		*Initialize right of previous node
		*Insert node into nodes table
		*Note that loop doesn't run for boundry rows and columns
	*/
	for (int i = 1; i < rows - 1; i++){
		for (int j = 1; j < column - 1; j++) {
			if ((image(j, i, 0, 0) == 255)) {
				temp = new Node;
				temp->x = j;
				temp->y = i;
				temp->visited = false;
				temp->heuristic = abs(end->x - temp->x) + abs(end->y - temp->y);
				temp->top = temp->bottom = temp->left = temp->right = temp->previous = nullptr;

				iterator = nodes.find((i - 1) * column + j);
				if (iterator != nodes.end()) {
					temp->top = iterator->second;
					temp->top->bottom = temp;
				}

				if (j != 1) {
					temp->left = previous;
					if (previous) {
						previous->right = temp;
					}
				}

				nodes.insert(make_pair(i*column + j, temp));
				previous = temp;
			}
			else {
				previous = nullptr;
			}
		}
	}


	/* Initialize top of end and bottom of top of end*/
	iterator = nodes.find((end->y - 1) * column + end->x);
	if (iterator != nodes.end()) {
		end->top = iterator->second;
		end->top->bottom = end;
	}

	end->heuristic = 0;
	start->heuristic = abs(end->x - start->x) + abs(end->y - start->y);

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



