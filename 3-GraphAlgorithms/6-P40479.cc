#include <iostream>
#include <vector>
#include <iostream>
using namespace std;
typedef vector<vector<pair<char, bool>>> matriu;

void pinta_dfs(matriu& m, int x, int y, char c) {
  if (m[y][x].first == '.') {
    m[y][x].first = c;
    pinta_dfs(m, x, y + 1, c);
    pinta_dfs(m, x, y - 1, c);
    pinta_dfs(m, x + 1, y, c);
    pinta_dfs(m, x - 1, y, c);
  }
}

int main() {
  int a, b;
  while (cin >> a >> b) {
    matriu m(b, vector<pair<char, bool>>(a));
    for (int i = 0; i < a; ++i) {
      for (int j = 0; j < b; ++j) {
        cin >> m[j][i].first;
        if (m[j][i].first != '#' and m[j][i].first != '.') m[j][i].second = true;
        else m[j][i].second = false;
      }
    }
    for (int i = 0; i < a; ++i) {
      for (int j = 0; j < b; ++j) {
        if (m[j][i].second) {
          char c = m[j][i].first;
          m[j][i].first = '.';
          pinta_dfs(m, i, j, c);
        }
      }
    }
    for (int i = 0; i < a; ++i) {
      for (int j = 0; j < b; ++j) cout << m[j][i].first;
      cout << endl;
    }
    cout << endl;
  }
}
