#include <iostream>
#include <vector>
#include <set>
using namespace std;

typedef vector<vector<int>> Mat;

void exhaustive(const Mat& mat, vector<int>& graus, vector<int>& v, set<int>& q) {
  if (q.empty()) {
    for (int i = 0; i < v.size(); ++i) {
      if (i != 0) cout << " ";
      cout << v[i];
    }
    cout << endl;
  }
  else {
    auto it = q.begin();
    while (it != q.end()) {
			int a = *it;
      for (int i = 0; i < mat[a].size(); ++i) {
        --graus[mat[a][i]];
        if (graus[mat[a][i]] == 0) q.insert(mat[a][i]);
      }
			q.erase(it);
			v.push_back(a);
			exhaustive(mat, graus, v, q);
			v.pop_back();
			it = q.insert(a).first;
      for (int i = 0; i < mat[a].size(); ++i) {
        ++graus[mat[a][i]];
        if (graus[mat[a][i]] == 1) q.erase(mat[a][i]);
      }
      ++it;
		}
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  Mat mat(n);
  vector<int> graus(n, 0);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    mat[a].push_back(b);
    ++graus[b];
  }
  set<int> q;
  vector<int> v;
  for (int i = 0; i < n; ++i) if (graus[i] == 0) q.insert(i);
  exhaustive(mat, graus, v, q);
}
