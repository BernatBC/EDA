#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void exahustive(const vector<int>& v, vector<bool>& num, int s, int k, bool& sol, int p) {
  if (not sol and k == s and p == v.size()) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < v.size(); ++i) {
      if (num[i] or v[i] == 0) {
        if (first) first = false;
        else cout << ",";
        cout << v[i];
      }
    }
    cout << "}" << endl;
    sol = true;
  }
  else if (not sol and p < v.size()) {
    num[p] = true;
    exahustive(v, num, s, k + v[p], sol, p + 1);
    num[p] = false;
    exahustive(v, num, s, k, sol, p + 1);
  }
}

bool comp(const int& a, const int& b) {
  return a > b;
}

int main() {
  int s, n;
  cin >> s >> n;
  vector<int> v(n);
  vector<bool> num(n, false);
  for (int i = 0; i < n; ++i) cin >> v[i];
  sort(v.begin(), v.end(), comp);
  bool sol = false;
  exahustive(v, num, s, 0, sol, 0);
  if (not sol) cout << "no solution" << endl;
}
