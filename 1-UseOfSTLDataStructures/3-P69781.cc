#include <iostream>
#include <map>
using namespace std;

int long_cicle(int x, int y, int n) {
  int l = 0;
  map<int, int> s;
  while (s.find(n) == s.end()) {
    s[n] = l;
    if (n%2 == 0) n = n/2 + x;
    else n = 3*n + y;
    if (n > 100000000) return n;
    ++l;
  }
  return l - s[n];
}

int main() {
  int x, y, n;
  while (cin >> x >> y >> n) {
    cout << long_cicle(x, y, n) << endl;
  }
}
