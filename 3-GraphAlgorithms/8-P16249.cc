#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

typedef map<string, vector<string>> matriu;

int main() {
  int n;
  while (cin >> n) {
    map<string, int> graus;
    vector<string> frase(n);
    for (int i = 0; i < n; ++i) {
      cin >> frase[i];
      graus[frase[i]] = 0;
    }
    int k;
    cin >> k;
    matriu mat;
    for (int i = 0; i < k; ++i) {
      string a, b;
      cin >> a >> b;
      mat[a].push_back(b);
      ++graus[b];
    }
    string smallest = "";
    priority_queue<string, vector<string>, greater<string>> q;
    int words = 0;
    for (int i = 0; i < n; ++i) {
      if (graus[frase[i]] == 0) q.push(frase[i]);
    }

    while(not q.empty()) {
      string s = q.top();
      q.pop();
      smallest = smallest + s;
      ++words;
      for (int i = 0; i < mat[s].size(); ++i) {
        if (--graus[mat[s][i]] == 0) q.push(mat[s][i]);
      }
    }
    if (words == n) cout << smallest << endl;
    else cout << "NO VALID ORDERING" << endl;
  }
}
