#include <iostream>
#include <cstdlib>
#include <list>

using namespace std;

class Graph
{
private:
	int n;
	int **matrix;
	bool *visited;

public:
	Graph(int n)
	{
		//n++;
		this->n = n;
		visited = new bool[n];
		matrix = new int*[n];

		for (int i = 0; i <= n; i++)
		{
			matrix[i] = new int[n];

			for (int j = 0; j <= n; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}

	bool Edge(int i, int j)
	{
		if (i > n || j > n || i < 0 || j < 0)
		{
			return false;
		}

		else
		{
			matrix[i][j] = 1;
			matrix[j][i] = 1;
			return true;
		}
	}

	void PrintGraph()
	{
		int i;
		int j;

		for (i = 0; i <= n; i++)
		{
			for (j = 0; j <= n; j++)
			{
				cout << matrix[i][j] << "  ";
			}

			cout << endl;
		}
	}

	void BFS()
	{
		int v;
		cout << "Starting node: ";
		cin >> v;

		for (int i = 0; i <= n; i++)
		{
			visited[i] = false;
		}

		list<int> queue;
		visited[v] = true;
		queue.push_back(v);


		while (!queue.empty())
		{
			v = queue.front();
			cout << v << " ";
			queue.pop_front();

			for (int i = 0; i <= n; i++)
			{
				if (matrix[v][i] > 0 && visited[i] == false)
				{
					queue.push_back(i);
					visited[i] = true;
				}
			}

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
	g.BFS();

	return 0;
}