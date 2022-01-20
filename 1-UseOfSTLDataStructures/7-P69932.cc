#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
  string s;
  vector<int> v;
  while (getline(cin, s)) {
    v.clear();
    istringstream iss;
    iss.str(s);
    int n;
    while (iss >> n) v.push_back(n);
    if (v.size() != 0) {
      sort(v.begin(), v.end());
      int c = 1;
      n = v[0];
      for (int i = 0; i < v.size(); ++i) {
        if (v[i] > n and n%2 != v[i]%2) {
          n = v[i];
          ++c;
        }
      }
      cout << c << endl;
    }
    else cout << 0 << endl;


  }
}
