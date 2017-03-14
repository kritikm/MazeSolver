// Greedy Best First Search implementation - Graph based strategy
// Takes a graph (an adjacency matrix) along with the heuristic function, the start node and the end node as input
// Prints the GBFS path as an output

#include<iostream>
#include<vector>
#include<stdlib.h>
#define MAX 8

using namespace std;

typedef struct node
{
	bool visited = false;
	int nodeID;
	int fn;
}NODE;

typedef struct nodex
{
	bool visited = false;
	int dist;
	int nodeID;
}NODEX;

int vectorSize = 1;
vector<int> path(1);

void displayResult()
{
	cout << "\nThe greedy Best First Search path is:\n";
	int n = path.size();
	for (int i = 0; i < n-1; i++)
		cout << path.at(i)<<" ";
	cout << endl;
}

// for debugging only
void d(vector<NODE>& frontier)
{
	cout << endl;
	for (int i = 0; i < frontier.size(); i++)
	{
		cout << frontier.at(i).nodeID << "\t" << frontier.at(i).fn << endl;
	}
}

// The entries must be made based on pirorities wrt the Heuristic
// Entries with lower heuristics will have higher pirorites and will be placed in front of the queue
void addToFrontier(vector<NODE>& frontier, NODE temp)
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
		if(temp.fn <= frontier.at(i).fn)
		{
			for(int j = n-1; j >= i; j--)
				frontier[j] = frontier[j-1];
			frontier[i] = temp;
			return;
		}
	}
	// Otherwise, put the element at the last position
	frontier[n-1] = temp;
}

void addToExplored(vector<NODE> explored, NODE temp)
{
	explored.push_back(temp);
}

// Removes the entry from the front of the frontier set and puts in explored
void removeFromFrontier(vector<NODE>& frontier, vector<NODE>& explored, int goal)
{
	int n = frontier.size();
	if (n == 0)
		return;
	// Remove the first element from frontier and put it in explored
	addToExplored(explored, frontier.at(0));
	// cout << "Removing: " << frontier.at(0).nodeID<<endl;
	int removed = frontier.at(0).nodeID;
	for (int i = 0; i < n-1; i++)
		frontier.at(i) = frontier.at(i + 1);
	int pathLength = path.size();
	path.resize(pathLength + 1);
	path[pathLength-1] = removed;
	// Goal is found! Program exits here
	if (removed == goal)
	{
		displayResult();
		exit(0);
	}
}

 int k = 0;
// int vicci[MAX] = { 0 };
void greedyBestFirst(NODEX a[MAX][MAX], vector<int>& heuristic, vector<NODE>& explored, vector<NODE>& frontier, int start, int goal)
{
	for (int i = 0; i < MAX; i++)
	{
		// Check for neighbours
		if ((a[frontier[0].nodeID][i]).dist)// && !vicci[i])
		{
			// vicci[i] = 1;
			NODE temp;
			temp.visited = true;
			temp.fn = heuristic[i];
			temp.nodeID = i;
			// If neighbour, then put in frontier set
			//cout << "Putting " << temp.nodeID << "  " << temp.fn << endl;
			addToFrontier(frontier, temp);
			//d(frontier);
			// cout << frontier.at(k).nodeID << "  "<<frontier.at(k).fn << endl;
			// k++;
		}
	}
	// Remove from frontier set and put in explored
	removeFromFrontier(frontier, explored, goal);
	//d(frontier);
	greedyBestFirst(a, heuristic, explored, frontier, frontier[0].nodeID, goal);
}

int main2()
{
	// Get the distance matrix
	cout << "Enter the distance matrix: \n";
	NODEX a[MAX][MAX];
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			cin >> a[i][j].dist;

	// Get the heuristic function from the user
	cout << "Enter the heuristic vector: ";
	vector<int> heuristic(MAX);
	// heuristic = { 7,6,2,1,0 };
	//heuristic = { 6, 6, 6, 8, 5, 4, 15, 0 };
	for (int i = 0; i < MAX; i++)
		cin >> heuristic[i];

	// Declare the explored set
	vector<NODE> explored(MAX);

	// Declare the frontier set
	vector<NODE> frontier(vectorSize);

	// Get the start node. Note that, the indexing starts from zero
	int start; 
	cout << "Enter the starting node: ";
	cin >> start;

	// Initialise the frontier set
	NODE temp;
	temp.visited = true;
	temp.nodeID = start;
	temp.fn = heuristic[start];
	frontier.at(0) = temp;

	// Get the goal node
	int goal;
	cout << "Enter the goal node: ";
	cin >> goal;

	// Call GBFS
	greedyBestFirst(a, heuristic, explored, frontier, start, goal);
	cout << endl;
	return 0;
}
/*
0 1 4 0 0
0 0 2 5 0
0 0 0 2 0
0 0 0 0 3
0 0 0 0 0
*/
/*
0 1 2 0 0 0 0 0
1 0 0 7 4 0 0 0
0 2 0 0 0 7 1 0
0 7 0 0 0 0 0 3
0 4 0 0 0 0 0 2
0 0 7 0 0 0 0 5
0 0 1 0 0 0 0 12
0 0 0 3 2 5 12 0

0 1 2 0 2 0 6 0
1 0 4 7 4 0 3 4
0 2 0 9 0 7 1 2
5 7 0 4 4 0 0 3
3 4 3 7 0 5 0 2
2 0 7 0 2 0 4 5
0 1 1 0 0 4 0 12
0 8 3 3 2 5 12 0

100 5 6 8 5 4 15 0
*/
