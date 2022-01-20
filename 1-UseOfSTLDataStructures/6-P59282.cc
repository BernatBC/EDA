#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {

  cout.setf(ios::fixed);
  cout.precision(4);

  string opcio;
  map<int, int> m;
  int suma = 0;
  int n = 0;
  while (cin >> opcio) {
    if (opcio == "number") {
      int x;
      cin >> x;
      ++n;
      suma += x;
      if (m.find(x) == m.end()) m.insert(make_pair(x, 1));
      else ++m[x];
    }
    else if (opcio == "delete") {
      if (m.size() != 0) {
        --n;
        suma -= m.begin()->first;
        if (m.begin()->second == 1) m.erase(m.begin());
        else --m[m.begin()->first];
      }
    }
    if (n == 0) cout << "no elements" << endl;
    else {
      cout << "minimum: " << m.begin()->first << ", maximum: ";
      auto it = m.end();
      --it;
      cout << it->first << ", average: " << (double) suma/n << endl;
    }
  }
}
