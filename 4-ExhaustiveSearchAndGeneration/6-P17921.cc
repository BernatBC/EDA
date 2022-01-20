#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<bool>> mat;

void write(const mat& m) {
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m.size(); ++j) {
      if (m[i][j]) cout << "Q";
      else cout << ".";
    }
    cout << endl;
  }
  cout << endl;
}

void exhaustive(mat& m, vector<bool>& row, vector<bool>& col, vector<bool>& diag1, vector<bool>& diag2, const int n, int q, int pos) {
  if (q == n) {
    write(m);
    return;
  }
  for (int i = 0; i < n; ++i) {
    if (not col[i] and not row[pos] and not diag1[pos + i] and not diag2[pos - i + n - 1]) {
      m[pos][i] = true;
      row[pos] = true;
      col[i] = true;
      diag1[pos + i] = true;
      diag2[pos - i + n - 1] = true;
      exhaustive(m, row, col, diag1, diag2, n, q + 1, pos + 1);
      row[pos] = false;
      col[i] = false;
      diag1[pos + i] = false;
      diag2[pos - i + n - 1] = false;
      m[pos][i] = false;
    }
  }
}

int main() {
  int n;
  cin >> n;
  mat m(n, vector<bool>(n, false));
  vector<bool> row(n, false);
  vector<bool> col(n, false);
  vector<bool> diag1(2*n - 1, false);
  vector<bool> diag2(2*n - 1, false);
  exhaustive(m, row, col, diag1, diag2, n, 0, 0);
}
