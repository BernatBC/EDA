#include <iostream>
#include <vector>
using namespace std;

void merge_sort(vector<int>& v, int a, int b, int& inv) {
  //Split
  int m = (a + b)/2;
  if (b > a) {
    merge_sort(v, a, m, inv);
    merge_sort(v, m + 1, b, inv);
    //Merge
    vector<int> v_aux;
      int i = a;
      int j = m + 1;
      while (i <= m and j <= b) {
        if (v[i] <= v[j]) {
          v_aux.push_back(v[i]);
          ++i;
        }
        else {
          v_aux.push_back(v[j]);
          inv += m - i + 1;
          ++j;
        }
      }
      while (i <= m) {
        v_aux.push_back(v[i]);
        ++i;
      }
      while (j <= b) {
        v_aux.push_back(v[j]);
        ++j;
      }
      //Write in vector v
      for (int i = 0; i < v_aux.size(); ++i) {
        v[i + a] = v_aux[i];
      }
    }
}

int inversions(vector<int>v) {
  int inv = 0;
  merge_sort(v, 0, v.size() - 1, inv);
  return inv;
}

int main() {
  int n;
  while (cin >> n) {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    cout << inversions(v) << endl;
  }
}
