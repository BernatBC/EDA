#include <iostream>
#include <string>
using namespace std;

void backtracking(string s, int n, int c, int h) {
  if (s.size() == n) cout << s << endl;
  else {
    if (c > 0) backtracking(s + 'b', n, c - 1, h + 1);
    if (h > 0) backtracking(s + 's', n, c + 1, h - 1);
  }
}

int main() {
  int n, c;
  cin >> n >> c;
  string s = "";
  backtracking(s, n, c, 0);
}
