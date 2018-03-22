#include <iostream>
#include <cstdlib>
#include <list>

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

		list<int> queue;
		int distance = 1;
		visited[v] = true;
		queue.push_back(v);

		cout << "Component: " << v << " ";
		while (!queue.empty())
		{
			v = queue.front();
			queue.pop_front();

			
			for (int i = 0; i < n; i++)
			{
				if (matrix[v][i] > 0 && visited[i] == false)
				{
					queue.push_back(i);
					cout << i << " ";
					visited[i] = true;
				}
			}

			
			distance++;
		}
		cout << endl;

	}

	int DiameterBFS(int v)
	{

		for (int i = 0; i < n; i++)
		{
			visited[i] = false;
		}

			list<int> queue;
			list<int> distances;
			int distance = 1;
			visited[v] = true;
			queue.push_back(v);

			while (!queue.empty())
			{
				v = queue.front();
				queue.pop_front();

				for (int i = 0; i < n; i++)
				{
					if (matrix[v][i] > 0 && visited[i] == false)
					{
						queue.push_back(i);
						distances.push_front(distance);
						visited[i] = true;
					}
				}

				distance++;
			}


			for (int i = 0; i < n; i++)
			{
				if (visited[i] == false)
				{
					return -1;
				}
			}

			return distances.front();
	}

	int Diameter()
	{
		int max = -1;
		int j;

		for (int i = 0; i < n; i++)
		{
			j = this->DiameterBFS(i);
			if (j > max) {
				max = j;
			}

			if (j == -1)
			{
				return j;
			}
		}

		return max;
	}

	int AllVisited()
	{
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

		while (this->AllVisited() != -1)
		{
			BFS(v);
			v = this->AllVisited();
		}
	}
};

int main()
{
	int nodes;
	int x;
	int y;
	cout << "Number of nodes: ";
	cin >> nodes;

	Graph g(nodes);

	int max = nodes * (nodes - 1);

	for (int i = 0; i < max; i++)
	{
		cout << "Edge " << i + 1 << ": ";
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
	cout << "Diameter: " << g.Diameter() << endl;
	g.Components();
	return 0;
}