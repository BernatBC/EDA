#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void exahustive(const vector<int>& v, vector<bool>& num, int s, int k, int p) {
  if (k == s and p == v.size()) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < v.size(); ++i) {
      if (num[i]) {
        if (first) first = false;
        else cout << ",";
        cout << v[i];
      }
    }
    cout << "}" << endl;
  }
  else if (p < v.size() and k <= s) {
    if (k + v[p] <= s) {
      num[p] = true;
      exahustive(v, num, s, k + v[p], p + 1);
      num[p] = false;
    }
    exahustive(v, num, s, k, p + 1);
  }
}

int main() {
  int s, n;
  cin >> s >> n;
  vector<int> v(n);
  vector<bool> num(n, false);
  for (int i = 0; i < n; ++i) cin >> v[i];
  exahustive(v, num, s, 0, 0);
}
