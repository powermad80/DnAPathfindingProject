#include <iostream>
#include <cstdlib>
#include <list>

//Jake Dubusker
//Ryan Karrasch
//Group 14

using namespace std;

class Graph
{
private:
	int n;			
	int **matrix;
	bool *visited;	//number of nodes, adjacency matrix, and array marking visited nodes always visible
					//to all functions within each instance of the graph class
public:
	Graph(int n)
	{
		this->n = n;
		visited = new bool[n];
		matrix = new int*[n];

		for (int i = 0; i < n; i++)
		{
			matrix[i] = new int[n];	//initialize new int row in matrix

			for (int j = 0; j < n; j++)
			{
				matrix[i][j] = 0; //create n x n matrix of zeroes to initialize adjacency matrix
			}
		}
	}

	bool Edge(int i, int j)
	{
		if (i >= n || j >= n || i < 0 || j < 0)
		{
			return false;	//verify that the input edge is not out of bounds, equal to n or less than zero
		}

		else
		{
			matrix[i][j]++;
			matrix[j][i]++;	//if edge is valid, add one to the matrix position and its reflection,
			return true;    //indicating a connection between the two nodes
		}
	}

	void PrintGraph()
	{
		int i;
		int j;

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				cout << matrix[i][j] << "  ";	//iterate through the matrix, printing out each cell's value
			}

			cout << endl;
		}
	}

	void BFS(int v)
	{

		list<int> queue;	//initialize queue
		visited[v] = true;	//set origin node as visited
		queue.push_back(v);

		cout << "Component: " << v << " ";
		while (!queue.empty())
		{
			v = queue.front();
			queue.pop_front();

			
			for (int i = 0; i < n; i++)
			{
				if (matrix[v][i] > 0 && visited[i] == false) //Check all possible adjacencies of a node
				{											 //and push any found adjacent nodes to back of queue,
					queue.push_back(i);						 //repeating for all found nodes
					cout << i << " ";
					visited[i] = true;
				}
			}
		}
		cout << endl;

	}

	int DiameterBFS(int v)	//Identical BFS function, but without any console output and which keeps track of node distances
	{

		for (int i = 0; i < n; i++)
		{
			visited[i] = false;
		}

			list<int> queue;
			list<int> distances;	//list of distances from origin to other nodes
			int distance = 1;
			bool travel = false;	//indicates whether a new node has been found and pushed on one cycle of a loop
			visited[v] = true;
			queue.push_back(v);

			while (!queue.empty())
			{
				travel = false;
				v = queue.front();
				queue.pop_front();

				for (int i = 0; i < n; i++)
				{
					if (matrix[v][i] > 0 && visited[i] == false)
					{
						queue.push_back(i);
						distances.push_front(distance);
						visited[i] = true;
						travel = true;
					}
				}

				if (travel)
				{
					distance++;	//Every iteration of the loop moves all operations one unit further from the origin
				}
			}


			for (int i = 0; i < n; i++)
			{
				if (visited[i] == false)	//If the search failed to find any nodes, the graph is not connected
				{							//and -1 is returned to indicate
					return -1;
				}
			}

			return distances.front();	//return the latest-added distance, which is always the greatest
	}

	int Diameter()
	{
		int max = -1;
		int j;

		for (int i = 0; i < n; i++)		//For each node, call BFS and return the greatest distance value that is returned
		{
			j = this->DiameterBFS(i);
			if (j > max) {
				max = j;
			}

			if (j == -1)
			{
				return j;	//If any call to BFS returns -1, the graph is not connected and Diameter is reported as -1
			}
		}

		return max;
	}

	int AllVisited()	//Simple helper function that returns whether or not all nodes have been marked as visited
	{					//If not, it returns the first node in the array that has not been visited. Otherwise, -1.
		for (int i = 0; i < n; i++)
		{
			if (visited[i] == false)
			{
				return i;
			}
		}

		return -1;
	}

	void Components()
	{
		int v = 0;

		for (int i = 0; i < n; i++)
		{
			visited[i] = false;
		}

		while (this->AllVisited() != -1)	//As long as all nodes have not been visited, BFS is called to print
		{									//each component of the graph until all nodes are visited and therefore all
			BFS(v);							//components have been printed
			v = this->AllVisited();
		}
	}
};

int main()
{
	int nodes;
	int x;
	int y;
	cout << "Number of nodes: ";	//Accept user input for number of nodes
	cin >> nodes;

	Graph g(nodes);

	int max = nodes * (nodes - 1);	//Enforces maximum number of possible edges to input

	for (int i = 0; i < max; i++)
	{
		cout << "Edge " << i + 1 << ": ";	//Accept edges one at a time, allowing for a single -1 to break
		cin >> x;
		if (x < 0)
		{
			break;
		}
		cin >> y;
		
		if (!g.Edge(x, y))
		{
			cout << "Invalid edge" << endl;
			i--;
		}
	}

	g.PrintGraph();
	cout << "Diameter: " << g.Diameter() << endl;	//Graph, Diameter, and Components are listed
	g.Components();
	return 0;
}