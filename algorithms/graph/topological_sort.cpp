
#include <bits/stdc++.h>

using namespace std;

// Kahn's algorithm: calculates the lexicographic smallest topological sort
bool topologicalSort(const vector<vector<int>>& graph, vector<int>& ts) {
	vector<int> inDegree(graph.size(), 0);
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++)
			inDegree[graph[i][j]]++;
	}
	queue<int> q;
	for (int i = 0; i < graph.size(); i++)
		if (inDegree[i] == 0)
			q.push(i);
	ts.clear();
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		ts.push_back(u);
		for (int v: graph[u]) {
			inDegree[v]--;
			if (inDegree[v] == 0) q.push(v);
		}
	}
	return ts.size() == graph.size();
}

// Warning: O((2^n)*n)
void allTopologicalSorts(const vector<vector<int>>& graph, vector<vector<int>>& tss) {
	if (graph.empty()) {
		tss.clear();
		return;
	}
	vector<int> inDegree(graph.size(), 0);
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++)
			inDegree[graph[i][j]]++;
	}
	function<void(vector<int>&)> dfs;
	dfs = [&graph, &inDegree, &tss, &dfs](vector<int>& curr) -> void {
		if (curr.size() == graph.size()) {
			tss.push_back(curr);
			return;
		}
		for (int u = 0; u < inDegree.size(); u++)
			if (inDegree[u] == 0) {
				inDegree[u]--;
				curr.push_back(u);
				for (int v: graph[u])
					inDegree[v]--;
				dfs(curr);
				for (int v: graph[u])
					inDegree[v]++;
				curr.pop_back();
				inDegree[u]++;
			}
	};
	vector<int> curr;
	dfs(curr);
}

int main() {
	vector<vector<int>> graph{
			{ 1, 2, 4 },
			{},
			{},
			{ 4 },
			{ 2 }
	};
	vector<vector<int>> tss(1);
	topologicalSort(graph, tss[0]);
	cout << "Topological sort using Kahn's algorithm:" << endl;
	for (int i = 0; i < tss[0].size(); i++)
		cout << tss[0][i] << " ";
	cout << endl << endl;

	allTopologicalSorts(graph, tss);
	cout << "All possible topological sorts:" << endl;
	for (int i = 0; i < tss.size(); ++i) {
		for (int j = 0; j < tss[i].size(); ++j)
			cout << tss[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}