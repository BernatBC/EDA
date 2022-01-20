#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Mat;

bool bfs(Mat& m, int i1, int j1) {
  if (m[i1][j1] != 'P') return false;
  queue<pair<int,int>> q;
  q.push(make_pair(i1, j1));
  while (not q.empty()) {
    pair<int, int> p1 = q.front();
    q.pop();
    //cout << p1.first << " " << p1.second << " " << m[p1.first][p1.second] << endl;
    if (m[p1.first][p1.second] == 'B') return true;
    if (m[p1.first][p1.second] == '.' or m[p1.first][p1.second] == 'P') {
      q.push(make_pair(p1.first - 1, p1.second));
      q.push(make_pair(p1.first + 1, p1.second));
      q.push(make_pair(p1.first, p1.second - 1));
      q.push(make_pair(p1.first, p1.second + 1));
      m[p1.first][p1.second] = 'X';
    }
  }
  return false;
}

int main() {
  int f, c;
  while (cin >> f >> c) {
    Mat m(f, vector<char>(c));
    int i1 = 0;
    int j1 = 0;
    for (int i = 0; i < f; ++i) {
      for (int j = 0; j < c; ++j) {
        char ca;
        cin >> ca;
        if (ca == 'P') {
          i1 = i;
          j1 = j;
        }
        else if (ca == 'F') {
          m[i - 1][j] = 'F';
          m[i][j - 1] = 'F';
          m[i + 1][j] = 'F';
          m[i][j + 1] = 'F';
          m[i - 1][j + 1] = 'F';
          m[i - 1][j - 1] = 'F';
          m[i + 1][j - 1] = 'F';
          m[i + 1][j + 1] = 'F';

        }
        if (m[i][j] != 'F') m[i][j] = ca;
      }
    }
    if (bfs(m, i1, j1)) cout << "si" << endl;
    else cout << "no" << endl;
  }
}
