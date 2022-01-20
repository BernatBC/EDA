#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool is_in(vector<int> v, int k) {
  for (int i = 0; i < v.size(); ++i) if (v[i] == k) return true;
  return false;
}

void exhaustive(vector<int> v, const vector<string>& words) {
  if (v[v.size() - 1] != 0) {
    for (int i = 0; i < v.size(); ++i) {
      if (i == 0) cout << "(";
      else cout << ",";
      cout << words[v[i] - 1];
    }
    cout << ")" << endl;
    return;
  }
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] == 0) {
      for (int j = 1; j <= v.size(); ++j) {
        if (not is_in(v, j)) {
          v[i] = j;
          exhaustive(v, words);
        }
      }
      return;
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<string> words(n);
  for (int i = 0; i < n; ++i) cin >> words[i];
  vector<int> v(n, 0);
  exhaustive(v, words);
}
