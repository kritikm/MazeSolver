#include "dhananjay.h"

#include <stack>  

using namespace std;


vector<pair<int, int>> dfs(Node * start, Node* end) {
	std::stack<Node *> stack;
	stack.push(start);
	Node *current = nullptr;
	vector<pair<int, int>> path;
	Node* childrens[4];

	while (!stack.empty()) {
		current = stack.top();
		stack.pop();
		current->visited = true;
		if (current == end) {
			return backtrack(current);
		}

		childrens[0] = current->top;
		childrens[1] = current->bottom;
		childrens[2] = current->left;
		childrens[3] = current->right;

		for (int i = 0; i < 4; i++) {
			if (childrens[i] && !childrens[i]->visited) {
				stack.push(childrens[i]);
				childrens[i]->previous = current;
			}
		}
	}
	return backtrack(nullptr);   // No Path Found

}

