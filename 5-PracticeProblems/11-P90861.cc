#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<queue<string>> Mat;

int main() {
  int n;
  cin >> n;
  Mat m(n);
  for (int i = -1; i < n; ++i) {
    string s;
    getline(cin, s);
    istringstream ss(s);
    string k;
    while (ss >> k) m[i].push(k);
  }
  string s;
  vector<string> v;
  while (cin >> s) {
    if (s == "SURT") {
      int k;
      cin >> k;
      if (k >= 1 and k <= n and not m[k - 1].empty()) {
        v.push_back(m[k - 1].front());
        m[k - 1].pop();
      }
    }
    else {
      string name;
      cin >> name;
      int k;
      cin >> k;
      if (k >= 1 and k <= n) m[k - 1].push(name);
    }
  }
  cout << "SORTIDES" << endl;
  cout << "--------" << endl;
  for (int i = 0; i < v.size(); ++i) cout << v[i] << endl;
  cout << endl;
  cout << "CONTINGUTS FINALS" << endl;
  cout << "-----------------" << endl;
  for (int i = 0; i < n; ++i) {
    cout << "cua " << i + 1 << ":";
    while (not m[i].empty()) {
      cout << " " << m[i].front();
      m[i].pop();
    }
    cout << endl;
  }
}
