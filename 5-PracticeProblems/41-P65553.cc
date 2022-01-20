#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
  int n;
  while (cin >> n) {
    int t = 0;
    map<string, int> m;
    for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      ++m[s];
      ++t;
    }
    int j;
    cin >> j;
    for (int i = 0; i < j; ++i) {
      string s;
      cin >> s;
      if (m[s] < t - m[s]) {
        ++m[s];
        ++t;
      }
    }
    auto it = m.begin();
    while (it != m.end()) {
      cout << it->first << " " << it->second << endl;
      ++it;
    }
    cout << "--------------------" << endl;
  }
}
