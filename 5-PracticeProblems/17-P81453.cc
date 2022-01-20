#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef vector<vector<int>> Mat;

void dijkstra(const Mat& mat) {
  vector<int> steps(mat.size(), 100000);
  vector<int> parent(mat.size());
  priority_queue<pair<int, int>> q;
  q.push(make_pair(0,0));
  steps[0] = 1;
  while (not q.empty()) {
    pair<int, int> p = q.top();
    int x = -p.second;
    q.pop();
    for (int i = 0; i < mat[x].size(); ++i) {
      int y = mat[x][i];
      int s = steps[x] + 1;
      if (s < steps[y]) {
        steps[y] = s;
        parent[y] = x;
        q.push(make_pair(-s, -y));
      }
      else if (s == steps[y] and parent[y] > x) {
        parent[y] = x;
        q.push(make_pair(-s, -y));
      }
    }
  }
  stack<int> st;
  int x = mat.size() - 1;
  while (x != 0) {
    st.push(x);
    x = parent[x];
  }
  cout << 0;
  while (not st.empty()) {
    cout << " " << st.top();
    st.pop();
  }
  cout << endl;
  return;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    Mat mat(n);
    for (int i = 0; i < m; ++i) {
      int a, b;
      cin >> a >> b;
      mat[a].push_back(b);
    }
    dijkstra(mat);
  }
}
