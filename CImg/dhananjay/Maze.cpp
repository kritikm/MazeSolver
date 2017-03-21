#include "Maze.h"
#include <iostream>

Maze::Maze(std::string inputFile) : image(inputFile.c_str()) {};


Maze::~Maze() {

}

void Maze::initialize() {
	this->rows = image.height();
	this->columns = image.width();
	this->path.reserve(rows);
	this->findStartEnd();
	this->setupNodes();
}

void Maze::findStartEnd() {
	this->start = this->end = nullptr;
	for (int i = 0; i < columns; i++) {
		if (!this->start && (image(i, 0, 0, 0) == 255)) {
			this->start = new Node(i, 0);
		}
		if (!this->end && (image(i, rows - 1, 0, 0) == 255)) {
			this->end = new Node(i, rows - 1);
		}
	}
}
 


void Maze::setupNodes() {
	Node *temp, *previous;
	Node **currentRow = new Node*[this->columns]();
	Node **previousRow = new Node*[this->columns]();
	Node **tempRow;



	previousRow[this->start->x] = start;

	unsigned int count = 0;
	int horizontalCost;

	/*
	*Initialize top and left of current node
	*Initialize bottom of top of current node
	*Initialize right of previous node
	*Insert node into nodes table
	*Note that the loop doesn't run for boundry rows and columns
	*/
	for (int i = 1; i < rows - 1; i++) {
		previous = nullptr;
		horizontalCost = 1;
		for (int j = 1; j < columns - 1; j++) {
			if ((image(j, i, 0, 0) == 255)) {
				if (image(j, i - 1, 0, 0) == 0 && image(j, i + 1, 0, 0) == 0) {
					horizontalCost++;
					previousRow[j] = nullptr;
					continue;
				}

				temp = new Node(j, i);
				temp->h = std::abs(end->x - temp->x) + std::abs(end->y - temp->y);

				if (previousRow[j]) {
					temp->top = previousRow[j];
					temp->tcost = 1;
					temp->top->bottom = temp;
					temp->top->bcost = 1;

				}

				if (previous) {
					temp->left = previous;
					temp->lcost = temp->x - temp->left->x;
					previous->right = temp;
					previous->rcost = temp->lcost;
				}

				currentRow[j] = temp;
				previous = temp;
				count++;

			//	std::cout << temp->x << " " << temp->y << " " << temp->lcost << "\n";

			}
			else {
				previous = nullptr;
			}
			previousRow[j] = nullptr;
		}
		tempRow = previousRow;
		previousRow = currentRow;
		currentRow = tempRow;

	}

	std::cout << "Total Nodes: " << count << "\n";;


	/* Initialize top of end and bottom of top of end*/
		end->top = previousRow[end->x];
		end->tcost = 1;
		end->top->bottom = end;
		end->top->bcost = 1;

	/* Set heuristics of start and end node*/
	start->h = std::abs(end->x - start->x) + std::abs(end->y - start->y);
	end->h = 0;


	delete[] currentRow;
	delete[] previousRow;
}


void Maze::backtrackToGetPath() {
	Node* current = end;
	while (current) {
		//std::cout << current->x << " " << current->y << "\n";
		path.push_back(current);
		current = current->previous;
	}
	reverse(path.begin(), path.end());
}

void Maze::printPathToImage(std::string outputFile) {

	this->backtrackToGetPath();

	cimg_library::CImg<unsigned char> outputImage = image;
	int x, y, j;
	for (int i = 0; i < path.size() - 1; i++) {
		x = path[i]->x;
		y = path[i]->y;
		paintRed(outputImage, x, y);

		if (y == path[i + 1]->y) {
			for (x++; x < path[i + 1]->x; x++) {
				paintRed(outputImage, x, y);
			}
			for (x--; x > path[i + 1]->x; x--) {
				paintRed(outputImage, x, y);
			}
		}
	}

	paintRed(outputImage, path.back()->x, path.back()->y);

	outputImage.save(outputFile.c_str());
}

void Maze::paintRed(cimg_library::CImg<unsigned char> &image, int x, int y) {
	image(x, y, 0, 0) = 255;  //Set Red component to 255
	image(x, y, 0, 1) = 0;
	image(x, y, 0, 2) = 0; //Set Blue and Green component to 0
}