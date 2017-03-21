#include "Maze.h"
#include "Node.h"

#include <queue>


using namespace std;

class mycomparison
{
public:
	bool operator() (Node* &lhs, Node* &rhs)
	{
		return lhs->h > rhs->h;
	}
};


bool gbfs(Maze &maze) {
	std::priority_queue<Node *, std::vector<Node *>, mycomparison> frontier;
	Node *current = nullptr;
	Node* childrens[4];

	frontier.push(maze.start);
	while (!frontier.empty()) {
		current = frontier.top();
		frontier.pop();
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
				if (childrens[i]->h < current->h) {
					frontier.push(current);
					frontier.push(childrens[i]);
					childrens[i]->previous = current;
					break;
				}
				else {
					frontier.push(childrens[i]);
					childrens[i]->previous = current;
				}
			}

		}
	}

	return false;  // No Path Found

}

