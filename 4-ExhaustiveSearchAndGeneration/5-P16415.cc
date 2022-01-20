#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<bool>> mat;

void exhaustive(mat& m, vector<bool>& row, vector<bool>& col, vector<bool>& diag1, vector<bool>& diag2, int& k, const int n, int q, int pos) {
  if (q == n) {
    ++k;
    return;
  }
  for (int i = 0; i < n; ++i) {
    if (not col[i] and not row[pos] and not diag1[pos + i] and not diag2[pos - i + n - 1]) {
      m[pos][i] = true;
      row[pos] = true;
      col[i] = true;
      diag1[pos + i] = true;
      diag2[pos - i + n - 1] = true;
      exhaustive(m, row, col, diag1, diag2, k, n, q + 1, pos + 1);
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
  int k = 0;
  mat m(n, vector<bool>(n, false));
  vector<bool> row(n, false);
  vector<bool> col(n, false);
  vector<bool> diag1(2*n - 1, false);
  vector<bool> diag2(2*n - 1, false);
  exhaustive(m, row, col, diag1, diag2, k, n, 0, 0);
  cout << k << endl;
}
