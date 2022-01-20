#include <iostream>
#include <vector>
using namespace std;

bool i_resistant_search(int e, int d, double x, const vector<double>& v) {
  if (e > d) return false;
  int m = (e + d)/2;
  if (m != 0 and v[m - 1] == x) return true;
  if (m != v.size() - 1 and v[m + 1] == x) return true;
  if (x < v[m]) return i_resistant_search(e, m - 1, x, v);
  if (x > v[m]) return i_resistant_search(m + 1, d, x, v);
  return true;
}

bool resistant_search(double x, const vector<double>& v) {
  return i_resistant_search(0, v.size() - 1, x, v);
}
/*
int main() {
  int n;
  cin >> n;
  vector<double> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }
  double k;
  cin >> k;
  cout << resistant_search(k, v);
}*/
