#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<pair<int, int>>> matriu;

void dijkstra(matriu& mat, int n, int a, int b) {
  vector<int> dist(n, 10000000);
  vector<int> ways(n, 0);
  priority_queue<pair<int,int>> q;
  dist[a] = 0;
  ways[a] = 1;
  q.push(make_pair(0, a));
  while (not q.empty()) {
    pair<int,int> p = q.top();
    q.pop();
    int d = -p.first;
    int x = p.second;
    if (d == dist[x]) {
      if (x == b) {
        cout << "cost " << dist[b] << ", " << ways[b] << " way(s)" << endl;
        return;
      }
      for (pair<int,int> a : mat[x]) {
        int d2 = d + a.first;
        int y = a.second;
        if (d2 < dist[y]) {
          dist[y] = d2;
          ways[y] = ways[x];
          q.push(make_pair(-d2, y));
        }
        else if (dist[y] == d2) ways[y] += ways[x];
      }
    }
  }
  cout << "no path from " << a << " to " << b << endl;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    matriu mat(n);
    for (int i = 0; i < m; ++i) {
      int x, y, c;
      cin >> x >> y >> c;
      mat[x].push_back(make_pair(c, y));
    }
    int a, b;
    cin >> a >> b;
    dijkstra(mat, n, a, b);
  }
}
