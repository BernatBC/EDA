#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
  string paraula;
  cin >> paraula;
  set<string> s;
  bool first = true;
  auto it = s.begin();
  while (paraula != "END") {
    if (first) {
      it = s.insert(it, paraula);
      first = false;
    }
    else {
      if (s.find(paraula) == s.end()) s.insert(paraula);
      if (paraula < *it and s.size()%2 == 0) --it;
      else if (paraula > *it and s.size()%2 == 1) ++it;
    }
    cout << *it << endl;
    cin >> paraula;
  }
}
