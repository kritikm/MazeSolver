#include"CImg.h"
#include <vector>
#include<iostream>
#include <stack>  
#include "SaveToFile.h"

using namespace cimg_library;
using namespace std;

template <typename T>
void printMatrix(const vector<vector<T>> &matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

struct Node {
	Node* top;
	Node* bottom;
	Node* left;
	Node* right;
	Node* previous;

	int ctop, cbottom, cleft, cright;
	int x, y;
	bool visited;

};

typedef struct Node Node;


vector<pair<int, int>> dfs(Node * start, Node* end) {
	std::stack<Node *> stack;
	stack.push(start);
	Node *current = nullptr;
	vector<pair<int, int>> path;

	while (!stack.empty()) {
		current = stack.top();
		stack.pop();
		current->visited = true;
		if (current == end) {
			while (current) {
				//cout << current->y << " " << current->x << "\n";
				path.push_back(make_pair(current->x,current->y));
				current = current->previous;
			}
			return path;
		}
		if (current->top && !current->top->visited) {
			stack.push(current->top);
			current->top->previous = current;
		}
		if (current->bottom && !current->bottom->visited) {
			stack.push(current->bottom);
			current->bottom->previous = current;

		}
		if (current->left && !current->left->visited) {
			stack.push(current->left);
			current->left->previous = current;

		}
		if (current->right && !current->right->visited) {
			stack.push(current->right);
			current->right->previous = current;
		}
	}
	return path;

}

int main()
{
	CImg<unsigned char> image("normal.bmp");

	auto width = image.width();
	auto height = image.height();

	vector<vector<Node*>> nodes(width);

	Node *temp;
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

	Node* start = nullptr;
	Node* end = nullptr;
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

	vector<pair<int, int>> path = dfs(start, end);
	printPathToImage(image, path);
	return 0;

}
