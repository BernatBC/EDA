#include <iostream>
#include <vector>
using namespace std;

vector<int> mult(vector<int> a, vector<int> b, int m) {
  vector<int> c(4);
  c[0] = (a[0]*b[0] + a[1]*b[2])%m;
  c[1] = (a[0]*b[1] + a[1]*b[3])%m;
  c[2] = (a[2]*b[0] + a[3]*b[2])%m;
  c[3] = (a[2]*b[1] + a[3]*b[3])%m;
  return c;
}

vector<int> pot(vector<int> a, int n, int m) {
  vector<int> c(4);
  c[0] = c[3] = 1;
  c[1] = c[2] = 0;
  if (n == 0) return c;
  if (n%2 == 0) {
    c = pot(a, n/2, m);
    return mult(c, c, m);
  }
  c = pot(a, n - 1, m);
  return mult(c, a, m);
}

int main() {
  vector<int> a(4);
  int n, m;
  while (cin >> a[0] >> a[1] >> a[2] >> a[3] >> n >> m) {
    vector<int> k(4);
    k = pot(a, n, m);
    cout << k[0] << " " << k[1] << endl;
    cout << k[2] << " " << k[3] << endl;
    cout << "----------" << endl;
  }
}
