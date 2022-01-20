#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool dos_colors_dfs(vector<vector<int>>& v, vector<int>& c, int color, int x) {
  if (c[x] == 0) {
    c[x] = color;
    for (int i = 0; i < v[x].size(); ++i) {
      if (not dos_colors_dfs(v, c, color + 1, v[x][i])) return false;
    }
    return true;
  }
  else if (c[x]%2 != color%2) return false;
  return true;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    vector<int> c(n, 0);
    vector<vector<int>> v(n);
    int a, b;
    for (int i = 0; i < m; ++i) {
      cin >> a >> b;
      v[a].push_back(b);
      v[b].push_back(a);
    }
    int i = 0;
    bool dos = true;
    while (dos and i < v.size()) {
      if (c[i] == 0 and not dos_colors_dfs(v, c, 1, i)) dos = false;
      ++i;
    }
    if (dos) cout << "yes" << endl;
    else cout << "no" << endl;
  }
}
