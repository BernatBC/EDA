#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(string a, string b) {
  if (a.size() == b.size()) return a < b;
  return a.size() < b.size();
}

int main(){
  int game = 1;
  string w = "";
  map<string, int> m;
  vector<string> v;
  while (w != "QUIT") {
    m.clear();
    v.clear();
    cin >> w;
    while (w != "END" and w != "QUIT") {
      m[w] += 1;
      cin >> w;
    }
    cout << "GAME #" << game << endl << "HAS:" << endl;
    for (auto it = m.begin(); it != m.end(); ++it) {
      if ((it->second)%2 == 0) v.push_back(it->first);
      else cout << it->first << endl;
    }
    cout << endl << "HAD:" << endl;
    sort(v.begin(), v.end(), comp);
    for(int i = 0; i < (int)v.size(); ++i) {
      cout << v[i] << endl;
    }
    if (w != "QUIT") cout << endl;
    ++game;
  }
}
