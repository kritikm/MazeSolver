#include "Maze.h"
#include "Node.h"
#include <stack>  

using namespace std;

bool dfs(Maze &maze) {
	std::stack<Node *> stack;
	Node *current = nullptr;
	Node* childrens[4];

	stack.push(maze.start);
	while (!stack.empty()) {
		current = stack.top();
		stack.pop();
		current->visited = true;
		if (current == maze.end) {
			return true;
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
	return false;   // No Path Found

}

