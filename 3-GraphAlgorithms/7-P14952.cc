#include <iostream>
#include <queue>
using namespace std;

typedef vector<vector<int>> matriu;

int main() {
  int n, m;
  while (cin >> n >> m) {
    matriu mat(n);
    vector<int> grau(n, 0);
    for (int i = 0; i < m; ++i) {
      int x, y;
      cin >> x >> y;
      mat[x].push_back(y);
      ++grau[y];
    }
    priority_queue<int> q;
    for (int x = 0; x < n; ++x) {
      if (grau[x] == 0) q.push(-x);
    }
    bool primer = true;
    while(not q.empty()) {
      int x = -q.top();
      q.pop();
      if (primer) primer = false;
      else cout << " ";
      cout << x;
      for (int y : mat[x]) {
        if (--grau[y] == 0) q.push(-y);
      }
    }
    cout << endl;
  }
}
