#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

typedef vector<vector<bool>> Mat;

void exahustive(const vector<char>& esp, const Mat& ma, vector<bool>& e, string s, int a) {
  if (s.size() == esp.size()) cout << s << endl;
  else {
    for (int i = 0; i < esp.size(); ++i) {
      char c = esp[i];
      if (not e[i] and (a == -1 or ma[i][a])) {
        e[i] = true;
        exahustive(esp, ma, e, s + c, i);
        e[i] = false;
      }
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<char> esp(n);
  map<char, int> num;
  for (int i = 0; i < n; ++i) {
    cin >> esp[i];
    num[esp[i]] = i;
  }
  int m;
  cin >> m;
  Mat ma(n, vector<bool>(n, true));
  for (int i = 0; i < m; ++i) {
    char a, b;
    cin >> a >> b;
    ma[num[a]][num[b]] = false;
    ma[num[b]][num[a]] = false;
  }
  vector<bool> e(n, false);
  string s = "";
  exahustive(esp, ma, e, s, -1);
}
