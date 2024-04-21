
#include <bits/stdc++.h>

using namespace std;

template<typename WeightType = int>
void floyd_warshall(vector<vector<WeightType>>& graph) {
	int n = graph.size();
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

template<typename WeightType = int>
void print(vector<vector<WeightType>>& graph, int padding = 5) {
	int n = graph.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << right << setw(padding) << graph[i][j];
		cout << endl;
	}
	cout << endl;
}

int main() {
	int n = 6;
	// Unused edges should be initialized with something about (max_int / 2)
	vector<vector<int>> graph(n, vector<int>(n, 1e9));
	// graph[i][i] is the distance between vertex i and itself
	for (int i=0; i < n; i++) graph[i][i] = 0;
	// This is the same node as in dijkstra.cpp
	graph[0][2] = 1, graph[0][1] = 4, graph[1][0] = 4, graph[1][3] = 2, graph[1][5] = 1, graph[1][4] = 3;
	graph[2][0] = 1, graph[2][3] = 1, graph[3][2] = 1, graph[3][1] = 2, graph[3][5] = 3, graph[4][1] = 3;
	graph[4][5] = 2, graph[5][3] = 3, graph[5][1] = 1, graph[5][4] = 2;

	floyd_warshall<int>(graph);
	print(graph);
}