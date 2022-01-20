#include <iostream>
#include <vector>
using namespace std;

int i_fixed(vector<int>& v, int a, int e, int d) {
  if (e <= d) {
    int m = (e + d)/2;
    int f = v[m] + a;
    if (f == m + 1) {
      int p = i_fixed(v, a, e, m - 1);
      if (p != -1) return p;
      return m + 1;
    }
    if (f < m + 1) return i_fixed(v, a, m + 1, d);
    if (f > m + 1) return i_fixed(v, a, e, m - 1);
  }
  return -1;
}

int fixed(vector<int>& v, int a) {
  return i_fixed(v, a, 0, v.size() - 1);
}

int main() {
  int n;
  int seq = 1;
  while (cin >> n) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    cout << "Sequence #" << seq << endl;
    int n2, a;
    cin >> n2;
    for (int i = 0; i < n2; ++i) {
      cin >> a;
      int b = fixed(v, a);
      if (b == -1) cout << "no fixed point for " << a << endl;
      else cout << "fixed point for " << a << ": " << b << endl;
    }
    cout << endl;
    ++seq;
  }
}
