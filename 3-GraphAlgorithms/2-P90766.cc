#include <iostream>
#include <vector>
#include <iostream>
using namespace std;
typedef vector<vector<char>> matriu;

int dfs(int x, int y, matriu& m) {
  int n = 0;
  if (m[x][y] == 't') {
    m[x][y] = 'X';
    ++n;
  }
  m[x][y] = 'X';
  if (m[x + 1][y] != 'X') {
    n += dfs(x + 1, y, m);
  }
  if (m[x - 1][y] != 'X') {
    n += dfs(x - 1, y, m);
  }
  if (m[x][y + 1] != 'X') {
    n += dfs(x, y + 1, m);
  }
  if (m[x][y - 1] != 'X') {
    n += dfs(x, y - 1, m);
  }
  return n;
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
  cout << dfs(d, c, m) << endl;
}
