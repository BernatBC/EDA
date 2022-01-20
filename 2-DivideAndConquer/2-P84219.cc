#include <iostream>
#include <vector>
using namespace std;

int i_first_occurrence(int e, int d, double x, const vector<double>& v) {
  if (e > d) return -1;
  int m = (e + d)/2;
  if (v[e] == x) return e;
  if (x < v[m]) return i_first_occurrence(e, m - 1, x, v);
  if (x > v[m]) return i_first_occurrence(m + 1, d, x, v);
  if (m > 0 and v[m - 1] == x) return i_first_occurrence(e, m - 1, x, v);
  return m;
}

int first_occurrence(double x, const vector<double>& v) {
  return i_first_occurrence(0, v.size() - 1, x, v);
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
  cout << first_occurrence(k, v);
}*/
