#include"Maze.h"

Maze::Maze(int ** maze, int width, int height)
{
	this->maze = maze;
	this->width = width;
	this->height = height;
}

int ** Maze::getMaze() { return maze; }
int ** Maze::getGraph() { return graph; }
int Maze::getMazeWidth() { return width; }
int Maze::getMazeHeight() { return height; }
std::vector<Node> Maze::getNodes() { return nodes; }


void Maze::makeRelevantNodes()
{
	int ends = 0;
	for (int i = 0; i < height; i++)
	{
		if (maze[0][i] == 1)
		{
			nodes.push_back(Node(0, i, true));
			break;
		}
	}

	for (int i = 0; i < height; i++)
	{
		if (maze[width - 1][i] == 1)
		{
			nodes.push_back(Node(width - 1, i, true));
			break;
		}
	}

	for (int i = 1; i < width - 1; i++)
		for (int j = 1; j < height - 1; j++)
			if (maze[i][j] == 1)
				if ((maze[i][j + 1] == 1 || maze[i][j - 1] == 1) && (maze[i + 1][j] == 1 || maze[i - 1][j] == 1))
					nodes.push_back(Node(i, j, false));

	makeConnections();
}

void Maze::makeConnections()
{
	int nNodes = nodes.size();

	graph = new int*[nNodes];
	for (int i = 0; i < nNodes; i++)
	{
		graph[i] = new int[nNodes];
		for (int j = 0; j < nNodes; j++)
			graph[i][j] = 0;
	}

	int pos = 0;
	for (auto trav = nodes.begin(); trav != nodes.end(); trav++, pos++)
	{
		int col = (*trav).getY();
		int row = (*trav).getX();

		if (pos == 0)	//start
		{
			(*trav).setTop(NULL, -1);
			(*trav).setBottom(&getNodeWithXY(row + 1, col), 1);
			(*trav).setLeft(NULL, -1);
			(*trav).setRight(NULL, -1);
			continue;
		}
		if (pos == 1)	//end
		{
			(*trav).setTop(&getNodeWithXY(row - 1, col), 1);
			(*trav).setBottom(NULL, -1);
			(*trav).setLeft(NULL, -1);
			(*trav).setRight(NULL, -1);
			continue;
		}

		int cost = 1;

		//for bottom link
		if (maze[row + 1][col] == 0)
			(*trav).setBottom(NULL, 0);
		else
		{
			row++;	//the element below
			int nodeCheck = isNode(row, col);
			int prev = nodeCheck;
			while (nodeCheck == -1)
			{
				cost++;
				row++;
				prev = nodeCheck;
				nodeCheck = isNode(row, col);
			}
			(*trav).setBottom(&getNodeWithXY(row, col), cost);
			prev = nodeCheck;
			graph[pos][prev] = graph[prev][pos] = cost;
		}

		//for top link
		cost = 1;
		col = (*trav).getY();
		row = (*trav).getX() - 1;	//the element above

		if (maze[row][col] == 0)
			(*trav).setTop(NULL, -1);
		else
		{
			int nodeCheck = isNode(row, col);
			int prev = nodeCheck;
			while (nodeCheck == -1)
			{
				cost++;
				row--;
				prev = nodeCheck;
				nodeCheck = isNode(row, col);
			}
			(*trav).setTop(&getNodeWithXY(row, col), cost);
			prev = nodeCheck;
			graph[pos][prev] = graph[prev][pos] = cost;
		}

		//for left link
		cost = 1;
		col = (*trav).getY() - 1;	//the element on the left
		row = (*trav).getX();

		if (maze[row][col] == 0)
			(*trav).setLeft(NULL, -1);
		else
		{
			int nodeCheck = isNode(row, col);
			int prev = nodeCheck;
			while (nodeCheck == -1)
			{
				cost++;
				col--;
				prev = nodeCheck;
				nodeCheck = isNode(row, col);
			}
			(*trav).setLeft(&getNodeWithXY(row, col), cost);
			prev = nodeCheck;
			graph[pos][prev] = graph[prev][pos] = cost;
		}

		//for right link
		cost = 1;
		col = (*trav).getY() + 1;	//the element on the right
		row = (*trav).getX();

		if (maze[row][col] == 0)
			(*trav).setRight(NULL, -1);
		else
		{
			int nodeCheck = isNode(row, col);
			int prev = nodeCheck;
			while (nodeCheck == -1)
			{
				cost++;
				col++;
				prev = nodeCheck;
				nodeCheck = isNode(row, col);
			}
			prev = nodeCheck;
			(*trav).setLeft(&getNodeWithXY(row, col), cost);
			graph[pos][prev] = graph[prev][pos] = cost;
		}
	}
}

int Maze::isNode(int x, int y)
{
	int pos = 0;
	for (auto trav = nodes.begin(); trav != nodes.end(); trav++, pos++)
		if ((*trav).getX() == x && (*trav).getY() == y)
			return pos;
	return -1;
}

Node Maze::getNodeWithXY(int x, int y)
{
	for (auto trav = nodes.begin(); trav != nodes.end(); trav++)
		if ((*trav).getX() == x && (*trav).getY() == y)
			return (*trav);
}