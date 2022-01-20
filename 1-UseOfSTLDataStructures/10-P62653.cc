#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

string tie_break;
bool comp(string a, string b) {
  if (a.size() == b.size()) {
    string w = tie_break.substr(0, a.size());
    if (w == a) return false;
    if (w == b) return true;
    if (a < b) {
      if (w > a and w < b) return true;
      return false;
    }
    else {
      if (w < a and w > b) return false;
      return true;
    }
  }
  return a.size() > b.size();
}
int main() {
  string p;
  int t = 0;
  priority_queue <string, vector<string>, decltype(comp)*> cua(comp);
  while (cin >> p) {
    if (p == "S") {
      string fan;
      cin >> fan;
      if (t != 0) {
        cout << fan << endl;
        --t;
      }
      else {
        cua.push(fan);
      }
    }
    else if (p == "T") {
      ++t;
      while (t > 0 and cua.size() != 0) {
        cout << cua.top() << endl;
        cua.pop();
        --t;
      }
    }
    else if (p == "E") {
      cout << t << " ticket(s) left" << endl;
      cout << cua.size() << " supporter(s) with no ticket" << endl << endl;
      t = 0;
      while (not cua.empty()) cua.pop();
    }
    else {
      tie_break = p;
    }
  }
}
