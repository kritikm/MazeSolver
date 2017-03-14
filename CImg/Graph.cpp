#pragma once
#include"Graph.h"

typedef struct nodex
{
	bool visited = false;
	int dist;
	int nodeID;
}NODEX;

typedef struct node
{
	bool visited = false;
	int nodeID;
	int fn;
}NODE;

void execGBFS(NODEX **, std::vector<int>, std::vector<NODE>, std::vector<NODE>, int, int);
void addToFrontier(std::vector<NODE> &, NODE);
int removeFromFrontier(std::vector<NODE> &, std::vector<NODE> &, int);
void addToExplored(std::vector<NODE>, NODE temp);

int vectorSize = 1; 
std::vector<int> path(1);


std::vector<int> greedyBestFirst(int ** graph, std::vector<int> heuristic, int start, int goal)
{
	int size = heuristic.size();
	std::vector<NODE> explored(size);
	std::vector<NODE> frontier(vectorSize);

	NODEX ** adjacency = new NODEX*[size];

	for (int i = 0; i < size; i++)
	{
		adjacency[i] = new NODEX[size];
		for (int j = 0; j < size; j++)
			adjacency[i][j].dist = graph[i][j];
	}


	NODE temp;
	temp.visited = true;
	temp.nodeID = start;
	temp.fn = heuristic[start];
	frontier.at(0) = temp;

	execGBFS(adjacency, heuristic, explored, frontier, start, goal);
	return path;
}

void execGBFS(NODEX ** a, std::vector<int> heuristic, std::vector<NODE> explored, std::vector<NODE> frontier, int start, int goal)
{
	int size = heuristic.size();
	for (int i = 0; i < size; i++)
	{
		// Check for neighbours
		if ((a[frontier[0].nodeID][i]).dist)
		{
			// vicci[i] = 1;
			NODE temp;
			temp.visited = true;
			temp.fn = heuristic[i];
			temp.nodeID = i;
			// If neighbour, then put in frontier set
			addToFrontier(frontier, temp);
		}
	}
	// Remove from frontier set and put in explored
	if (removeFromFrontier(frontier, explored, goal) == 1)
		return;

	execGBFS(a, heuristic, explored, frontier, frontier[0].nodeID, goal);
}

void addToFrontier(std::vector<NODE> &frontier, NODE temp)
{
	if (vectorSize == 1)
	{
		frontier.push_back(temp);
		vectorSize++;
		return;
	}
	vectorSize++;
	frontier.resize(vectorSize);
	int n = vectorSize;
	for (int i = 1; i < n; i++) // do not disturb the first element
	{
		if (temp.fn <= frontier.at(i).fn)
		{
			for (int j = n - 1; j >= i; j--)
				frontier[j] = frontier[j - 1];
			frontier[i] = temp;
			return;
		}
	}
	// Otherwise, put the element at the last position
	frontier[n - 1] = temp;

}

int removeFromFrontier(std::vector<NODE> &frontier, std::vector<NODE> &explored, int goal)
{
	int n = frontier.size();
	if (n == 0)
		return -1;
	// Remove the first element from frontier and put it in explored
	addToExplored(explored, frontier.at(0));
	// cout << "Removing: " << frontier.at(0).nodeID<<endl;
	int removed = frontier.at(0).nodeID;
	for (int i = 0; i < n - 1; i++)
		frontier.at(i) = frontier.at(i + 1);
	int pathLength = path.size();
	path.resize(pathLength + 1);
	path[pathLength - 1] = removed;
	// Goal is found! Program exits here
	if (removed == goal)
		return 1;
	return 0;

}

void addToExplored(std::vector<NODE> explored, NODE temp) { explored.push_back(temp); }