
#include <bits/stdc++.h>

using namespace std;

struct edge {
	int dest;
	int weight;
};

/**
 * @tparam WeightType int, long long, double, etc.
 * @param[in] graph Each position i in the graph represents a vertex, with its list of edges
 * @param[in] root Start vertex
 * @param[out] dist dist[i] is the min distance from root to i
 * @param[out] vis vis[i] is true if vertex i can be visited by root
 */
template<typename WeightType = int>
void dijkstra(const vector<vector<edge>>& graph, int root, vector<int>& dist, vector<bool>& vis) {
	int vertices = graph.size();
	const WeightType INF = std::numeric_limits<WeightType>::max();
	dist.assign(vertices, INF);
	vis.assign(vertices, false);
	priority_queue<tuple<WeightType, int>, vector<tuple<WeightType, int>>, greater<>> pq;                    // C++17
//	priority_queue<pair<WeightType, int>, vector<pair<WeightType, int>>, greater<pair<WeightType, int>>> pq; // C++11
	dist[root] = 0;
	pq.push({ 0, root });
	while (!pq.empty()) {
		auto [d, u] = pq.top(); // C++17
//		auto curr = pq.top();   // C++11
//		int d = curr.first;     // C++11
//		int u = curr.second;    // C++11
		pq.pop();
		if (!vis[u]) {
			vis[u] = true;
			for (int i = 0; i < graph[u].size(); i++) {
				edge t = graph[u][i];
				if (dist[t.dest] > dist[u] + t.weight) {
					dist[t.dest] = dist[u] + t.weight;
					pq.push({ dist[t.dest], t.dest });
				}
			}
		}
	}
}

int main() {
	int vertices = 6;
	vector<vector<edge>> graph{
			{{ 2, 1 }, { 1, 4 }},
			{{ 0, 4 }, { 3, 2 }, { 5, 1 }, { 4, 3 }},
			{{ 0, 1 }, { 3, 1 }},
			{{ 2, 1 }, { 1, 2 }, { 5, 3 }},
			{{ 1, 3 }, { 5, 2 }},
			{{ 3, 3 }, { 1, 1 }, { 4, 2 }}
	};
	vector<int> dist;
	vector<bool> vis;
	dijkstra(graph, 0, dist, vis);
	for (int i = 1; i < vertices; i++)
		cout << "Minimum distance from 0 to " << i << ": " << dist[i] << endl;
}