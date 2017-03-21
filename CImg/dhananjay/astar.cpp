#include "Maze.h"
#include "Node.h"

#include <algorithm>
#include <iostream>

using namespace std;


bool CompareMin(Node* &lhs, Node* &rhs) {
	return lhs->h + lhs->g > rhs->h + rhs->g;
}


bool astar(Maze &maze) {
	std::vector<Node *> frontier;

	Node *current = nullptr;
	Node* childrens[4];
	int cost[4];
	int tempGScore;
	auto iterator = frontier.cend();


	maze.start->g = 0;
	frontier.push_back(maze.start);
	std::make_heap(frontier.begin(), frontier.end(), CompareMin);
	while (!frontier.empty()) {
		std::pop_heap(frontier.begin(), frontier.end(), CompareMin);
		current = frontier.back();

		if (current == maze.end) {
			return true;
		}

		frontier.pop_back();
		current->visited = true;
		//std::cout << current->x << " " << current->y << " "<<current->g<<"\n";

		childrens[0] = current->top;
		childrens[1] = current->bottom;
		childrens[2] = current->left;
		childrens[3] = current->right;

		cost[0] = current->tcost;
		cost[1] = current->bcost;
		cost[2] = current->lcost;
		cost[3] = current->rcost;

		for (int i = 0; i < 4; i++) {
			if (childrens[i] && !childrens[i]->visited) {
				iterator = std::find(frontier.begin(), frontier.end(), childrens[i]);
				if (iterator == frontier.end()) {
					frontier.push_back(childrens[i]);
					push_heap(frontier.begin(), frontier.end(), CompareMin);
				}				
				tempGScore = current->g + cost[i];
				if (tempGScore < childrens[i]->g) {
					childrens[i]->g = tempGScore;
					childrens[i]->previous = current;
					std::make_heap(frontier.begin(), frontier.end(), CompareMin);
				}

			}
		}
	}

	return false;  // No Path Found

}

