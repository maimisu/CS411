// Malvika Shriwas
// Ford-Fulkerson.cpp
// Started: December 13, 2020
// Finished: December 14, 2020

// C++ program that implements the Ford-Fulkerson Algorithm for Maximum Flow 
// Referenced: https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/

#include <queue>
#include <iostream>
#include <vector>

using namespace std;

// BFS loop
int bfs(int source, int sink, vector<int>& parent, vector<vector<int>>& resGraph) {
	fill(parent.begin(), parent.end(), -1);
	int V = resGraph.size();
	parent[source] = -1;
	queue<pair<int, int>> q;
	q.push({ source, INT_MAX });

	while (!q.empty()) {
		int u = q.front().first;
		int capacity = q.front().second;
		q.pop();
		for (int av = 0; av < V; av++) {
			if (u != av && parent[av] == -1 && resGraph[u][av] != 0) {
				parent[av] = u;
				int minCapacity = min(capacity, resGraph[u][av]);
				if (av == sink)
					return minCapacity;
				q.push({ av, minCapacity });
			}
		}
	}
	return 0;
}

// Ford-Fulkerson function
int ford(vector<vector<int>>& graph, int source, int sink) {
	vector<int> parent(graph.size(), -1);
	vector<vector<int>> resGraph = graph;
	int minCapacity = 0;
	int maxFlow = 0; 
	while (minCapacity = bfs(source, sink, parent, resGraph)) {
		maxFlow += minCapacity;
		int u = sink;
		while (u != source) {
			int v = parent[u];
			resGraph[u][v] += minCapacity;
			resGraph[v][u] -= minCapacity;
			u = v;
		}
	}
	return maxFlow;
}

void addEdge(vector<vector<int>>& graph,
	int u, int v, int w)
{
	graph[u][v] = w;
}

// Driver program to test the above functions

int main()
{
	// Number of vertices in given graph
	int V = 6; 
	vector<vector<int>> graph(V, vector<int>(V, 0));

	// Graph taken from the geeksforgeeks
	// Maximum flow should be 23
	addEdge(graph, 0, 1, 16);
	addEdge(graph, 0, 2, 13);
	addEdge(graph, 1, 2, 10);
	addEdge(graph, 1, 3, 12);
	addEdge(graph, 2, 1, 4);
	addEdge(graph, 2, 4, 14);
	addEdge(graph, 3, 2, 9);
	addEdge(graph, 3, 5, 20); 
	addEdge(graph, 4, 3, 7);
	addEdge(graph, 4, 5, 4);

/*
	// Another graph with different weights
	// Maximum flow should be 19
	addEdge(graph, 0, 1, 10);
	addEdge(graph, 0, 2, 9);
	addEdge(graph, 1, 2, 2);
	addEdge(graph, 1, 3, 4);
	addEdge(graph, 1, 4, 8);
	addEdge(graph, 2, 4, 9);
	addEdge(graph, 3, 5, 10);
	addEdge(graph, 4, 3, 6);
	addEdge(graph, 4, 5, 10);

*/

	cout << "Maximum Flow of the given graph is " << ford(graph, 0, 5) << "." << endl;
	return 0;
}
