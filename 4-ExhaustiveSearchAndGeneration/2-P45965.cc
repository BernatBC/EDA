#include <iostream>
#include <vector>
using namespace std;

void exhaustive(vector<int>& v, int u, int k, int pos) {
  if (k == u) {
    for (int i = 0; i < v.size(); ++i) {
      if (i != 0) cout << " ";
      cout << v[i];
    }
    cout << endl;
  }
  else if (pos < v.size() and k < u and v.size() - pos >= u - k) {
    exhaustive(v, u, k, pos + 1);
    v[pos] = 1;
    exhaustive(v, u, k + 1, pos + 1);
    v[pos] = 0;
  }
}

int main() {
  int n, u;
  cin >> n >> u;
  vector<int> v(n, 0);
  exhaustive(v, u, 0, 0);
}
