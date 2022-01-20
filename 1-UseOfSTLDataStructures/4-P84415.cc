#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
  string opcio;
  map<string, int> m;
  while (cin >> opcio) {
    if (opcio == "minimum?") {
      if (m.begin() == m.end()) cout << "indefinite minimum" << endl;
      else cout << "minimum: " << m.begin()->first << ", " << m.begin()->second << " time(s)" << endl;
    }
    else if (opcio == "maximum?") {
      if (m.begin() == m.end()) cout << "indefinite maximum" << endl;
      else {
        auto it = m.end();
        --it;
        cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
      }
    }
    else if (opcio == "store") {
      string p;
      cin >> p;
      if (m.find(p) == m.end()) m.insert(make_pair(p, 1));
      else ++m[p];
    }
    else if (opcio == "delete") {
      string p;
      cin >> p;
      if (m.find(p) != m.end()) {
        --m[p];
        if (m[p] <= 0) m.erase(p);
      }
    }
  }
}
