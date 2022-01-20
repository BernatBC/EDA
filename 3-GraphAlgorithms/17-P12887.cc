#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<pair<int,int>>> Mat;

void min_spanning_tree(const Mat& mat) {
  vector<bool> visited(mat.size(), false);
  priority_queue<pair<int,int>> q;
  for (int i = 0; i < mat[0].size(); ++i) q.push(make_pair(-mat[0][i].first, mat[0][i].second));
  int weight = 0;
  visited[0] = true;
  int nodes = 1;
  while (nodes < mat.size()) {
    pair<int, int> p = q.top();
    q.pop();
    if (not visited[p.second]) {
      weight += -p.first;
      ++nodes;
      visited[p.second] = true;
      for (int i = 0; i < mat[p.second].size(); ++i) q.push(make_pair(-mat[p.second][i].first, mat[p.second][i].second));
    }
  }
  cout << weight << endl;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    Mat mat(n);
    int u, v, w;
    for (int i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      mat[u - 1].push_back(make_pair(w, v - 1));
      mat[v - 1].push_back(make_pair(w, u - 1));
    }
    min_spanning_tree(mat);
  }
}
