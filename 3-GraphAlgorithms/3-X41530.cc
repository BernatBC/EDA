#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool cicles_dfs (vector<vector<int>>& v, set<int>& no_visitats, int x, int prev) {
  if (no_visitats.find(x) != no_visitats.end()) {
    no_visitats.erase(x);
    for (int i = 0; i < v[x].size(); ++i) {
      if (prev != v[x][i] and cicles_dfs(v, no_visitats, v[x][i], x)) return true;
    }
    return false;
  }
  return true;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    vector<vector<int>> v(n);
    set<int> no_visitats;
    for (int i = 0; i < n; ++i) no_visitats.insert(i);

    int a, b;
    for (int i = 0; i < m; ++i) {
      cin >> a >> b;
      v[a].push_back(b);
      v[b].push_back(a);
    }

    int arbres = 0;
    bool cicles = false;
    while(not cicles and not no_visitats.empty()) {
      auto it = no_visitats.begin();
      if (not cicles_dfs(v, no_visitats, *it, *it)) ++arbres;
      else cicles = true;
    }
    if (cicles) cout << "no" << endl;
    else cout << arbres << endl;
  }
}
