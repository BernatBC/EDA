#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool is_in(const vector<char>& v, char c) {
  for (int i = 0; i < v.size(); ++i) if (v[i] == c) return true;
  return false;
}

void exhaustive(string a, string b, vector<char> v) {
  if (v[v.size() - 1] != ' ') {
    for (int i = 0; i < v.size(); ++i) cout << v[i];
    cout << endl;
    return;
  }
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] == ' ') {
      if (i%2 == 0) {
        for (int j = 0; j < a.size(); ++j) {
          if (not is_in(v, a[j])) {
            v[i] = a[j];
            exhaustive(a, b, v);
          }
        }
      }
      else {
        for (int j = 0; j < b.size(); ++j) {
          if (not is_in(v, b[j])) {
            v[i] = b[j];
            exhaustive(a, b, v);
          }
        }
      }
      return;
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<char> v(2*n, ' ');
  string a, b;
  cin >> a >> b;
  exhaustive(a, b, v);
}
