#include <iostream>
#include <vector>
using namespace std;

bool is_in(vector<int> v, int k) {
  for (int i = 0; i < v.size(); ++i) if (v[i] == k) return true;
  return false;
}

void exhaustive(vector<int> v) {
  if (v[v.size() - 1] != 0) {
    for (int i = 0; i < v.size(); ++i) {
      if (i == 0) cout << "(";
      else cout << ",";
      cout << v[i];
    }
    cout << ")" << endl;
    return;
  }
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] == 0) {
      for (int j = 1; j <= v.size(); ++j) {
        if (not is_in(v, j)) {
          v[i] = j;
          exhaustive(v);
        }
      }
      return;
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<int> v(n, 0);
  exhaustive(v);
}
