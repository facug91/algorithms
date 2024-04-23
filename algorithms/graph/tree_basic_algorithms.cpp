
#include <bits/stdc++.h>

using namespace std;

void findMiddleVertexes(const vector<vector<int>>& tree, vector<int>& middlePoints) {
	if (tree.empty()) {
		middlePoints.clear();
		return;
	}
	if (tree.size() == 1) {
		middlePoints = { 0 };
		return;
	}
	vector<int> degree(tree.size(), 0);
	queue<int> q;
	for (int i = 0; i < tree.size(); i++) {
		degree[i] = tree[i].size();
		if (degree[i] == 1) q.push(i);
	}
	while (!q.empty()) {
		int size = q.size();
		middlePoints.clear();
		for (int i = 0; i < size; i++) {
			int u = q.front(); q.pop();
			middlePoints.push_back(u);
			for (const int v: tree[u]) {
				degree[v]--;
				if (degree[v] == 1)
					q.push(v);
			}
		}
	}
}

int diameter(const vector<vector<int>>& tree) {
	if (tree.empty()) return 0;
	vector<int> depth;
	function<int(int, int)> dfs;
	dfs = [&tree, &depth, &dfs](int u, int d) -> int {
		depth[u] = d;
		int ans = d;
		for (int v : tree[u])
			if (depth[v] == -1)
				ans = max(ans, dfs(v, d+1));
		return ans;
	};
	depth.assign(tree.size(), -1);
	dfs(0, 0);
	int e = max_element(depth.begin(), depth.end()) - depth.begin();
	depth.assign(tree.size(), -1);
	dfs(e, 0);
	return *max_element(depth.begin(), depth.end()) + 1;
}

int main() {
	vector<vector<int>> tree{
			{ 3 },
			{ 3 },
			{ 3 },
			{ 0, 1, 2, 3, 4 },
			{ 3, 5 },
			{ 4 }
	};
	vector<int> middleVertexes;
	findMiddleVertexes(tree, middleVertexes);
	int d = diameter(tree);
	cout << "Tree has diameter " << d << " and middle vertexes:";
	for (int v: middleVertexes) cout << " " << v;
	cout << endl;
}
