#include <stack>  
#include <vector>
#include "dhananjay.h"
#include<iostream>

using namespace std;


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
				//cout << current->x << " " << current->y << "\n";
				path.push_back(make_pair(current->x, current->y));
				current = current->previous;
			}
			reverse(path.begin(), path.end());
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
	path.push_back(make_pair(0, 0));
	return path;

}

