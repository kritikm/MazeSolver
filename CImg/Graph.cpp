#pragma once
#include"Graph.h"
#include<iostream>

using namespace std;

typedef struct nodex
{
	bool visited = false;
	int dist;
	int nodeID;
}NODEX;

typedef struct node
{
	std::vector<int> _path;
	bool visited = false;
	int nodeID;
	int fn;
}NODE;

void execGBFS(NODEX **, std::vector<int> &, std::vector<NODE> &, std::vector<NODE> &, int, int);
void addToFrontier(std::vector<NODE> &, NODE);
int removeFromFrontier(std::vector<NODE> &, std::vector<NODE> &, int);
void addToExplored(std::vector<NODE>, NODE);
bool inExplored(std::vector<NODE>, NODE);
bool isNeighbour(NODEX **, int, int);

int _removed = 0;
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

void execGBFS(NODEX ** a, std::vector<int> & heuristic, std::vector<NODE> & explored, std::vector<NODE> & frontier, int start, int goal)
{
	int size = heuristic.size();
	for (int i = 0; i < size; i++)
	{
		// Check for unexplored neighbours
		if ((a[frontier[0].nodeID][i]).dist && !(a[frontier[0].nodeID][i]).visited)
		{
			for (int s = 0; s < size; s++)
				a[s][frontier[0].nodeID].visited = true;
			NODE temp;
			temp._path.insert(temp._path.end(), frontier.at(0)._path.begin(), (frontier.at(0)._path).end());
			temp._path.push_back(i);
			temp.visited = true;
			temp.fn = heuristic[i];
			temp.nodeID = i;
			// If neighbour, then put in frontier set
			// d(frontier);	
			_removed = 0;
			//cout << "Putting " << temp.nodeID << "  " << temp.fn; 
			addToFrontier(frontier, temp);
			//d(frontier);
		}
	}
	// Remove from frontier set and put in explored
	if (removeFromFrontier(frontier, explored, goal) == 1)
		return;
	if (++_removed == 2) // a terminal node has been reached
	{
		int last_path_element;
		int f = 0;
		while (1)
		{
			int path_len = path.size() - 1;
			last_path_element = path.at(path_len - 1);
			if (isNeighbour(a, frontier.at(0).nodeID, last_path_element))
				break;
			else
				path.pop_back();
		}
	}

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
	// cout << "n = " << n;
	frontier[n - 1] = temp;
}

int removeFromFrontier(std::vector<NODE> &frontier, std::vector<NODE> &explored, int goal)
{
	vectorSize--;
	int n = frontier.size();
	if (n == 0)
		return -1;
	// Remove the first element from frontier and put it in explored
	addToExplored(explored, frontier.at(0));
	//cout << "\nRemoving: " << frontier.at(0).nodeID<<"  "<<frontier.at(0).fn<<endl<<endl;
	int removed = frontier.at(0).nodeID;
	if (removed == goal)
	{
		path = frontier.at(0)._path;
		return 1;
	}
	for (int i = 0; i < n - 1; i++)
		frontier.at(i) = frontier.at(i + 1);
	frontier.pop_back();// remove the last element (duplicate)
	int pathLength = path.size();
	path.resize(pathLength + 1);
	path[pathLength - 1] = removed;	// Goal is found! Program exits here

	return 0;

}

void addToExplored(std::vector<NODE> explored, NODE temp) { explored.push_back(temp); }

bool inExplored(std::vector<NODE> explored, int n)
{
	int explored_size = explored.size();
	for (int i = 0; i < explored_size; i++)
	{
		if (explored.at(i).nodeID == n)
			return true;
	}
	return false;
}
bool isNeighbour(NODEX ** a, int x, int y)
{
	if (a[x][y].dist)
		return true;
	return false;
}