#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct jugador {
  bool connectat;
  int punts;
};

bool comp(const pair<string, int>& a, const pair<string, int>& b) {
  if (a.second == b.second) return a.first < b.first;
  return a.second > b.second;
}

int main() {
  string opcio;
  map<string, jugador> m;
  while (cin >> opcio) {
    if (opcio == "LOGIN") {
      string j;
      cin >> j;
      if (m.find(j) == m.end()) {
        jugador a;
        a.connectat = true;
        a.punts = 1200;
        m.insert(make_pair(j, a));
      }
      else m[j].connectat = true;
    }
    else if (opcio == "PLAY") {
      string j1, j2;
      cin >> j1 >> j2;
      if (m.find(j1) != m.end() and m[j1].connectat and m.find(j2) != m.end() and m[j2].connectat) {
        m[j1].punts += 10;
        if (m[j2].punts >= 1210) m[j2].punts -= 10;
      }
      else cout << "jugador(s) no connectat(s)" << endl;
    }
    else if (opcio == "GET_ELO") {
      string j;
      cin >> j;
      if (m.find(j) != m.end()) cout << j << " " << m[j].punts << endl;
    }
    else if (opcio == "LOGOUT") {
      string j;
      cin >> j;
      if (m.find(j) != m.end()) m[j].connectat = false;
    }
  }
  cout << endl << "RANKING" << endl;
  vector<pair<string, int>> v;
  auto it = m.begin();
  while (it != m.end()) {
    v.push_back(make_pair(it->first, it->second.punts));
    ++it;
  }
  sort(v.begin(), v.end(), comp);
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i].first << " " << v[i].second << endl;
  }
}
