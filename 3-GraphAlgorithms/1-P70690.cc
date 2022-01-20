#include <iostream>
#include <vector>
#include <iostream>
using namespace std;
typedef vector<vector<char>> matriu;

bool dfs(int x, int y, matriu& m) {
  if (m[x][y] == 't') return true;
  m[x][y] = 'X';
  if (m[x + 1][y] != 'X') {
    bool b = dfs(x + 1, y, m);
    if (b) return true;
  }
  if (m[x - 1][y] != 'X') {
    bool b = dfs(x - 1, y, m);
    if (b) return true;
  }
  if (m[x][y + 1] != 'X') {
    bool b = dfs(x, y + 1, m);
    if (b) return true;
  }
  if (m[x][y - 1] != 'X') {
    bool b = dfs(x, y - 1, m);
    if (b) return true;
  }
  return false;
}

int main() {
  int a, b;
  cin >> a >> b;
  matriu m(b + 2, vector<char>(a + 2, 'X'));
  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < b; ++j) cin >> m[j + 1][i + 1];
  }
  /*for (int i = 0; i < a + 2; ++i) {
    for (int j = 0; j < b + 2; ++j) cout << m[j][i];
    cout << endl;
  }*/
  int c, d;
  cin >> c >> d;
  if (dfs(d, c, m)) cout << "yes" << endl;
  else cout << "no" << endl;
}
