#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> Mat;

int main() {
  int n, m;
  while (cin >> n >> m) {
    Mar ma(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) cin >> ma[i][j];
    }
    int coins = 0;
  }
}
