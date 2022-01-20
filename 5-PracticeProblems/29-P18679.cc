#include <iostream>
#include <vector>
using namespace std;

void backtracking(const vector<int>& v, int n, int k, int p) {
  if (p == v.size()) cout << k << endl;
  else {
    if (k + v[p] <= n/2) backtracking(v, n, k + v[p], p + 1);
    if (k - v[p] >= -n/2) backtracking(v, n, k - v[p], p + 1);
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> v(m);
  for (int i = 0; i < m; ++i) cin >> v[i];
  backtracking(v, n, 0, 0);
}
