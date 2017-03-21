// Greedy Best First Search implementation - Graph based strategy
// Takes a graph (an adjacency matrix) along with the heuristic function, the start node and the end node as input
// Prints the GBFS path as an output

#include<iostream>
#include<vector>
#include<stdlib.h>
#define MAX 28

using namespace std;

typedef struct node
{
	vector<int> _path;
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

int _removed = 0;
int vectorSize = 1;
vector<int> path(1);
void greedyBestFirst(NODEX a[MAX][MAX], vector<int>& heuristic, vector<NODE>& explored, vector<NODE>& frontier, int start, int goal);
void displayResult(vector<NODE>&);
void addToFrontier(vector<NODE>& , NODE);
void addToExplored(vector<NODE>& , NODE);
void removeFromFrontier(vector<NODE>& , vector<NODE>& , int);

void displayResult(vector<NODE>& explored, vector<NODE>& frontier)
{
	cout << "\nThe greedy Best First Search path is:\n";
	/*int n = path.size();
	for (int i = 0; i < n-1; i++)
		cout << path.at(i)<<" ";
	cout << endl;
	n = explored.size();
	for (int i = 1; i < n; i++)
		cout << explored.at(i).nodeID<<" ";*/
	cout << endl;
	// cout << "\n\nThe actual path is: ";
	int result_size = frontier.at(0)._path.size();
	for (int i = 0; i < result_size; i++)
		cout << frontier.at(0)._path.at(i) << " ";
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
// Entries with lower heuristics will have higher priorites and will be placed in front of the queue
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
	// cout << "n = " << n;
	frontier[n-1] = temp;
}

void addToExplored(vector<NODE>& explored, NODE temp)
{
	//cout << " \nexplored " << temp.nodeID << endl;
	explored.push_back(temp);
	explored.at(0).fn;
}

// Removes the entry from the front of the frontier set and puts in explored
void removeFromFrontier(vector<NODE>& frontier, vector<NODE>& explored, int goal)
{
	vectorSize--;
	int n = frontier.size();
	if (n == 0)
		return;
	// Remove the first element from frontier and put it in explored
	addToExplored(explored, frontier.at(0));
	//cout << "\nRemoving: " << frontier.at(0).nodeID<<"  "<<frontier.at(0).fn<<endl<<endl;
	int removed = frontier.at(0).nodeID;
	for (int i = 0; i < n-1; i++)
		frontier.at(i) = frontier.at(i + 1);
	frontier.pop_back(); // remove the last element (duplicate)
	int pathLength = path.size();
	path.resize(pathLength + 1);
	path[pathLength-1] = removed;
	//d(frontier); cout << endl;
	// Goal is found! Program exits here
	if (removed == goal)
	{
		//for (int i = 0; i < explored.size(); i++)
			//cout << explored.at(i).nodeID<<" ";
		//cout << endl;
		//displayResult(explored, frontier);
		exit(0);
	}
}

// checks if the node n is present in the explored set
bool inExplored(vector<NODE> explored, int n)
{
	int explored_size = explored.size();
	for (int i = 0; i < explored_size; i++)
	{
		if (explored.at(i).nodeID == n)
			return true;
	}
	return false;
}

// checks if x is a neighbour of y
bool isNeighbour(NODEX a[MAX][MAX], int x, int y)
{
	if (a[x][y].dist)
		return true;
	return false;
}

void greedyBestFirst(NODEX a[MAX][MAX], vector<int>& heuristic, vector<NODE>& explored, vector<NODE>& frontier, int start, int goal)
{
	for (int i = 0; i < MAX; i++)
	{
		// Check for unexplored neighbours
		if ((a[frontier[0].nodeID][i]).dist && !(a[frontier[0].nodeID][i]).visited)
		{
			for (int s = 0; s < MAX; s++)
				a[s][frontier[0].nodeID].visited = true;
			NODE temp;
			temp._path.insert(temp._path.end(), frontier.at(0)._path.begin(), (frontier.at(0)._path).end());
			temp._path.push_back(i);
			// ._path.push_back(frontier.at(0)._path);
			temp.visited = true;
			temp.fn = heuristic[i];
			temp.nodeID = i;
			// If neighbour, then put in frontier set
			// d(frontier);	
			_removed = 0;
			// cout << "Putting " << temp.nodeID << "  " << temp.fn; 
			addToFrontier(frontier, temp);
			// d(frontier);
		}
	}
	// Remove from frontier set and put in explored
	removeFromFrontier(frontier, explored, goal);
	//_removed++; 
	// displayResult(explored);
	if (++_removed == 2) // a terminal node has been reached
	{
		int last_path_element; int f = 0;
		while (1)
		{
			int path_len = path.size()-1;
			last_path_element = path.at(path_len - 1);
			if (isNeighbour(a, frontier.at(0).nodeID, last_path_element))
				break;
			else
			{
				// cout << "pppoooooopped " << last_path_element;
				path.pop_back();
			}
			// displayResult(explored);
		}
		/*
		int flag = 0;
		while (a[frontier][])
		{
			int path_len = path.size();
			int exp_len = explored.size() - 1;
			int z = path.at(path_len - 1);
			for (int r = 0; r < exp_len; r++)
			{
				pop the shit out of path until a neighbour of frontier(0) is reached which hasnt been included in the explored
			}

			flag = 1;
		}*/
	}
	// d(frontier);

	cout << "\n\nThe GreedyBFS path is: ";
	int result_size = frontier.at(0)._path.size();
	for (int i = 0; i < result_size; i++)
		cout << frontier.at(0)._path.at(i)<<" ";
	cout << endl;
	greedyBestFirst(a, heuristic, explored, frontier, frontier[0].nodeID, goal);
}

int main()
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
	//heuristic = { 1, 2, 3, 4, 5, 6, 7, 0 };
	// heuristic = { 26, 0, 25 ,24 ,22 ,13 ,12 ,10, 21 ,19 ,11 ,17 ,13 ,9 ,7 ,17 ,15 ,13 ,11 ,13 ,11 ,4 ,2 ,13 ,11 ,7 ,5 ,3};
	//heuristic = { 26, 0, 25 ,24 ,22 ,13 ,12 ,14, 21 ,19 ,11 ,17 ,13 ,9 ,7 ,17 ,15 ,13 ,11 ,13 ,11 ,4 ,2 ,13 ,11 ,7 ,5 ,3};

	for (int i = 0; i < MAX; i++)
		cin >> heuristic[i];

	// Declare the explored set
	vector<NODE> explored(1);

	// Declare the frontier set
	vector<NODE> frontier(vectorSize);

	// Get the start node. Note that, the indexing starts from zero
	int start; 
	cout << "Enter the starting node: ";
	cin >> start;
	// start = 0;
	// Initialise the frontier set
	NODE temp;
	temp._path.push_back(start);
	temp.visited = true;
	temp.nodeID = start;
	temp.fn = heuristic[start];
	frontier.at(0) = temp;

	// Get the goal node
	int goal;
	cout << "Enter the goal node: ";
	cin >> goal;
	// goal = 1;
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
2 0 0 0 0 7 1 0
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
/*
0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0
1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 1 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 2 0 9 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 9 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 2 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 2 0 0 0 0 0 0 0 3 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 2 0 8 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0 8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 2 0 0 4 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 3 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 4 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 2 0 0 0 0 0 0 0 4 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 2 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 2 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 1
0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 0 0 0 0 0 2 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 2 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 0 0 0 0 2 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 2
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 2 0
*/
/*
0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0
1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 1 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 2 0 9 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 9 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 2 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 2 0 0 0 0 0 0 0 3 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 2 0 8 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0 8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 2 0 0 4 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 3 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 4 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 2 0 0 0 0 0 0 0 4 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 2 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 2 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 1
0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 0 0 0 0 0 2 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 2 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 0 0 0 0 2 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 2
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 2 0
*/