#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<pair<bool, bool>> Vec;

void write(const vector<int>& v, Vec& m, int value) {
  cout << value << " = ";
  bool first = true;
  for (int i = 0; i < v.size(); ++i) {
    if (m[i].first) {
      if (not first) cout << " + " ;
      cout << v[i];
      first = false;
    }
    if (m[i].second) {
      if (not first) cout << " + " ;
      cout << v[i] << 'p';
      first = false;
    }
  }
  cout << endl;
}

void exhaustive(int x, const vector<int>& v, Vec& m, int value, int pos, int& k) {
  if (value == x) ++k;
  else if (pos < v.size() and value < x) {
    m[pos].first = true;
    m[pos].second = true;
    exhaustive(x, v, m, value + 2*v[pos], pos + 1, k);
    m[pos].second = false;
    exhaustive(x, v, m, value + v[pos], pos + 1, k);
    m[pos].first = false;
    m[pos].second = false;
    exhaustive(x, v, m, value, pos + 1, k);
  }
}

int main() {
  int x, n;
  while (cin >> x >> n) {
    vector<int> v(n);
    Vec m(n, make_pair(false, false));
    for (int i = 0; i < n; ++i) cin >> v[i];
    sort(v.begin(), v.end());
    int k = 0;
    exhaustive(x, v, m, 0, 0, k);
    cout << k << endl;
  }
}
