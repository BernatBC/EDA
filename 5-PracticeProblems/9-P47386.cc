#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
  string s;
  set<string> sol;
  set<string> t;
  set<pair<int, int>> par;
  while (cin >> s) {
    if (s == "liats") {
      string a, b;
      if (t.find(a) == t.end()) {
        t.insert(a);
        if (t.find(b) == t.end()) {
          t.insert(b);
          if (a < b) par.insert(make_pair(a, b));
        }
        else {
          if (sol.find(b) != sol.end()) {
            sol.erase(b);
            if (a < b) par.insert(make_pair(a, b));
          }
          else {
            auto it = par.begin();
            bool found = false;
            while (not found and it != par.end()) {
              if (*it.first == b) {
                sol.insert(*it.second);
                *it.second = a;
              }
              else if (*it.second == b) {
                sol.insert(*it.first);
                *it.first = a;
              }
              ++it;
            }
          }
        }
      }
      else {
        if (t.find(b) == t.end()) {
          t.insert(b);
          if (sol.find(a) != sol.end()) {
            sol.erase(a);
            if (a < b) par.insert(make_pair(a, b));
          }
          else {
            auto it = par.begin();
            bool found = false;
            while (not found and it != par.end()) {
              if (*it.first == a) {
                sol.insert(*it.second);
                *it.second = b;
              }
              else if (*it.second == a) {
                sol.insert(*it.first);
                *it.first = b;
              }
              ++it;
            }
          }
        }
        else {

        }
      }
    }
    else {
      cout << "PARELLES:" << endl;
      auto it = par.begin();
      while (it != par.end()) {
        cout << *it.first << " " << *it.second << endl;
        ++it;
      }
      cout << "SOLS:" << endl;
      auto it2 = sol.begin();
      while (it2 != sol.end()) {
        cout << *it2 << endl;
        ++it2;
      }
      cout << "----------" << endl;
    }
  }
}
