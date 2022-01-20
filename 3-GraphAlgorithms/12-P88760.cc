#include <iostream>
#include <vector>
#include <iostream>
#include <list>
using namespace std;
typedef vector<vector<char>> matriu;

struct casella {
  int x;
  int y;
  int d;
};

int distancia_bfs(matriu& m, int x, int y) {
  list<casella> per_visitar;
  int dmax = -1;
  casella p;
  p.x = x;
  p.y = y;
  p.d = 0;
  per_visitar.push_back(p);
  while (!per_visitar.empty()) {
    casella t = per_visitar.front();
    per_visitar.pop_front();
    //cout << "x: " << t.x << " y: " << t.y << " val: " << m[t.x][t.y] << " dist: " << t.d << endl;
    if (m[t.x][t.y] != 'X') {
      if (m[t.x][t.y] == 't') dmax = t.d;
      casella c;
      c.x = t.x + 1;
      c.y = t.y;
      c.d = t.d + 1;
      if (m[c.x][c.y] != 'X') per_visitar.push_back(c);
      c.x = t.x - 1;
      if (m[c.x][c.y] != 'X') per_visitar.push_back(c);
      c.x = t.x;
      c.y = t.y + 1;
      if (m[c.x][c.y] != 'X') per_visitar.push_back(c);
      c.y = t.y - 1;
      if (m[c.x][c.y] != 'X') per_visitar.push_back(c);
    }
    m[t.x][t.y] = 'X';
  }
  return dmax;
}

int main() {
  int a, b;
  cin >> a >> b;
  matriu m(b + 2, vector<char>(a + 2, 'X'));
  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < b; ++j) cin >> m[j + 1][i + 1];
  }
  int x, y;
  cin >> x >> y;
  int d = distancia_bfs(m, y, x);
  if (d == -1) cout << "no es pot arribar a cap tresor" << endl;
  else cout << "distancia maxima: " << d << endl;
}
