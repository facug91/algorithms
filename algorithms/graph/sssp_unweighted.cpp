#include <bits/stdc++.h>

using namespace std;

// Single Source Shortest Path unweighted
void shortestPath(const vector<vector<int>>& graph, int src, vector<int>& dist, vector<bool>& vis) {
	int n = graph.size();
	dist.assign(n, -1);
	vis.assign(n, false);
	queue<int> q;
	q.push(src);
	vis[src] = true;
	dist[src] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		int w = dist[u];
		for (int v: graph[u]) {
			if (!vis[v]) {
				vis[v] = true;
				dist[v] = w + 1;
				q.push(v);
			}
		}
	}
}

int main() {
	int vertices = 6;
	vector<vector<int>> graph{
			{ 2, 1 },
			{ 0, 3, 4 },
			{ 0, 3 },
			{ 2, 1, 5 },
			{ 1, 5 },
			{ 3, 1, 4 }
	};
	vector<int> dist;
	vector<bool> vis;
	shortestPath(graph, 0, dist, vis);
	for (int i = 1; i < vertices; i++)
		cout << "Minimum distance from 0 to " << i << ": " << dist[i] << endl;
}