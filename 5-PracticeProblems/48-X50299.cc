#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<pair<int, int>>> Mat;

int dijkstra(Mat& mat) {
  priority_queue<pair<int, int>> q;
  vector<int> visited(mat.size(), false);
  q.push(make_pair(0, 0));
  while (not q.empty()) {
    int c = -q.top().first;
    int node = q.top().second;
    q.pop();
    if (node == 1) return c;
    if (not visited[node]) {
      visited[node] = true;
      for (int i = 0; i < mat[node].size(); ++i) {
        int c2 = mat[node][i].first;
        if (c2 < c) c2 = c;
        q.push(make_pair(-c2, mat[node][i].second));
      }
    }
  }
  return -1;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    Mat mat(n);
    for (int i = 0; i < m; ++i) {
      int x, y, l;
      cin >> x >> y >> l;
      mat[x].push_back(make_pair(l, y));
    }
    cout << dijkstra(mat) << endl;
  }
}
