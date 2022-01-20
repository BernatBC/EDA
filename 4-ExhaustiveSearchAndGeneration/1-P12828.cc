#include <iostream>
#include <vector>
using namespace std;

void exhaustive(vector<int> v) {
  if (v[v.size() - 1] != -1) {
    for (int i = 0; i < v.size(); ++i) {
      if (i != 0) cout << " ";
      cout << v[i];
    }
    cout << endl;
    return;
  }
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] == -1) {
      v[i] = 0;
      exhaustive(v);
      v[i] = 1;
      exhaustive(v);
      return;
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<int> v(n, -1);
  exhaustive(v);
}
