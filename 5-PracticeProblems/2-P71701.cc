#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<bool>> Mat;

void wrtie(Mat& m) {
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < m.size(); ++j) {
      if (m[i][j]) cout << "K";
      else cout << ".";
    }
    cout << endl;
  }
  cout << "----------" << endl;
}

bool is_free(const Mat& m, int i, int j) {
  if (i >= 1 and m[i - 1][j]) return false;
  if (j >= 1 and m[i][j - 1]) return false;
  if (i < m.size() - 1 and m[i + 1][j]) return false;
  if (j < m.size() - 1 and m[i][j + 1]) return false;
  if (i >= 1 and j >= 1 and m[i - 1][j - 1]) return false;
  if (i < m.size() - 1 and j >= 1 and m[i + 1][j - 1]) return false;
  if (i >= 1 and j < m.size() - 1 and m[i - 1][j + 1]) return false;
  if (i < m.size() - 1 and j < m.size() - 1 and m[i + 1][j + 1]) return false;
  return true;
}

void exahustive(Mat& m, int r, int k, int p) {
  if (r == k) wrtie(m);
  else {
    for (int i = p/m.size(); i < m.size(); ++i) {
      for (int j = 0; j < m.size(); ++j) {
        if (i == p and j == 0) j = p%m.size();
        if (not m[i][j] and is_free(m, i, j)) {
          m[i][j] = true;
          exahustive(m, r, k + 1, i*m.size() + j + 1);
          m[i][j] = false;
          exahustive(m, r, k, i*m.size() + j + 1);
        }
      }
    }
  }
}

int main() {
  int n, r;
  cin >> n >> r;
  Mat m(n, vector<bool>(n, false));
  exahustive(m, r, 0, 0);
}
