#include <iostream>
#include <string>
using namespace std;

void exahustive(string s, int n) {
  if (n == s.size()) cout << s << endl;
  else {
    exahustive(s + 'A', n);
    exahustive(s + 'C', n);
    exahustive(s + 'G', n);
    exahustive(s + 'T', n);
  }
}

int main() {
  int n;
  cin >> n;
  string s = "";
  exahustive(s, n);
}
