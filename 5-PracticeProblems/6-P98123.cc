#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
  int n;
  cin >> n;
  set<int> s;
  string a;
  int j = 0;
  int min = 0;
  long long value = 0;
  while (cin >> a) {
    int k;
    cin >> k;
    if (a == "deixar") {
      s.insert(-k);
      if (j < n) {
        value += k;
        ++j;
        if (min == 0 or k < min) min = k;
      }
      else if (j == n and k > min) {
        value = 0;
        j = 0;
        auto it = s.begin();
        while (it != s.end() and j < n) {
          value -= *it;
          ++j;
          ++it;
        }
      }
    }
    else {
      s.erase(-k);
      value = 0;
      j = 0;
      auto it = s.begin();
      while (it != s.end() and j < n) {
        value -= *it;
        ++j;
        ++it;
      }
    }

    cout << value << endl;
  }
}
