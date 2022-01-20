#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<int>> Mat;

int num(const Mat& mat, int u, int v) {
  queue<int> q;
  vector<int> visited(mat.size());
  q.push(u);
  int n = 0;
  while (not q.empty()) {
    if ()
  }
}

int main() {
    int n, u, v, m;
    while (cin >> n >> u >> v >> m) {
      Mat mat(n);
      for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        mat[a].push_back(b);
      }
      cout << num(mat, u, v);
    }
}
