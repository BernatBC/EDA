#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int n;
  vector<string> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];
  int p;
  exahustive(v, p);
}
