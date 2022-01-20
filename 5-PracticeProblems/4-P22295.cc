#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<char>> Mat;
typedef vector<vector<bool>> Matb;

void exahustive(const Mat& ma, Matb& mb, int i1, int j1, int i2, int j2, string s) {
  if (i1 == i2 and j1 == j2)  cout << s << endl;
  else {
    if (i1 > 0 and not mb[i1 - 1][j1]) {
      mb[i1 - 1][j1] = true;
      s += ma[i1 - 1][j1];
      exahustive(ma, mb, i1 - 1, j1, i2, j2, s);
      mb[i1 - 1][j1] = false;
      s.pop_back();
    }
    if (i1 < ma.size() - 1 and not mb[i1 + 1][j1]) {
      mb[i1 + 1][j1] = true;
      s += ma[i1 + 1][j1];
      exahustive(ma, mb, i1 + 1, j1, i2, j2, s);
      mb[i1 + 1][j1] = false;
      s.pop_back();
    }
    if (j1 > 0 and not mb[i1][j1 - 1]) {
      mb[i1][j1 - 1] = true;
      s += ma[i1][j1 - 1];
      exahustive(ma, mb, i1, j1 - 1, i2, j2, s);
      mb[i1][j1 - 1] = false;
      s.pop_back();
    }
    if (j1 < ma[0].size() - 1 and not mb[i1][j1 + 1]) {
      mb[i1][j1 + 1] = true;
      s += ma[i1][j1 + 1];
      exahustive(ma, mb, i1, j1 + 1, i2, j2, s);
      mb[i1][j1 + 1] = false;
      s.pop_back();
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  Mat ma(n, vector<char>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) cin >> ma[i][j];
  }
  int i1, i2, j1, j2;
  cin >> i1 >> j1 >> i2 >> j2;
  Matb mb(n, vector<bool>(m, false));
  string s = "";
  s += ma[i1][j1];
  mb[i1][j1] = true;
  exahustive(ma, mb, i1, j1, i2, j2, s);
}
