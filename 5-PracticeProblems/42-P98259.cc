#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Mat;

void dijkstra(Mat& mat) {
  priority_queue<pair<int, pair<int, int>>> q;
  vector<vector<int>> max(mat.size(), vector<int>(mat[0].size(), 0));
  q.push(make_pair(0, make_pair(1, 1)));
  int cost = 10000000;
  int max_p = 0;
  while (not q.empty()) {
    int c = -q.top().first;
    pair<int, int> p = q.top().second;
    q.pop();
    if (mat[p.first][p.second] == 'T') {
      if (c < cost) {
        cost = c;
        max_p = max[p.first][p.second];
      }
      if (c == cost and max[p.first][p.second] > max_p) max_p = max[p.first][p.second];
    }
    else if (mat[p.first][p.second] == 'P') {
      mat[p.first][p.second] = '#';
      q.push(make_pair(-c - 1, make_pair(p.first + 1, p.second)));
      if (c == ) max[p.first + 1][p.second] = max[p.first][p.second] + 1;
      q.push(make_pair(-c - 1, make_pair(p.first, p.second + 1)));
      max[p.first][p.second + 1] = max[p.first][p.second] + 1;
      q.push(make_pair(-c - 1, make_pair(p.first - 1, p.second)));
      max[p.first - 1][p.second] = max[p.first][p.second] + 1;
      q.push(make_pair(-c - 1, make_pair(p.first, p.second - 1)));
      max[p.first][p.second - 1] = max[p.first][p.second] + 1;
    }
    else if (mat[p.first][p.second] == '.') {
      mat[p.first][p.second] = '#';
      q.push(make_pair(-c - 1, make_pair(p.first + 1, p.second)));
      max[p.first + 1][p.second] = max[p.first][p.second];
      q.push(make_pair(-c - 1, make_pair(p.first, p.second + 1)));
      max[p.first][p.second + 1] = max[p.first][p.second];
      q.push(make_pair(-c - 1, make_pair(p.first - 1, p.second)));
      max[p.first - 1][p.second] = max[p.first][p.second];
      q.push(make_pair(-c - 1, make_pair(p.first, p.second - 1)));
      max[p.first][p.second - 1] = max[p.first][p.second];
    }
  }
  if (cost != 10000000) cout << cost << " " << max_p << endl;
  else cout << "El telecos esta amagat." << endl;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    Mat mat(n + 2, vector<char>(m + 2, '#'));
    bool telecos = false;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        char c;
        cin >> c;
        if (c == 'T') telecos = true;
        mat[i + 1][j + 1] = c;
      }
    }
    if (telecos) dijkstra(mat);
    else cout << "El telecos ha fugit." << endl;
  }
}
