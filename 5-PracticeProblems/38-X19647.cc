#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<pair<int,int>>> Mat;

void dijkstra(const Mat& mat, const vector<int>& cost, int a, int b) {
  priority_queue<pair<int,int>> q;
  vector<int> visited(mat.size());
  q.push(make_pair(0, a));
  bool first = true;
  while (not q.empty()) {
    int c = -q.top().first;
    int node = q.top().second;
    q.pop();
    if (node == b) {
      if (first) cout << "c(" << a << "," << b << ") = " << 0 << endl;
      else cout << "c(" << a << "," << b << ") = " << c - cost[b] << endl;
      return;
    }
    first = false;
    if (not visited[node]) {
      visited[node] = true;
      for (int i = 0; i < mat[node].size(); ++i) {
        q.push(make_pair(-c - cost[mat[node][i].second] - mat[node][i].first, mat[node][i].second));
      }
    }
  }
  cout << "c(" << a << "," << b << ") = +oo" << endl;
}

int main() {
  int n, m;
  cin >> n >> m;
  Mat mat(n);
  vector<int> cost(n);
  for (int i = 0; i < n; ++i) cin >> cost[i];
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    mat[a].push_back(make_pair(c, b));
    mat[b].push_back(make_pair(c, a));
  }
  int a, b;
  while (cin >> a >> b) dijkstra(mat, cost, a, b);
}
